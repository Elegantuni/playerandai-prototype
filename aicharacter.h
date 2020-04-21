#ifndef __AICHARACTER_H
#define __AICHARACTER_H

#include "globaldefs.h"
#include "movement.h"
#include "weapons.h"
#include "thiefing.h"
#include "classes.h"
#include "jobs.h"
#include "weaponsdamageenemies.h"

struct aicharacter
{
	int thenumber;
	int y;
	int x;
	struct picturestruct aipiccoord;
	int hitpoints;
	int magicpoints;
	int defensepoints;
	int hitpointsadjust;
	int magicpointsadjust;
	int defensepointsadjust;
	char* weapon;
	char* shield;
	char* charactersign;
	int prevy;
	int prevx;
	int magicattack;
	int count;
	int replayer;
	int playerturn;
	int randomitem;
	int shieldsrandomitem;
	struct movement aimovement[AIMOVE];
	struct weapons aiweapons;
	struct weaponsdamageenemies aiweaponsdamage;
	struct thiefing aithiefing;
	struct shields aishield;
	struct shieldsdamageenemies aishielddamage;
	struct character aicharacter;
	struct magic aimagic;
	struct armor aiarmor;
	struct classes aiclass;
	struct jobs aijob;
};

#endif

