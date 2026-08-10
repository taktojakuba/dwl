#!/bin/bash

set +e

wlr-randr --output HDMI-A-1 --mode 1920x1080@119.878998Hz >/dev/null 2>&1 &
noctalia >/dev/null 2>&1 &
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 >/dev/null 2>&1 &
~/.config/bashscripts/clipboardfix-wf.sh >/dev/null 2>&1 &
