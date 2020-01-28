#ifndef __MAGIC_H
#define __MAGIC_H

struct magic
{
	char* equiped;
	int damage;
	int randommagic[MAGICAMOUNT];
	int rangey;
	int rangex;
	int cost;
	char* magicitems[MAGICAMOUNT];
	int magiccount;
};

#endif

