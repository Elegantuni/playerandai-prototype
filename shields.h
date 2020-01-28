#ifndef __SHIELDS_H
#define __SHIELDS_H

struct shields
{
	char* equiped;
	char* item[ALLDEFENSEITEMS];
	int damage;
	int numberitems;
	int randomshield[SHIELDAMOUNT];
	int shieldcount;
};

#endif

