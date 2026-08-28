#!/bin/bash

choice=$(printf "Shutdown\nReboot\nLogout\nSuspend" | rofi -dmenu -p "Power")
[ -z "$choice" ] && exit 1

case "$choice" in
	Shutdown) shutdown -p ;;
	Reboot)   shutdown -r ;;
	Logout)   loginctl terminate-user "$USER" ;;
	Suspend)  loginctl suspend ;;
esac
