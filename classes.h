#ifndef __CLASSES_H
#define __CLASSES_H

struct classes
{
	int player;
	int side;
	char *type_of_class[CLASSAMOUNT];
	char *switchable_to[CLASSAMOUNT];
};

#endif

