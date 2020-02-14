#ifdef INITWINDOWSNOW
#include <curses.h>
#include "fileexists.h"
#endif

ifdef INITOPENSSL
#include "seed.h"
#endif

#ifdef INITNCURSESNOW2
#include <ncurses.h>
#include unistd.h>
#endif

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

#ifdef INITLIBTCODNOW
#if !defined(_MSC_VER)
#include <unistd.h>
#endif
#endif

#ifdef INITMSYS2NOW
#include <unistd.h>
#endif

#include "str2int.h"

#include <stdio.h>

#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#ifdef FREEBSD
#include "freebsddepends.h"
#endif

#ifdef INITNCURSESNOW
#define RETURNTYPEVIDEO intptr_t
#endif

#ifdef INITLIBTCODNOW
#define RETURNTYPEVIDEO char
#endif

#include "alldefines.h"

#include "initvideo.h"

#include "ncursesinput.h"


