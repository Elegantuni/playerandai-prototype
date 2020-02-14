#ifndef __WEAPONS_H
#define __WEAPONS_H

#include "globaldefs.h"

struct weapons
{
	char* equiped;
	char* item;
	int damage;
	int rangey;
	int rangex;
	char* statuseffects[STATUSEFFECTSAMOUNT];
	char* durability;
	int timeleft;
	int temporarytimeleft;
};

#endif

