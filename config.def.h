/* See LICENSE file for copyright and license details. */
/* #include "gaplessgrid.c" */ 
/* appearance */
static const unsigned int borderpx  = 2.0;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gaps between windows */
static const unsigned int snap      = 12;       /* snap pixel */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 1;   /* systray spacing */
static const int systraypinningfailfirst = 0;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on
                                                   the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
                                       "PragmataPro:size=9",
                                      "Siji" 
 };
static const char dmenufont[]       = "PragmataPro:size=9";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_gruvbox_bg0[]    = "#282828";
static const char col_gruvbox_bg0_h[]  = "#034252";
static const char col_gruvbox_fg[]     = "#ebdbb2";
static const char col_gruvbox_fg0[]    = "#fbf1c7";
static const char col_gruvbox_yellow[] = "#fabd2f";
static const char col_gruvbox_purple_dark[] = "#b16286";
static const char col_gruvbox_purple[] = "#d3869b";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = 0xd0;
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gruvbox_fg0, col_gruvbox_bg0, col_cyan },
    [SchemeSel]  = { col_gruvbox_fg, col_gruvbox_bg0_h, col_gruvbox_bg0_h },
};
static const unsigned int alphas[][3]      = {
  /*               fg      bg        border     */
  [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
  [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* autostarts */
static const char *const autostart[] = {	
	"/home/cirrus/.fehbg", NULL,
	"tilda", NULL,
	"termite", NULL,
	"firefox", NULL,
	"dwmblocks", NULL,
	"compton", NULL,
	"volctl", NULL,
	"rss-notify", NULL,
	"cbatticon", NULL,
	"terminator", NULL,	
	"xbindkeys", NULL,										
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = {
/*		"web",
		"term",
		"code",
		"media",
		"game",
		"play",
		"misc"
**/
	    "\ue1d7",
		"\ue1ef",
		"\ue269",
		"\ue1d1",
		"\ue1e0",
        "\ue1df",
		"\ue1e9" 
};


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */    
	/* class		instance	title		tags mask	isfloating		monitor */
	 { "Gimp",     NULL,       NULL,       0,            True,         0 },
	 { "Firefox",  NULL,       NULL,       1,            False,        0 },
	 { "trayer",   NULL,       NULL,       1,            True,         0 },
	 { "Polybar",  NULL,       NULL,       1,            True,         0 },
	 { "MPlayer",  NULL,       NULL,       0,            True,         0 },
	 { "Pcmanfm",  NULL,  "Execute File",  0,            True,         0 },
	 { "Volctl",   NULL,  "Preferences",   0,            True,         0 },
	 { "mpv",      NULL,       NULL,       0,            True,         0 },
	 { "Termite",     NULL,    NULL,     4 << 0,         False,        0 },
	 { "Sxiv",        NULL,    NULL,       0,            True,         0 },
	 { "st-256color",  NULL,   NULL,       0,            False,        0 },
	 { "Terminator",  NULL,    NULL,       2,            False,        0 },
	 { "XClock",      NULL,    NULL,       4,            True,         0 },
	 { "feh",      NULL,       NULL,       0,            True,         0 },
         { "Tilda",    NULL,      "tilda",   6 << 5,         True,         0 },
	 { "Pavucontrol", NULL,    NULL,       0,            True,         0 },
	 { "Xeyes",      NULL,     NULL,       0,            True,         0 },
	 { "sublime_text",   NULL, "Sublime Text 2",    0,   False,        0 },
	 { "Orage",    NULL,       NULL,       0,            True,         0 },
	 { "Xsensors",  NULL,      NULL,       1,            True,         0 },
	 { "Vlc",       NULL,      NULL,       0,            True,         0 },
	 { "XTerm",     NULL,      NULL,       0,            True,         0 },
	 { "Toolkit",  "NULL", "Picture-in-Picture",    5,   True,         0 },
	 { "Dclock",    NULL,      NULL,    6 << 5,          True,         0 },
	 
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 0;    /* 1 means attach after the currently active window */


static const Layout layouts[] = {
	/* symbol     arrange function */
	    { "[]=",      tile },    /* first entry is default */
        { "><>",      NULL },    /* no layout function means floating behavior */
	    { "[M]",      monocle },
        { "TTT",      bstack },
        { "===",      bstackhoriz },
  	  /*  { "[G]",      gaplessgrid }, */ 
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gruvbox_bg0_h, "-nf", col_gruvbox_fg, "-sb", col_gruvbox_purple_dark, "-sf", col_gruvbox_fg0, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *emacscmd[] = { "emacsclient", "-c", "-n", NULL };
static const char *frontcmd[] = { "front", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
    { MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
    { MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY|ShiftMask,             XK_f,      spawn,          {.v = frontcmd } },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
    { MODKEY,                       XK_e,      spawn,          {.v = emacscmd } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

void
setlayoutex(const Arg *arg)
{
  setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
  view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
  view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
  toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
  tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
  toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
  tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
       /* signum           function */
       { "focusstack",     focusstack },
       { "setmfact",       setmfact },
       { "togglebar",      togglebar },
       { "incnmaster",     incnmaster },
       { "togglefloating", togglefloating },
       { "focusmon",       focusmon },
       { "tagmon",         tagmon },
       { "zoom",           zoom },
       { "view",           view },
       { "viewall",        viewall },
       { "viewex",         viewex },
       { "toggleview",     view },
       { "toggleviewex",   toggleviewex },
       { "tag",            tag },
       { "tagall",         tagall },
       { "tagex",          tagex },
       { "toggletag",      tag },
       { "toggletagex",    toggletagex },
       { "killclient",     killclient },
       { "quit",           quit },
       { "setlayout",      setlayout },
       { "setlayoutex",    setlayoutex },
};
