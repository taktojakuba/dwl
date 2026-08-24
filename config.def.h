/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;
static const unsigned int borderpx         = 1;  /* borderpx */

/* cursor theme/size  */
static const char *cursor_theme            = "Future-dark-cursors";
static const int cursor_size               = 24;

/* window gaps */
static const int gappx                     = 15;

/* tags */
#define TAGCOUNT (9)

/* logging */
static int log_level = WLR_ERROR;

/* window resizing */
/* resize_corner:
 * 0: top-left
 * 1: top-right
 * 2: bottom-left
 * 3: bottom-right
 * 4: closest to the cursor
 */
static const int resize_corner = 4;
static const int warp_cursor = 1;	/* 1: warp to corner, 0: don’t warp */
static const int lock_cursor = 0;	/* 1: lock cursor, 0: don't lock */

/* NOTE: ALWAYS keep a rule declared even if you don't use rules (e.g leave at least one example) */
static const Rule rules[] = {
	{ NULL,      NULL,    0,           0,            -1 },
};

/* layouts */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[F]",      fair },
  { "[]=",      tile },
	{ "><>",      NULL },
  { "[M]",      monocle },
};

static const int layout = 0; 

/* monitors */
static const MonitorRule monrules[] = {
	{ "HDMI-A-1", 0.55f, 1,      1,    &layouts[layout], WL_OUTPUT_TRANSFORM_NORMAL,   1920, 60 },
	{ "eDP-1",    0.55f, 1,      1,    &layouts[layout], WL_OUTPUT_TRANSFORM_NORMAL,      0,  0 },
	{ NULL,       0.55f, 1,      1,    &layouts[layout], WL_OUTPUT_TRANSFORM_NORMAL,     -1, -1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	.layout = "pl",
	.options = "caps2super:super",
};

static const int repeat_rate = 35;
static const int repeat_delay = 250;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;

static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;

static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

#define MODKEY WLR_MODIFIER_LOGO

static const int cursor_timeout = 5;

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }

/* shell command helper */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static const Key keys[] = {
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

	/* focus window in direction vim style */
	{ MODKEY,                    XKB_KEY_h,           focusdir,         {.ui = 0} },
	{ MODKEY,                    XKB_KEY_l,           focusdir,         {.ui = 1} },
	{ MODKEY,                    XKB_KEY_k,           focusdir,         {.ui = 2} },
	{ MODKEY,                    XKB_KEY_j,           focusdir,         {.ui = 3} },
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
	/* toggle maximize screen */
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
	{ 0,                         XKB_KEY_Print, spawn, SHCMD("$HOME/dwl/fscreen.sh HDMI-A-1")},
	{ WLR_MODIFIER_SHIFT,        XKB_KEY_Print, spawn, SHCMD("$HOME/dwl/sscreen.sh")},
	{ WLR_MODIFIER_CTRL,         XKB_KEY_Print, spawn, SHCMD("$HOME/dwl/toggle-recording.sh") },
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT, XKB_KEY_Print, spawn, SHCMD("$HOME/dwl/toggle-recording-area.sh") },

	/* app binds */
	{ MODKEY,                    XKB_KEY_s,           spawn,            SHCMD("foot tmux") },
	{ MODKEY,                    XKB_KEY_v,           spawn,            SHCMD("foot nvim") },
	{ MODKEY,                    XKB_KEY_e,           spawn,            SHCMD("foot yazi") },
	{ MODKEY,                    XKB_KEY_b,           spawn,            SHCMD("firefox") },
	{ MODKEY,                    XKB_KEY_t,           spawn,            SHCMD("foot") },

	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
