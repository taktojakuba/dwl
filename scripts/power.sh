#!/bin/bash

choice=$(printf "Shutdown\nReboot\nLogout\nSuspend" | rofi -dmenu -p "Power")
[ -z "$choice" ] && exit 1

case "$choice" in
	Shutdown) sudo shutdown -p ;;
	Reboot)   sudo shutdown -r ;;
	Logout)   sudo loginctl terminate-user kuba ;;
	Suspend)  sudo loginctl suspend ;;
esac
