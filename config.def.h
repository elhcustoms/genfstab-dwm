/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 5; /* border pixel of windows */
static const unsigned int gappx = 25;   /* gaps between windows */
static const unsigned int snap = 32;    /* snap pixel */
static const unsigned int systraypinning =
    0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor
          X */
static const unsigned int systrayonleft =
    0; /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst =
    1; /* 1: if pinning fails, display systray on the first monitor, False:
          display systray on the last monitor*/
static const int showsystray = 1; /* 0 means no systray */
static const int showbar = 1;     /* 0 means no bar */
static const int topbar = 1;      /* 0 means bottom bar */
static const int horizpadbar = 5; /* horizontal padding for statusbar */
static const int vertpadbar = 5;  /* vertical padding for statusbar */
static const int vertpad = 10;    /* vertical padding of bar */
static const int sidepad = 7;     /* horizontal padding of bar */
static const int user_bh = 1; /* 0 means that dwm will calculate bar height, >=
                                 1 means dwm will user_bh as bar height */
static const char *fonts[] = {"Source Code Pro:size=12",
                              "Font Awesome:size=14"};
static const char dmenufont[] = "monospace:size=10";
static const char col_gray1[] = "#17202a";
static const char col_gray2[] = "#3B4252";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#ffffff";
static const char col_cyan[] = "#d78ac6";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    [SchemeSel] = {col_gray4, col_cyan, col_cyan},
    [SchemeStatus] = {col_gray3, col_gray1,
                      "#000000"}, // Statusbar right {text,background,not used
                                  // but cannot be empty}
    [SchemeTagsSel] = {col_gray4, col_cyan,
                       "#000000"}, // Tagbar left selected {text,background,not
                                   // used but cannot be empty}
    [SchemeTagsNorm] =
        {col_gray3, col_gray1,
         "#000000"}, // Tagbar left unselected {text,background,not used but
                     // cannot be empty}
    [SchemeInfoSel] =
        {col_gray4, col_cyan,
         "#000000"}, // infobar middle  selected {text,background,not used but
                     // cannot be empty}
    [SchemeInfoNorm] =
        {col_gray3, col_gray1,
         "#000000"}, // infobar middle  unselected {text,background,not used but
                     // cannot be empty}
};

/* tagging */
/*static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"}; */
static const char *tags[] = {"", "", "", "", "", "", "", "", ""};

static const char *tagsel[][2] = {
    {"#ff0000", "#302d41"}, {"#ff7f00", "#302d41"}, {"#ffff00", "#302d41"},
    {"#00ff00", "#302d41"}, {"#0000ff", "#302d41"}, {"#4b0082", "#302d41"},
    {"#9400d3", "#302d41"}, {"#ffffff", "#302d41"}, {"#000000", "#302d41"},
};
static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp", NULL, NULL, 0, 1, -1},
    {"Firefox", NULL, NULL, 1 << 8, 0, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle}, {"[@]", spiral}, {"[\\]", dwindle},
};
#include <X11/XF86keysym.h>

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
static const char *termcmd[] = {"st", NULL};

static const char *upvol[] = {"/usr/bin/pactl", "set-sink-volume", "0", "+5%",
                              NULL};
static const char *downvol[] = {"/usr/bin/pactl", "set-sink-volume", "0", "-5%",
                                NULL};
static const char *mutevol[] = {"/usr/bin/pactl", "set-sink-mute", "0",
                                "toggle", NULL};
static Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_d, spawn, SHCMD("dmenu_run")},
    {MODKEY | ShiftMask, XK_d, spawn, SHCMD("rofi -show drun")},
    {MODKEY, XK_Return, spawn, SHCMD("tabbed -r 2 st -w '' || st ")},
    {MODKEY | ShiftMask, XK_b, togglebar, {0}},

    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_o, incnmaster, {.i = -1}},
    {MODKEY, XK_p, spawn, SHCMD("pcmanfm")},
    {MODKEY, XK_b, spawn, SHCMD("librewolf || firefox || chromium")},
    {MODKEY, XK_x, spawn, SHCMD("slock")},
    {0, XK_Print, spawn,
     SHCMD("flameshot gui --path $HOME/Pictures/screenshots/")},
    {0, XF86XK_AudioLowerVolume, spawn, {.v = downvol}},
    {0, XF86XK_AudioMute, spawn, {.v = mutevol}},
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = upvol}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY | ShiftMask, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, XK_q, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY | ShiftMask, XK_f, togglefullscr, {0}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ControlMask | ShiftMask, XK_q, quit, {1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = -1}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_r, quit, {0}},
    {MODKEY, XK_e, setlayout, {.v = &layouts[3]}},
    {MODKEY | ShiftMask, XK_e, setlayout, {.v = &layouts[4]}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
