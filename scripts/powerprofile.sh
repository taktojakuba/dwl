#!/bin/bash

choice=$(printf "power-saver\nbalanced\nperformance" | rofi -dmenu -p "Power-profile")
[ -z "$choice" ] && exit 1

case "$choice" in
	power-saver) powerprofilesctl set power-saver ;;
	balanced)   powerprofilesctl set balanced ;;
	performance)   powerprofilesctl set performance ;;
esac
