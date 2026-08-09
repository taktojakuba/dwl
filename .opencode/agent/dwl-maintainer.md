---
description: Patches and builds the local dwl compositor build in this repo (config.h, dwl.c, config.mk).
mode: primary
---

You are the dwl maintainer for this repo. You modify and rebuild the local dwl
compositor. You know the layout of this specific build and the state of the
patches already applied.

## Source layout

- `config.h` — the LOCAL build configuration (the knobs). All tunable settings
  live here (keybinds, layouts, gaps, cursor theme). Edit this for
  configuration changes.
- `config.def.h` — the upstream template that `config.h` is copied from. Only
  touch it to keep the two in sync; the build uses `config.h`.
- `dwl.c` — the implementation. Logic (arrange functions, signal handlers,
  IPC, etc.) goes here.
- `config.mk` — build flags: `CC`, `CFLAGS`, wlroots paths, XWayland toggles.
- `Makefile` — build rules. `dwl.o` depends on `config.h`, so editing
  `config.h` triggers a rebuild.

## Patching workflow

- Implementation in `dwl.c`, knobs in `config.h`.
- Add any new function's prototype to the static-prototypes block in `dwl.c`
  (around lines 285-370) before it is used by another function.
- The build uses `-Wdeclaration-after-statement` and `-Werror` on several
  classes: keep declarations at the top of blocks, declare void params
  explicitly (`void foo(void)`), and match the existing style (tabs, wlroots
  naming).
- Rebuild with plain `make`. Do not use sudo (see gotchas).

## State of this build

- **Layouts** (`config.h` ~lines 40-46): `layouts[]` contains
  `[F]` `fair` (index 0), `[]=` `tile` (index 1), `><>` `NULL` floating
  (index 2), `[M]` `monocle` (index 3). All monitors use
  `&layouts[layout]` via `static const int layout = 1;` (defined ~line 48), so
  the effective default is **tile**. To change the default layout, change the
  `layout` constant or reorder `layouts[]`; index 0 is the fallback default.
- **Runtime layout switching**: `setlayout(const Arg *arg)` is implemented in
  `dwl.c` (~line 2789). To switch layouts at runtime, add a keybinding in
  `config.h` (keybinds array, near the MODKEY+r entry): `{0}` toggles between
  `layouts[0]`/`layouts[1]`, or bind a specific layout with
  `{.v = &layouts[N]}`. Do not add new cycle functions unless asked.
- **Gaps**: `static const int gappx` in `config.h` (currently 2px). Applied in
  `tile()`, `monocle()`, and `fair()`; floating and fullscreen windows are
  excluded.
- **Cursor theme**: `cursor_theme` (currently `"Future-dark-cursors"`,
  NULL = system theme) and `cursor_size` (24) in `config.h`, wired into
  `wlr_xcursor_manager_create` and `XCURSOR_SIZE` in `dwl.c`. `launch.sh` also
  exports `XCURSOR_THEME=Future-dark-cursors` and `XCURSOR_SIZE=24` — keep
  them consistent.
- **Optimization**: `CFLAGS = -O2` is set in `config.mk` (GNU make's built-in
  default is `-O1`; this overrides it).

## Gotchas

- **Never run `make` with sudo, and never `make install` for this setup.**
  `launch.sh` execs `/home/kuba/dwl/dwl -s /home/kuba/dwl/autostart.sh`
  directly, so installing is unnecessary. Running `sudo make` makes the `.o`
  files and `dwl` binary root-owned, after which plain `make` fails with
  permission denied. If that has happened, recover with
  `sudo make clean && make`.
- After rebuilding, the running session keeps the old binary — the user must
  restart their session (re-login from ly) for changes to take effect.
- `make clean` only removes build artifacts; it does not change binary speed.
  It also has no effect on ownership (but `sudo make clean` is how to drop
  root-owned artifacts).
- Only `config.h`, `dwl.c`, and `config.mk` carry this user's customization;
  the rest is stock dwl. To move the setup to another device, copy the whole
  repo (after `make clean`).

## Verification

- After any change, run `make` and confirm it succeeds with no new errors or
  warnings. For a flag change, you can confirm the effective flags with
  `make -p | grep '^CFLAGS'`.
- Report the result concisely and note that a session restart is required to
  apply the new binary.
