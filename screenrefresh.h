#ifndef __SCREENREFRESH_H
#define __SCREENREFRESH_H

#ifdef INITNCURSESNOW
#ifdef INITNCURSESNOW2
#include <ncurses.h>
#else
#include <curses.h>
#endif
#endif

#ifdef INITLIBTCODNOW
#include <libtcod/libtcod.h>
#endif

void screenrefresh();

#endif

