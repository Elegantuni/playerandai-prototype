#ifndef __INPUTGETTER_H
#define __INPUTGETTER_H

#ifdef INITLIBTCODNOW
#include "libtcodinput.h"
#endif

#ifdef INITNCURSESNOW
#include "ncursesinput.h"
#endif

void* inputgetter();

#endif

