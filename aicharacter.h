#ifndef __AICHARACTER_H
#define __AICHARACTER_H

#include "globaldefs.h"
#include "movement.h"
#include "weapons.h"
#include "thiefing.h"
#include "classes.h"
#include "jobs.h"

struct aicharacter
{
	int thenumber;
	int y;
	int x;
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
	struct weapons aiweapons[WEAPONSAMOUNT];
	struct thiefing aithiefing[THIEFINGAMOUNT];
	struct shields aishield[SHIELDAMOUNT];
	struct character aicharacter[CHARACTERAMOUNT];
	struct magic aimagic[MAGICAMOUNT];
	struct armor aiarmor[ARMORAMOUNT];
	struct classes aiclasses[CLASSAMOUNT];
	struct jobs aijob[JOBAMOUNT];
};

#endif

