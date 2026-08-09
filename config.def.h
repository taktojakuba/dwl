/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const unsigned int borderpx         = 1;  /* border pixel of windows */
/* colors */
static float rootcolor[]                   = COLOR(0x0f0a0bff); /* background of root */
static float bordercolor[]                 = COLOR(0x795457ff); /* border of non-focused windows */
static float focuscolor[]                  = COLOR(0xe0858dff); /* border of focused windows */
static float urgentcolor[]                 = COLOR(0xd96a76ff); /* border of urgent windows */
/* This conforms to the xdg-protocol. Set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.0f, 0.0f, 0.0f, 1.0f}; /* You can also use glsl colors */

/* cursor theme and size; NULL theme means use the system XCURSOR_THEME */
static const char *cursor_theme            = "Future-dark-cursors";
static const int cursor_size               = 24;

/* window gaps: spacing between tiled windows and screen edges, in pixels */
static const int gappx                     = 2;

/* tagging - TAGCOUNT must be no greater than 31 */
#define TAGCOUNT (9)

/* logging */
static int log_level = WLR_ERROR;

static const Rule rules[] = {
	/* app_id    title    tags mask    isfloating    monitor */
	{ NULL,      NULL,    0,           0,            -1 }, /* default no-op rule: dwl requires at least one rule */
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[F]",      fair },    /* default: fair (grid of equal-sized windows) */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

static const int layout = 1; 

/* monitors */
/* (x=-1, y=-1) is reserved as an "autoconfigure" monitor position indicator
 * WARNING: negative values other than (-1, -1) cause problems with Xwayland clients due to
 * https://gitlab.freedesktop.org/xorg/xserver/-/issues/899 */
static const MonitorRule monrules[] = {
   /* name        mfact  nmaster scale layout       rotate/reflect                x     y */
	{ "HDMI-A-1", 0.55f, 1,      1,    &layouts[layout], WL_OUTPUT_TRANSFORM_NORMAL,   1920, 60 },
	{ "eDP-1",    0.55f, 1,      1,    &layouts[layout], WL_OUTPUT_TRANSFORM_NORMAL,      0,  0 },
	{ NULL,       0.55f, 1,      1,    &layouts[layout], WL_OUTPUT_TRANSFORM_NORMAL,     -1, -1 },
	/* default monitor rule: can be changed but cannot be eliminated; at least one monitor rule must exist */
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	.layout = "pl",
	.options = "caps2super:super",
};

static const int repeat_rate = 35;
static const int repeat_delay = 200;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static const Key keys[] = {
	/* Note that Shift changes certain key codes: 2 -> at, etc. */
	/* modifier                  key                  function          argument */

	/* workspaces: switch */
	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                        0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                            1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                    2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                        3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                       4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                   5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                     6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                      7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                     8),

	/* focus window in direction (vim style) */
	{ MODKEY,                    XKB_KEY_h,           focusdir,         {.ui = 0} }, /* left */
	{ MODKEY,                    XKB_KEY_l,           focusdir,         {.ui = 1} }, /* right */
	{ MODKEY,                    XKB_KEY_k,           focusdir,         {.ui = 2} }, /* up */
	{ MODKEY,                    XKB_KEY_j,           focusdir,         {.ui = 3} }, /* down */
	{ MODKEY,                    XKB_KEY_Left,        focusdir,         {.ui = 0} },
	{ MODKEY,                    XKB_KEY_Right,       focusdir,         {.ui = 1} },
	{ MODKEY,                    XKB_KEY_Up,          focusdir,         {.ui = 2} },
	{ MODKEY,                    XKB_KEY_Down,        focusdir,         {.ui = 3} },

	/* swap windows in direction */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_h,           swapdir,          {.ui = 0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_l,           swapdir,          {.ui = 1} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_k,           swapdir,          {.ui = 2} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_j,           swapdir,          {.ui = 3} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Left,        swapdir,          {.ui = 0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Right,       swapdir,          {.ui = 1} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Up,          swapdir,          {.ui = 2} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Down,        swapdir,          {.ui = 3} },

	/* toggle float */
	{ MODKEY,                    XKB_KEY_f,           togglefloating,   {0} },
	/* toggle maximize screen (mango); dwl has no maximize, fullscreen is closest */
	{ MODKEY,                    XKB_KEY_w,           togglefullscreen, {0} },
	/* toggle fullscreen */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_w,           togglefullscreen, {0} },

	/* kill window */
	{ MODKEY,                    XKB_KEY_q,           killclient,       {0} },

	/* noctalia shell binds */
	{ MODKEY,                    XKB_KEY_a,           spawn,            SHCMD("noctalia msg panel-toggle launcher") },
	{ MODKEY,                    XKB_KEY_y,           spawn,            SHCMD("noctalia msg panel-toggle wallpaper") },
	{ MODKEY,                    XKB_KEY_Escape,      spawn,            SHCMD("noctalia msg panel-toggle session") },
	/* audio */
	{ 0,                         XKB_KEY_XF86AudioRaiseVolume, spawn,   SHCMD("noctalia msg volume-up") },
	{ 0,                         XKB_KEY_XF86AudioLowerVolume, spawn,   SHCMD("noctalia msg volume-down") },
	{ 0,                         XKB_KEY_XF86AudioMute, spawn,           SHCMD("noctalia msg volume-mute") },
	/* media */
	{ 0,                         XKB_KEY_XF86AudioPlay, spawn,           SHCMD("noctalia msg media toggle") },
	{ 0,                         XKB_KEY_XF86AudioNext, spawn,           SHCMD("noctalia msg media next") },
	{ 0,                         XKB_KEY_XF86AudioPrev, spawn,           SHCMD("noctalia msg media previous") },
	/* brightness */
	{ 0,                         XKB_KEY_XF86MonBrightnessUp, spawn,     SHCMD("noctalia msg brightness-up") },
	{ 0,                         XKB_KEY_XF86MonBrightnessDown, spawn,   SHCMD("noctalia msg brightness-down") },
	/* power */
	{ 0,                         XKB_KEY_XF86Search, spawn,              SHCMD("noctalia msg power-cycle") },

	/* screenshots */
	{ 0,                         XKB_KEY_Print, spawn, SHCMD("f=\"$HOME/Pictures/Screenshots/$(date +%Y%m%d%H%M%S).png\"; grim \"$f\" && notify-send -i \"$f\" \"Screenshot saved\"") },
	{ WLR_MODIFIER_SHIFT,        XKB_KEY_Print, spawn, SHCMD("f=\"$HOME/Pictures/Screenshots/$(date +%Y%m%d%H%M%S).png\"; g=$(slurp) && [ -n \"$g\" ] && grim -g \"$g\" \"$f\" && wl-copy < \"$f\" && notify-send -i \"$f\" \"Screenshot saved and copied to clipboard\"") },
	{ WLR_MODIFIER_CTRL,         XKB_KEY_Print, spawn, SHCMD("~/.local/bin/toggle-recording") },
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT, XKB_KEY_Print, spawn, SHCMD("~/.local/bin/toggle-recording-area") },

	/* app binds */
	{ MODKEY,                    XKB_KEY_s,           spawn,            SHCMD("foot tmux") },
	{ MODKEY,                    XKB_KEY_v,           spawn,            SHCMD("foot nvim") },
	{ MODKEY,                    XKB_KEY_e,           spawn,            SHCMD("foot yazi") },
	{ MODKEY,                    XKB_KEY_b,           spawn,            SHCMD("flatpak run org.mozilla.firefox") },
	{ MODKEY,                    XKB_KEY_t,           spawn,            SHCMD("foot") },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
	/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
	 * do not remove them.
	 */
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
