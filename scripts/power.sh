#!/bin/bash

choice=$(printf "Shutdown\nReboot\nLogout\nSuspend" | rofi -dmenu -p "Power")
[ -z "$choice" ] && exit 1

case "$choice" in
	Shutdown) sudo dinitctl poweroff ;;
	Reboot)   sudo dinitctl reboot ;;
	Logout)   pkill -u "$USER" ;;
	Suspend)  sudo dinitctl suspend ;;
esac
