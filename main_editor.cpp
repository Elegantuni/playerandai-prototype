#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

//#include "player.h"
//#include "aicharacter.h"

void readfiletest(FILE *fp1);

int main(int argc, char *argv[])
{
	FILE *fp1;
	
	if(argc > 1 && (strcmp(argv[1], "-f") == 0))
	{
		const int filenamesize = 100;
		
		char buffer1[filenamesize];

		snprintf(buffer1, filenamesize - 1, "%s", argv[2]);
		
		fp1 = fopen(buffer1, "r");
	}
	else
	{
		fp1 = fopen("Config/playerandai-prototype-version-2.txt", "r");
	}
	
	return 0;
}

void readfiletest(FILE *fp1)
{
	const int arbsize = 1000;

	char buffer1[arbsize];
	
	size_t thereturnsize;
	
	while((thereturnsize = fread(buffer1, 1, arbsize, fp1)) > 0)
	{
		printf("%s", buffer1);
	}
}

