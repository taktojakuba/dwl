!/bin/bash

choice=$(printf "Shutdown\nReboot\nLogout\nSuspend" | rofi -dmenu -p "Power")
[ -z "$choice" ] && exit 1

case "$choice" in
	Shutdown) shutdown ;;
	Reboot)   reboot ;;
	Logout)   loginctl terminate-user kuba ;;
	Suspend)  loginctl suspend ;;
esac
