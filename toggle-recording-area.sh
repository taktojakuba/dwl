#!/bin/bash

PIDFILE="${XDG_RUNTIME_DIR}/wf-recorder-area.pid"
OUTDIR="${HOME}/Videos/Recordings"
AUDIO_SOURCE="JadeAudio JA11 Analog Stereo.monitor"

mkdir -p "$OUTDIR"

if [[ -f "$PIDFILE" ]] && kill -0 "$(cat "$PIDFILE")" 2>/dev/null; then
    kill -INT "$(cat "$PIDFILE")"
    rm -f "$PIDFILE"
    notify-send "Area recording" "Recording stopped"
else
    GEOMETRY=$(slurp)
    [[ -z "$GEOMETRY" ]] && exit 0
    OUTPUT="${OUTDIR}/recording-area-$(date +%Y-%m-%d_%H-%M-%S).mp4"

    wf-recorder \
        --geometry="$GEOMETRY" \
        --audio="$AUDIO_SOURCE" \
        --file="$OUTPUT" \
        >/tmp/wf-recorder-area.log 2>&1 &

    echo $! > "$PIDFILE"
    notify-send "Area recording" "Recording started"
fi
