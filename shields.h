#ifndef __SHIELDS_H
#define __SHIELDS_H

#include "globaldefs.h"

struct shields
{
	char* equiped;
	char* item[SHIELDAMOUNT];
	int damage;
	int numberitems;
	int randomshield[SHIELDAMOUNT];
	int shieldcount;
};

#endif

