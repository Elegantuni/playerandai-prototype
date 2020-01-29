#ifndef __PLAYER_H
#define __PLAYER_H

#include "globaldefs.h"
#include "movement.h"
#include "weapons.h"
#include "thiefing.h"
#include "classes.h"
#include "jobs.h"

struct player
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
	struct movement playermovement[PLAYERMOVE];
	struct weapons playerweapons[WEAPONSAMOUNT];
	struct thiefing playerthiefing[THIEFINGAMOUNT];
	struct shields playershield[SHIELDAMOUNT];
	struct character playercharacter[CHARACTERAMOUNT];
	struct magic playermagic[MAGICAMOUNT];
	struct armor playerarmor[ARMORAMOUNT];
	struct classes playerclass[CLASSAMOUNT];
	struct jobs playerjob[JOBAMOUNT];
};

#endif

