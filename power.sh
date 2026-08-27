#!/bin/bash

choice=$(printf "Shutdown\nReboot\nLogout\nSuspend" | rofi -dmenu -p "Power")
[ -z "$choice" ] && exit 1

case "$choice" in
	Shutdown) systemctl poweroff ;;
	Reboot)   systemctl reboot ;;
	Logout)   loginctl terminate-user "$USER" ;;
	Suspend)  systemctl suspend ;;
esac