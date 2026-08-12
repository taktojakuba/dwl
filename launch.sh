#!/bin/bash
export XCURSOR_THEME=Future-dark-cursors
export XCURSOR_SIZE=24
export XDG_CURRENT_DESKTOP=dwl:wlroots
export DBUS_SESSION_BUS_ADDRESS="unix:path=/run/user/$(id -u)/bus"
export WLR_RENDERER=gles2
# gles2 vulkan
exec prime-run /home/kuba/dwl/dwl -s /home/kuba/dwl/autostart.sh
