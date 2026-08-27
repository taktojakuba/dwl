#!/bin/bash

ID_FILE="/tmp/volume-notify-id"

wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+

vol=$(wpctl get-volume @DEFAULT_AUDIO_SINK@ | awk '{print int($2*100)}')

if [ -f "$ID_FILE" ]; then
    id=$(cat "$ID_FILE")
    new_id=$(notify-send -u low -r "$id" -p "Volume" "${vol}%")
else
    new_id=$(notify-send -u low -p "Volume" "${vol}%")
fi

echo "$new_id" > "$ID_FILE"