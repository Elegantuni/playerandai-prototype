#ifndef __WEAPONS_H
#define __WEAPONS_H

#include "globaldefs.h"

struct weapons
{
	char* equiped;
	char* item[WEAPONSAMOUNT];
	int damage;
	int rangey;
	int rangex;
	char* statuseffects[STATUSEFFECTSAMOUNT];
	char* durability[WEAPONSAMOUNT];
	int timeleft;
	int temporarytimeleft;
	int numberitems;
	int weaponcount;
	int randomweapon[WEAPONSAMOUNT];
};

#endif

