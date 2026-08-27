#!/bin/bash

PIDFILE="${XDG_RUNTIME_DIR}/wf-recorder.pid"
OUTDIR="${HOME}/Videos/Recordings"
AUDIO_SOURCE="JadeAudio JA11 Analog Stereo.monitor"

mkdir -p "$OUTDIR"

if [[ -f "$PIDFILE" ]] && kill -0 "$(cat "$PIDFILE")" 2>/dev/null; then
kill -INT "$(cat "$PIDFILE")"
rm -f "$PIDFILE"
notify-send "Screen recording" "Recording stopped"
else
	OUTPUT="${OUTDIR}/recording-$(date +%Y-%m-%d_%H-%M-%S).mp4"

	wf-recorder \
		--audio="$AUDIO_SOURCE" \
		--file="$OUTPUT" \
		>/tmp/wf-recorder.log 2>&1 &

	echo $! > "$PIDFILE"
	notify-send "Screen recording" "Recording started"
fi
