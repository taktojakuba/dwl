#!/bin/bash

name=$(date +%Y-%m-%d_%H-%M-%S)
file="$HOME/Pictures/Screenshots/$name.png"

grim -o $1 "$file"
notify-send -u low "$(basename "$file") saved"
wl-copy < $file
