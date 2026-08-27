#!/bin/bash

ID_FILE="/tmp/volume-notify-id"

wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle

status=$(wpctl get-volume @DEFAULT_AUDIO_SINK@)

if echo "$status" | grep -q MUTED; then
    msg="Muted"
else
    vol=$(echo "$status" | awk '{print int($2*100)}')
    msg="Volume ${vol}%"
fi

if [ -f "$ID_FILE" ]; then
    id=$(cat "$ID_FILE")
    new_id=$(notify-send -u low -r "$id" -p "Audio" "$msg")
else
    new_id=$(notify-send -u low -p "Audio" "$msg")
fi

echo "$new_id" > "$ID_FILE"