#ifndef __ARMOR_H
#define __ARMOR_H

struct armor
{
	char *equiped;
	int protection;
	int rangey;
	int rangex;
	int protections[ARMORAMOUNT];
	char *item[allarmor];
	int randomarmor[ARMORAMOUNT];
	int armorcount;
};

#endif

