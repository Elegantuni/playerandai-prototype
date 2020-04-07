#ifndef __PLAYER_H
#define __PLAYER_H

#include "globaldefs.h"
#include "movement.h"
#include "weapons.h"
#include "thiefing.h"
#include "classes.h"
#include "jobs.h"
#include "character.h"
#include "weaponsdamage.h"

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
	struct weapons playerweapons;
	struct weaponsdamage playerweaponsdamage;
	struct thiefing playerthiefing;
	struct shields playershield;
	struct shieldsdamage playershielddamage;
	struct character playercharacter;
	struct magic playermagic;
	struct armor playerarmor;
	struct classes playerclass;
	struct jobs playerjob;
};

#endif

