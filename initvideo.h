#ifndef __INITVIDEO_H
#define __INITVIDEO_H

#ifdef INITLIBTCODNOW
#include "libtcod/libtcod.hpp"
#endif

#ifndef INITLIBTCODNOW
#ifndef INITWINDOWSNOW
#include <ncurses.h>
#else
#include <curses.h>
#endif
#endif

void initvideo(int hitpointsy, int hitpointsx);

#endif

