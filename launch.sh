#!/bin/bash
# Launch dwl from ly (or any display manager).
export XCURSOR_THEME=Future-dark-cursors
export XCURSOR_SIZE=24
export XDG_CURRENT_DESKTOP=dwl:wlroots
# Point the session at the dinit-started dbus user service; without this
# flatpak apps and xdg-desktop-portal requests can't find the session bus.
export DBUS_SESSION_BUS_ADDRESS="unix:path=/run/user/$(id -u)/bus"
# GLES2 renderer: far less memory than wlroots' default Vulkan renderer
# on the Intel iGPU. pixman = even less memory but software rendering.
export WLR_RENDERER=opengl
exec /home/kuba/dwl/dwl -s /home/kuba/dwl/autostart.sh
