#ifndef __INPUTMOVE_H
#define __INPUTMOVE_H

#ifdef INITLIBTCODNOW
#include <libtcod/libtcod.h>
#endif

#ifdef INITNCURSESNOW
#ifdef INITNCURSESNOW2
#include <ncurses.h>
#else
#include <curses.h>
#endif
#endif

void inputmove(int y, int x);

#endif

