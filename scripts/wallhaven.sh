#!/bin/bash

# Fetch and download wallpapers from wallhaven.cc, then pick one to set as background.

dir="$HOME/Pictures/Wallpapers/Wallhaven"
mkdir -p "$dir"

api="https://wallhaven.cc/api/v1/search"
count=20

# Ask for a search query (empty = random SFW wallpapers)
query=$(rofi -dmenu -theme-str 'window { width: 40%; }' -p "Search wallhaven" -mesg "Empty = random wallpapers" 2>/dev/null)
[ -z "$query" ] && exit 1

# Build API params
params="purity=100&categories=100&sorting=random&atleast=1920x1080"
[ -n "$query" ] && params="$params&q=$query"

echo "Fetching wallpapers from wallhaven..." >&2
json=$(curl -s --max-time 30 "$api?$params")

# Parse results: path (full image), thumb (grid icon), id, resolution
mapfile -t paths < <(jq -r '.data[].path' <<<"$json")
mapfile -t thumbs < <(jq -r '.data[].thumbs.large' <<<"$json")
mapfile -t ids < <(jq -r '.data[].id' <<<"$json")
mapfile -t res < <(jq -r '.data[].resolution' <<<"$json")

total="${#ids[@]}"
[ "$total" -eq 0 ] && { echo "No results found." >&2; exit 1; }

# Download up to $count wallpapers; detect the real file type for the extension.
downloaded=0
files=()
for ((i = 0; i < total && downloaded < count; i++)); do
  file="$dir/${ids[$i]}.jpg"
  if [ -f "$file" ]; then
    echo "skip (already have) ${ids[$i]} - ${res[$i]}" >&2
  else
    echo "download ${ids[$i]} - ${res[$i]}" >&2
    curl -s --max-time 60 -o "$file" "${paths[$i]}"
    if [ -s "$file" ]; then
      downloaded=$((downloaded + 1))
      # Re-derive extension from the actual downloaded bytes
      real=$(file -b "$file" | grep -oiE 'png|jpe?g|webp' | head -1 | tr '[:upper:]' '[:lower:]')
      if [ -n "$real" ] && ! grep -qi "jpg\|jpeg" <<<"$real"; then
        fixed="$dir/${ids[$i]}.$real"
        file "$file" >/dev/null 2>&1 && mv "$file" "$fixed"
        file="$fixed"
      fi
    else
      rm -f "$file"
    fi
  fi
  [ -f "$file" ] && files+=("$file")
done

echo "Have ${#files[@]} wallpaper(s) in $dir" >&2

[ "${#files[@]}" -eq 0 ] && exit 1

# Picker: show downloaded images in a rofi grid, using wallhaven's light
# thumbnails as icons (loading the full-size files stalls rofi).
workdir="$(mktemp -d)"
trap 'rm -rf "$workdir"' EXIT

for f in "${files[@]}"; do
  id="${f##*/}"
  id="${id%%.*}"
  idx=-1
  for ((j = 0; j < total; j++)); do
    [ "${ids[$j]}" = "$id" ] && { idx=$j; break; }
  done
  if [ "$idx" -ge 0 ] && [ -n "${thumbs[$idx]}" ]; then
    thumb="$workdir/$id.jpg"
    curl -s --max-time 20 -o "$thumb" "${thumbs[$idx]}"
    [ -s "$thumb" ] && icon="$thumb" || icon="$f"
  else
    icon="$f"
  fi
  printf '%s\0icon\x1f%s\n' "$(basename "$f")" "$icon"
done > "$workdir/list"

selection=$(rofi -dmenu -theme wallhaven-grid -show-icons -i \
            -p "Wallpaper" < "$workdir/list")
[ -z "$selection" ] && exit 1

chosen_id="${selection%%$'\n'*}"
chosen=""
for f in "${files[@]}"; do
  [ "$(basename "$f")" = "$chosen_id" ] && { chosen="$f"; break; }
done

if [ -n "$chosen" ] && [ -f "$chosen" ]; then
  pkill wbg 2>/dev/null
  wbg "$chosen" 2>/dev/null &
  echo "Set $chosen" >&2
fi
