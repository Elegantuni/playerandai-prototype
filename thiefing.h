#ifndef __THIEFING_H
#define __THIEFING_H

#include "globaldefs.h"

struct thiefing
{
	int x; // If x < 0 then it is on the player or enemy
	int y; // If y < 0 then it is on the player or enemy
	int health;
	int to_be_stolen_from_percentage[THIEFINGITEMAMOUNT];
	int is_able_to_steal;
	int amount_able_steal;
	char* what_able_steal[THIEFINGITEMAMOUNT];
	char* what_others_steal[THIEFINGITEMAMOUNT];
};

#endif

