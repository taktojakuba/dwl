#!/bin/bash

dir="$HOME/Pictures/Wallpapers"
[ -d "$dir" ] || exit 1

wallpaper=$(find "$dir" -maxdepth 1 -type f \( -name '*.jpg' -o -name '*.jpeg' -o -name '*.png' -o -name '*.webp' \) -printf '%f\n' | sort | rofi -dmenu -p "Wallpaper")
[ -z "$wallpaper" ] && exit 1

pkill wbg 2>/dev/null
wbg "$dir/$wallpaper" 2>/dev/null &
matugen --prefer=value image "$dir/$wallpaper" -t scheme-content &
