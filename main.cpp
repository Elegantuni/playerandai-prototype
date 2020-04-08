#ifdef INITWINDOWSNOW
#include <curses.h>
#include "fileexists.h"
#endif

#ifdef INITOPENSSL
#include "seed.h"
#endif

#ifdef INITNCURSESNOW2
#include <ncurses.h>
#endif

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

#ifdef INITNCURSESNOW2
#include <unistd.h>
#endif

#ifdef INITLIBTCODNOW
#include <unistd.h>
#endif

#ifdef INITMSYS2NOW
#include <unistd.h>
#endif

#include "str2int.h"

#include <stdio.h>

#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#ifdef FREEBSD
#include "freebsddepends.h"
#endif

#ifdef INITNCURSESNOW
#define RETURNTYPEVIDEO intptr_t
#endif

#ifdef INITLIBTCODNOW
#define RETURNTYPEVIDEO char
#endif

#include "alldefines.h"

#include "initvideo.h"

#include "ncursesinput.h"

#include "inputcompare.h"

#include "inputgetter.h"

#include "inputmove.h"

#include "screenclear.h"

#include "screenrefresh.h"

#include "ncursesprint.h"

#include "ncursesprintarg1.h"

#include "ncursesprintarg2.h"

#include "ncursesprintstats.h"

#include "videoprinternorm.h"

#include "videoprinterarg1.h"

#include "videoprinterarg2.h"

#include "videoprinterstats.h"

#include "magic.h"

#include "magicenemies.h"

#include "character.h"

#include "shieldsdamage.h"

#include "shieldsdamageenemies.h"

#include "shields.h"

#include "shieldsenemies.h"

#include "weaponsdamage.h"

#include "weaponsdamageenemies.h"

#include "weapons.h"

#include "weaponsenemies.h"

#include "hitpointspos.h"

#include "armor.h"

#include "armorenemies.h"

#include "player.h"

#include "aicharacter.h"

#include "writestring.h"

#include "writenumber.h"

#include "loadnumber.h"

#include "loadstring.h"

int main(int argc, char *argv[])
{
	int maxenemies1 = 0;
	int maxplayers1 = 0;

	int hitpointsy = 24;
	int hitpointsx = 80;

	long theseed;
	char *digest = (char *)malloc(sizeof(char) * 33);

	int commandlineset = 0;
	int rounds = 1;

	int twoplayers = 0;
	int whosturn = 0;

	if(argc >= 3 && strcmp(argv[2], "1") == 0)
	{
			  twoplayers = 1;
	}

	if(argc >= 2)
	{
#ifdef INITOPENSSL
		char *end;
		int sizeofthis = 0;

		while (argv[1][sizeofthis] != '\0')
		{
			sizeofthis++;
		}

		digest = str2md5(argv[1], sizeofthis);

		theseed = strtol(digest, &end, 10);
		#ifdef OPENBSD
			srand_deterministic(theseed);
		#endif
#endif
	}
	else
	{
		theseed = 0;	
	}

	#ifdef INITNCURSESNOW2

	int row;
	int col;

	initscr();
	getmaxyx(stdscr, row, col);
	endwin();

	if(row < hitpointsy)
	{
		printf("Change your terminal row to %d or greater\n", hitpointsy);

	   return 1;
	}

	if(col < hitpointsx)
	{
		printf("Change your terminal col to %d or greater\n", hitpointsx);

	   return 1;
	}

	#endif

	#ifdef INITWINDOWSNCURSES
		hitpointsy = 24;
		hitpointsx = 120;
	#endif

	#ifdef INITLIBTCODNOW
		hitpointsy = 24;
		hitpointsx = 120;
	#endif

#if defined(_MSC_VER)
                if(!fileExists("Data/SaveFile.txt"))
#else
                if(access("Data/SaveFile.txt", F_OK ) == -1)
#endif
                {
	while(maxplayers1 < 10 || maxplayers1 > 1000000)
	{
		printf("Enter the amount of ai you want to face (10 - 1000000). You will have to use in bash ulimit -s unlimited for values above 7000 probably: ");
		
		fflush(stdout);
		
		scanf("%d", &maxplayers1);
	}

	rounds = 1;
	
	while(rounds < 10 || rounds > 1000000)
	{
		printf("Enter the amount of rounds you want to play (10 - 1000000).  If you want a real acheivemnet choose 50 or greater: ");
		
		fflush(stdout);

		scanf("%d", &rounds);
	}
	}

#if defined(_MSC_VER)
                if(fileExists("Data/SaveFile.txt"))
#else
                if(access("Data/SaveFile.txt", F_OK ) != -1)
#endif
 		{
			FILE *fp11 = fopen("Data/SaveFile.txt", "r");
			int temp1;
			loadnumber(128, &temp1, fp11);
			maxplayers1 = static_cast<long>(temp1);
			loadnumber(128, &commandlineset, fp11);
			loadnumber(128, &temp1, fp11);
			theseed = static_cast<long>(temp1);

			fclose(fp11);
		}
	
	const int maxenemies2 = maxplayers1;
	const int maxplayers2 = maxplayers1;

	#define maxenemies maxenemies2
	#define maxplayers maxplayers2
	#define playermagiclist allmagics
	#define aimagiclist allmagicsenemies
	
#if defined(_MSC_VER)
	int lineamount = 128;
#else
	#define lineamount 128
#endif

	int terminalend = (maxenemies + maxplayers) * 3;
	int terminalendx = 140;
	
	int savefile = 0;

	int positiony = 0;
	int positionx = 0;

	if(maxenemies < 1)
	{
		printf("You need maxenemies set to 1 or greater\n");
		
		return 1;
	}
	
	if(maxplayers < 1)
	{
		printf("You need maxplayers set to 1 or greater\n");
		
		return 1;
	}
	
	FILE *fp1;
#if defined(_MSC_VER)
	char lineBuffer[128];
	lineamount = 128;
#else
	char lineBuffer[lineamount];
#endif
	ssize_t len = 0;

	for(int j = 0; j < lineamount; j++)
	{
		lineBuffer[j] = '\0';
	}

	int roundssofar = 1;

	#ifdef INITNCURSESNOW

	int ch;

	ch = 'l';
	
	#endif

	#ifdef INITLIBTCODNOW

	char ch;
	
	ch = 'l';

	TCOD_key_t key;
	
	#endif

	if(commandlineset == 1 || argc == 2)
	{
#ifndef OPENBSD
		srand(theseed);
#endif
		commandlineset = 1;
	}
	else
	{
		srand(time(NULL));
	}

beginning:

	while(roundssofar <= rounds && ch != 'y')
	{
#ifndef INITWINDOWSNOW
		struct player myplayer[maxplayers];
		struct aicharacter myai[maxenemies];
#else
		struct player *myplayer = (struct player *) malloc(sizeof(struct player) * maxplayers);
		struct aicharacter *myai = (struct aicharacter *) malloc(sizeof(struct aicharacter) * maxenemies);
#endif

		for(int i = 0; i < maxplayers; i++)
		{
			myplayer[i].weapon = (char*)malloc(sizeof(char) * lineamount);
			myplayer[i].shield = (char*)malloc(sizeof(char) * lineamount);
			myplayer[i].charactersign = (char*)malloc(sizeof(char) * lineamount);
		}

		for(int i = 0; i < maxenemies; i++)
		{
			myai[i].weapon = (char*)malloc(sizeof(char) * lineamount);

			myai[i].shield = (char*)malloc(sizeof(char) * lineamount);

			myai[i].charactersign = (char*)malloc(sizeof(char) * lineamount);
		}

		for(int i = 0; i < maxplayers; i++)
		{
			for(int j = 0; j < WEAPONSAMOUNT; j++)
			{
				myplayer[i].playerweapons.item[j] = (char*)malloc(sizeof(char) * lineamount);
				myplayer[i].playerweapons.durability[j] = (char*)malloc(sizeof(char) * lineamount);
			}
		}

		for(int i = 0; i < maxplayers; i++)
		{
			myplayer[i].playerweaponsdamage.item = (char*)malloc(sizeof(char) * lineamount);
		}

		for(int i = 0; i < maxplayers; i++)
		{
			for(int j = 0; j < STATUSEFFECTSAMOUNT; j++)
			{
				myplayer[i].playerweapons.statuseffects[j] = (char*)malloc(sizeof(char) * lineamount);
			}
		}

		for(int i = 0; i < maxplayers; i++)
		{
			myplayer[i].playerweaponsdamage.item = (char*)malloc(sizeof(char) * lineamount);
		}

		for(int i = 0; i < maxplayers; i++)
		{
			for(int j = 0; j < THIEFINGITEMAMOUNT; j++)
			{
				myplayer[i].playerthiefing.what_able_steal[j] = (char*)malloc(sizeof(char) * lineamount);
				myplayer[i].playerthiefing.what_others_steal[j] = (char*)malloc(sizeof(char) * lineamount);
			}
		}

		for(int i = 0; i < maxplayers; i++)
		{
			myplayer[i].playershield.equiped = (char*)malloc(sizeof(char) * lineamount);
			
			for(int j = 0; j < SHIELDAMOUNT; j++)
			{
				myplayer[i].playershield.item[j] = (char*)malloc(sizeof(char) * lineamount);
				
				myplayer[i].playershield.randomshield[j] = (char*)malloc(sizeof(char) * lineamount);
			}
		}

		for(int i = 0; i < maxplayers; i++)
		{
			myplayer[i].playershielddamage.item = (char*)malloc(sizeof(char) * lineamount);
			
			myplayer[i].playershielddamage.damage = (int*)malloc(sizeof(int) * allitems);
		}

		for(int i = 0; i < maxplayers; i++)
		{
			myplayer[i].playercharacter.character = (char*)malloc(sizeof(char) * lineamount);
			
			myplayer[i].playercharacter.sign = (char*)malloc(sizeof(char) * lineamount);
		}

		for(int i = 0; i < maxplayers; i++)
		{
			myplayer[i].playermagic.equiped = (char*)malloc(sizeof(char) * lineamount);

			for(int j = 0; j < MAGICAMOUNT; j++)
			{
				myplayer[i].playermagic.magicitems[j] = (char*)malloc(sizeof(char) * lineamount);
			}
		}

		for(int i = 0; i < maxplayers; i++)
		{
			myplayer[i].playerarmor.equiped = (char*)malloc(sizeof(char) * lineamount);

			for(int j = 0; j < ARMORAMOUNT; j++)
			{
				myplayer[i].playerarmor.item[j] = (char*)malloc(sizeof(char) * lineamount);
			}
		}

		for(int i = 0; i < maxplayers; i++)
		{
			for(int j = 0; j < CLASSAMOUNT; j++)
			{
				myplayer[i].playerclass.type_of_class[j] = (char*)malloc(sizeof(char) * lineamount);

				myplayer[i].playerclass.switchable_to[j] = (char*)malloc(sizeof(char) * lineamount);
			}
		}

		for(int i = 0; i < maxenemies; i++)
		{
			myai[i].aiweapons.equiped = (char*)malloc(sizeof(char) * lineamount);

			for(int j = 0; j < allitemsenemies; j++)
			{
				myai[i].aiweapons.item[j] = (char*)malloc(sizeof(char) * lineamount);
			}
		}

		for(int i = 0; i < maxenemies; i++)
		{
			myai[i].aiweaponsdamage.item = (char*)malloc(sizeof(char) * lineamount);
		}

		for(int i = 0; i < maxenemies; i++)
		{
			for(int j = 0; j < THIEFINGITEMAMOUNT; j++)
			{
				myai[i].aithiefing.what_able_steal[j] = (char*)malloc(sizeof(char) * lineamount);

				myai[i].aithiefing.what_others_steal[j] = (char*)malloc(sizeof(char) * lineamount);
			}
		}

		for(int i = 0; i < maxenemies; i++)
		{
			myai[i].aishield.equiped = (char*)malloc(sizeof(char) * lineamount);

			for(int j = 0; j < SHIELDAMOUNT; j++)
			{
				myai[i].aishield.item[j] = (char*)malloc(sizeof(char) * lineamount);
				
				myai[i].aishield.randomshield[j] = (char*)malloc(sizeof(char) * lineamount);
			}
		}

		for(int i = 0; i < maxenemies; i++)
		{
			myai[i].aishielddamage.item = (char*)malloc(sizeof(char) * lineamount);

			myai[i].aishielddamage.damage = (int*)malloc(sizeof(int) * allitems);
		}

		for(int i = 0; i < maxenemies; i++)
		{
			myai[i].aicharacter.character = (char*)malloc(sizeof(char) * lineamount);

			myai[i].aicharacter.sign = (char*)malloc(sizeof(char) * lineamount);
		}

		for(int i = 0; i < maxenemies; i++)
		{
			myai[i].aimagic.equiped = (char*)malloc(sizeof(char) * lineamount);

			for(int j = 0; j < MAGICAMOUNT; j++)
			{
				myai[i].aimagic.magicitems[j] = (char*)malloc(sizeof(char) * lineamount);
			}
		}

		for(int i = 0; i < maxenemies; i++)
		{
			myai[i].aiarmor.equiped = (char*)malloc(sizeof(char) * lineamount);

			for(int j = 0; j < ARMORAMOUNT; j++)
			{
				myai[i].aiarmor.item[j] = (char*)malloc(sizeof(char) * lineamount);
			}
		}

		for(int i = 0; i < maxenemies; i++)
		{
			for(int j = 0; j < CLASSAMOUNT; j++)
			{
				myai[i].aiclass.type_of_class[j] = (char*)malloc(sizeof(char) * lineamount);

				myai[i].aiclass.switchable_to[j] = (char*)malloc(sizeof(char) * lineamount);
			}
		}

		for(int i = 0; i < maxplayers; i++)
		{
			myplayer[i].playerweapons.damage = 0;
			myplayer[i].playerweapons.rangex = 0;
			myplayer[i].playerweapons.rangey = 0;
		}

		char *item[allitems];

		fp1 = fopen("Data/PLAYERWEAPONS.txt", "r");

		for(int i = 0; i < allitems; i++)
		{
			loadstring(lineamount, &item[i], fp1);
		}

		fclose(fp1);

		char* itemdamage[alldefenseitems];

		fp1 = fopen("Data/PLAYERDEFENSE.txt", "r");

		for(int i = 0; i < alldefenseitems; i++)
		{
			loadstring(lineamount, &itemdamage[i], fp1);
		}

		fclose(fp1);

		char* itemenemies[allitemsenemies];

		if (twoplayers != 1)
		{
			fp1 = fopen("Data/AIWEAPONS.txt", "r");

			for (int i = 0; i < allitemsenemies; i++)
			{
				loadstring(lineamount, &itemenemies[i], fp1);
			}

			fclose(fp1);
		}
		else
		{
			fp1 = fopen("Data/AIWEAPONSPLAYER2.txt", "r");

			for (int i = 0; i < allitemsenemiesplayer2; i++)
			{
				loadstring(lineamount, &itemenemies[i], fp1);
			}

			fclose(fp1);
		}

		char* itemdamageenemies[alldefenseitemsenemies];
		
		fp1 = fopen("Data/AIDEFENSE.txt", "r");

		for(int i = 0; i < alldefenseitemsenemies; i++)
		{
			loadstring(lineamount, &itemdamageenemies[i], fp1);
		}

		fclose(fp1);

		int* damage = (int *)malloc(sizeof(int) * allitems);

		fp1 = fopen("Data/PLAYERWEAPONSDAMAGE.txt", "r");

		for(int i = 0; i < allitems; i++)
		{
			loadnumber(lineamount, &damage[i], fp1);
		}

		fclose(fp1);

		int* rangey = (int *)malloc(sizeof(int) * allitems);

		fp1 = fopen("Data/PLAYERWEAPONSRANGEY.txt", "r");

		for(int i = 0; i < allitems; i++)
		{
			loadnumber(lineamount, &rangey[i], fp1);
		}

		fclose(fp1);

		int* rangex = (int *)malloc(sizeof(int) * allitems);

		fp1 = fopen("Data/PLAYERWEAPONSRANGEX.txt", "r");

		for(int i = 0; i < allitems; i++)
		{
			loadnumber(lineamount, &rangex[i], fp1);
		}

		fclose(fp1);

		int* damageenemies = (int *)malloc(sizeof(int) * allitemsenemies);

		fp1 = fopen("Data/AIWEAPONSDAMAGE.txt", "r");

		if (twoplayers != 1)
		{
			for (int i = 0; i < allitemsenemies; i++)
			{
				loadnumber(lineamount, &damageenemies[i], fp1);
			}
		}
		else
		{
			for (int i = 0; i < allitemsenemiesplayer2; i++)
			{
				loadnumber(lineamount, &damageenemies[i], fp1);
			}
		}

		fclose(fp1);

		int* rangeyenemies = (int *)malloc(sizeof(int) * allitemsenemies);

		fp1 = fopen("Data/AIWEAPONSRANGEY.txt", "r");

		if (twoplayers != 1)
		{
			for (int i = 0; i < allitemsenemies; i++)
			{
				loadnumber(lineamount, &rangeyenemies[i], fp1);
			}

			fclose(fp1);
		}
		else
		{
			for (int i = 0; i < allitemsenemiesplayer2; i++)
			{
				loadnumber(lineamount, &rangeyenemies[i], fp1);
			}

			fclose(fp1);
		}

		int* rangexenemies = (int *)malloc(sizeof(int) * allitemsenemies);

		fp1 = fopen("Data/AIWEAPONSRANGEX.txt", "r");

		if (twoplayers != 1)
		{
			for (int i = 0; i < allitemsenemies; i++)
			{
				loadnumber(lineamount, &rangexenemies[i], fp1);
			}

			fclose(fp1);
		}
		else
		{
			for (int i = 0; i < allitemsenemiesplayer2; i++)
			{
				loadnumber(lineamount, &rangexenemies[i], fp1);
			}

			fclose(fp1);
		}

		int* shielddamage = (int *)malloc(sizeof(int) * alldefenseitems);

		fp1 = fopen("Data/PLAYERSHIELDDAMAGE.txt", "r");

		for(int i = 0; i < alldefenseitems; i++)
		{
			loadnumber(lineamount, &shielddamage[i], fp1);
		}

		fclose(fp1);

		int* shielddamageenemies = (int *)malloc(sizeof(int) * alldefenseitemsenemies);

		fp1 = fopen("Data/AISHIELDDAMAGE.txt", "r");

		for(int i = 0; i < alldefenseitemsenemies; i++)
		{
			loadnumber(lineamount, &shielddamageenemies[i], fp1);
		}

		fclose(fp1);

		char* playercharacter1[playercharacters];

		fp1 = fopen("Data/PLAYERCHARACTER.txt", "r");

		for(int i = 0; i < playercharacters; i++)
		{
			loadstring(lineamount, &playercharacter1[i], fp1);
		}

		fclose(fp1);

		char* aicharacter1[aicharacters];

		fp1 = fopen("Data/AICHARACTER.txt", "r");

		for(int i = 0; i < aicharacters; i++)
		{
			loadstring(lineamount, &aicharacter1[i], fp1);
		}

		fclose(fp1);

		char* playersigns[playercharacters];

		fp1 = fopen("Data/PLAYERSIGN.txt", "r");

		for(int i = 0; i < playercharacters; i++)
		{
			loadstring(lineamount, &playersigns[i], fp1);
		}

		fclose(fp1);

		char* aisigns[aicharacters];

		fp1 = fopen("Data/AISIGN.txt", "r");

		for(int i = 0; i < aicharacters; i++)
		{
			loadstring(lineamount, &aisigns[i], fp1);
		}

		fclose(fp1);

		int playerhitpoints[playercharacters];

		fp1 = fopen("Data/PLAYERHITPOINTS.txt", "r");

		for(int i = 0; i < playercharacters; i++)
		{
			loadnumber(lineamount, &playerhitpoints[i], fp1);
		}

		fclose(fp1);

		int aihitpoints[aicharacters];

		fp1 = fopen("Data/AIHITPOINTS.txt", "r");

		for(int i = 0; i < aicharacters; i++)
		{
			loadnumber(lineamount, &aihitpoints[i], fp1);
		}

		fclose(fp1);

		int playerdefense[playercharacters];

		fp1 = fopen("Data/PLAYERDEFENSEVALUES.txt", "r");

		for(int i = 0; i < playercharacters; i++)
		{
			loadnumber(lineamount, &playerdefense[i], fp1);
		}

		fclose(fp1);

		int aidefense[aicharacters];

		fp1 = fopen("Data/AIDEFENSEVALUES.txt", "r");

		for(int i = 0; i < aicharacters; i++)
		{
			loadnumber(lineamount, &aidefense[i], fp1);
		}

		fclose(fp1);

		int playerattack[playercharacters];

		fp1 = fopen("Data/PLAYERATTACK.txt", "r");

		for(int i = 0; i < playercharacters; i++)
		{
			loadnumber(lineamount, &playerattack[i], fp1);
		}

		fclose(fp1);

		int aiattack[aicharacters];

		fp1 = fopen("Data/AIATTACK.txt", "r");

		for(int i = 0; i < aicharacters; i++)
		{
			loadnumber(lineamount, &aiattack[i], fp1);
		}

		fclose(fp1);

		char* playermagicitems[playermagiclist];
		
		fp1 = fopen("Data/PLAYERMAGICS.txt", "r");

		for(int i = 0; i < playermagiclist; i++)
		{
			loadstring(lineamount, &playermagicitems[i], fp1);
		}

		fclose(fp1);

		char* aimagicitems[aimagiclist];
		
		fp1 = fopen("Data/AIMAGICS.txt", "r");

		for(int i = 0; i < aimagiclist; i++)
		{
			loadstring(lineamount, &aimagicitems[i], fp1);
		}

		fclose(fp1);

		int playermagicdamage[playermagiclist];
		
		fp1 = fopen("Data/PLAYERMAGICSDAMAGE.txt", "r");

		for(int i = 0; i < playermagiclist; i++)
		{
			loadnumber(lineamount, &playermagicdamage[i], fp1);
		}

		fclose(fp1);

		int aimagicdamage[aimagiclist];
		
		fp1 = fopen("Data/AIMAGICSDAMAGE.txt", "r");

		for(int i = 0; i < aimagiclist; i++)
		{
			loadnumber(lineamount, &aimagicdamage[i], fp1);
		}

		fclose(fp1);

		int playermagicdistance[playermagiclist];
		
		fp1 = fopen("Data/PLAYERMAGICSDISTANCE.txt", "r");

		for(int i = 0; i < playermagiclist; i++)
		{
			loadnumber(lineamount, &playermagicdistance[i], fp1);
		}

		fclose(fp1);

		int aimagicdistance[aimagiclist];

		fp1 = fopen("Data/AIMAGICSDISTANCE.txt", "r");

		for(int i = 0; i < aimagiclist; i++)
		{
			loadnumber(lineamount, &aimagicdistance[i], fp1);
		}

		fclose(fp1);

		int playermagicresist[playercharacters];

		fp1 = fopen("Data/PLAYERMAGICRESISTANCE.txt", "r");

		for(int i = 0; i < playercharacters; i++)
		{
			loadnumber(lineamount, &playermagicresist[i], fp1);
		}

		fclose(fp1);

		int aimagicresist[aicharacters];

		fp1 = fopen("Data/AIMAGICRESISTANCE.txt", "r");

		for(int i = 0; i < aicharacters; i++)
		{
			loadnumber(lineamount, &aimagicresist[i], fp1);
		}

		fclose(fp1);

		int playermagicpoints[playercharacters];

		fp1 = fopen("Data/PLAYERMAGICPOINTS.txt", "r");

		for(int i = 0; i < playercharacters; i++)
		{
			loadnumber(lineamount, &playermagicpoints[i], fp1);
		}

		fclose(fp1);

		int aimagicpoints[aicharacters];

		fp1 = fopen("Data/AIMAGICPOINTS.txt", "r");

		for(int i = 0; i < aicharacters; i++)
		{
			loadnumber(lineamount, &aimagicpoints[i], fp1);
		}

		fclose(fp1);

		int playermagiccost[playermagiclist];

		fp1 = fopen("Data/PLAYERMAGICSCOST.txt", "r");

		for(int i = 0; i < playermagiclist; i++)
		{
			loadnumber(lineamount, &playermagiccost[i], fp1);
		}

		fclose(fp1);

		int aimagiccost[aimagiclist];
		
		fp1 = fopen("Data/AIMAGICSCOST.txt", "r");

		for(int i = 0; i < aimagiclist; i++)
		{
			loadnumber(lineamount, &aimagiccost[i], fp1);
		}

		fclose(fp1);

		char* playerarmor[allarmor];

		fp1 = fopen("Data/PLAYERARMOR.txt", "r");

		for(int i = 0; i < allarmor; i++)
		{
			loadstring(lineamount, &playerarmor[i], fp1);
		}

		fclose(fp1);

		char* aiarmor[allarmorenemies];

		fp1 = fopen("Data/AIARMOR.txt", "r");

		for(int i = 0; i < allarmorenemies; i++)
		{
			loadstring(lineamount, &aiarmor[i], fp1);
		}

		fclose(fp1);

		int playerarmorpts[allarmor];
		
		fp1 = fopen("Data/PLAYERARMORPOINTS.txt", "r");

		for(int i = 0; i < allarmor; i++)
		{
			loadnumber(lineamount, &playerarmorpts[i], fp1);
		}

		fclose(fp1);

		int aiarmorpts[allarmorenemies];
		
		fp1 = fopen("Data/AIARMORPOINTS.txt", "r");

		for(int i = 0; i < allarmorenemies; i++)
		{
			loadnumber(lineamount, &aiarmorpts[i], fp1);
		}

		fclose(fp1);

		int playerarmordistancex[allarmor];

		fp1 = fopen("Data/PLAYERARMORDISTANCEX.txt", "r");

		for(int i = 0; i < allarmor; i++)
		{
			loadnumber(lineamount, &playerarmordistancex[i], fp1);
		}

		fclose(fp1);

		int aiarmordistancex[allarmorenemies];

		fp1 = fopen("Data/AIARMORDISTANCEX.txt", "r");

		for(int i = 0; i < allarmorenemies; i++)
		{
			loadnumber(lineamount, &aiarmordistancex[i], fp1);
		}

		fclose(fp1);

		int playerarmordistancey[allarmor];
		
		fp1 = fopen("Data/PLAYERARMORDISTANCEY.txt", "r");

		for(int i = 0; i < allarmor; i++)
		{
			loadnumber(lineamount, &playerarmordistancey[i], fp1);
		}

		fclose(fp1);

		int aiarmordistancey[allarmorenemies];
		
		fp1 = fopen("Data/AIARMORDISTANCEY.txt", "r");

		for(int i = 0; i < allarmorenemies; i++)
		{
			loadnumber(lineamount, &aiarmordistancey[i], fp1);
		}

		fclose(fp1);

		for(int i = 0; i < maxplayers; i++)
		{
			myplayer[i].randomitem = rand() % allitems;
		}
	
		for (int i = 0; i < maxenemies; i++)
		{
			if (twoplayers != 1)
			{
				myai[i].randomitem = rand() % allitemsenemies;
			}
			else
			{
				myai[i].randomitem = rand() % allitemsenemiesplayer2;
			}
		}

		for(int i = 0; i < maxplayers; i++)
		{
			myplayer[i].shieldsrandomitem = rand() % alldefenseitems;
		}

		for(int i = 0; i < maxenemies; i++)
		{
			myai[i].shieldsrandomitem = rand() % alldefenseitemsenemies;
		}

		for(int i = 0; i < maxplayers; i++)
		{
			myplayer[i].playercharacter.randomcharacter = rand() % playercharacters;
		}

		for(int i = 0; i < maxenemies; i++)
		{
			myai[i].aicharacter.randomcharacter = rand() % aicharacters;
		}

		for(int i = 0; i < maxplayers; i++)
		{
			for(int j = 0; j < MAGICAMOUNT; j++)
			{
				myplayer[i].playermagic.randommagic[j] = rand() % playermagiclist;
			}
		}

		for(int i = 0; i < maxenemies; i++)
		{
			for(int j = 0; j < MAGICAMOUNT; j++)
			{
				myai[i].aimagic.randommagic[j] = rand() % aimagiclist;
			}
		}

		for(int i = 0; i < maxplayers; i++)
		{
			for(int j = 0; j < ARMORAMOUNT; j++)
			{
				myplayer[i].playerarmor.randomarmor[j] = rand() % allarmor;
			}
		}

		for(int i = 0; i < maxenemies; i++)
		{
			for(int j = 0; j < ARMORAMOUNT; j++)
			{
				myai[i].aiarmor.randomarmor[j] = rand() % allarmorenemies;
			}
		}

		for(int i = 0; i < maxplayers; i++)
		{
			for(int j = 0; j < WEAPONSAMOUNT; j++)
			{
				myplayer[i].playerweapons.randomweapon[j] = rand() % allitems;
			}
		}

		for(int i = 0; i < maxplayers; i++)
		{
			for(int j = 0; j < SHIELDAMOUNT; j++)
			{
				myplayer[i].playershield.randomshield[j] = rand() % alldefenseitems;
			}
		}

		for(int i = 0; i < maxplayers; i++)
		{
			for(int j = 0; j < MAGICAMOUNT; j++)
			{
				myplayer[i].playermagic.magicitems[j] = const_cast<char *>("Empty");
			}

			for(int j = 0; j < WEAPONSAMOUNT; j++)
			{
				myplayer[i].playerweapons.item[j] = const_cast<char *>("Empty");
			}

			for(int j = 0; j < SHIELDAMOUNT; j++)
			{
				myplayer[i].playershield.item[j] = const_cast<char *>("Empty");
			}

			for(int j = 0; j < ARMORAMOUNT; j++)
			{
				myplayer[i].playerarmor.item[j] = const_cast<char *>("Empty");
			}
			
			myplayer[i].thenumber = i + 1;
			myplayer[i].y = 10;
			myplayer[i].x = 12;
			myplayer[i].hitpoints = 1000;
			myplayer[i].magicpoints = 1000;
			myplayer[i].defensepoints = 20;
			myplayer[i].weapon = const_cast<char *>("Knife");
			myplayer[i].shield = const_cast<char *>("LargeShield");
			myplayer[i].charactersign = const_cast<char *>("@");
			myplayer[i].prevy = 10;
			myplayer[i].prevx = 12;
			myplayer[i].magicattack = 100;
			myplayer[i].count = i+1;
			myplayer[i].replayer =  0;
			myplayer[i].playerturn = 0;

			for(int j = 0; j < WEAPONSAMOUNT; j++)
			{
				myplayer[i].playerweapons.equiped = const_cast<char *>("NULL");
			}
			
			myplayer[i].playercharacter.character = playercharacter1[myplayer[i].playercharacter.randomcharacter];
			myplayer[i].playercharacter.sign = playersigns[myplayer[i].playercharacter.randomcharacter];
			myplayer[i].playercharacter.hitpoints = playerhitpoints[myplayer[i].playercharacter.randomcharacter];
			myplayer[i].playercharacter.defense = playerdefense[myplayer[i].playercharacter.randomcharacter];
			myplayer[i].playercharacter.attack = playerattack[myplayer[i].playercharacter.randomcharacter];

			for(int j = 0; j < WEAPONSAMOUNT; j++)
			{
				myplayer[i].playerweapons.item[j] = item[myplayer[i].randomitem];
			}
			
			myplayer[i].charactersign = myplayer[i].playercharacter.sign;
			myplayer[i].defensepoints = myplayer[i].playercharacter.defense;
			myplayer[i].hitpoints = myplayer[i].playercharacter.hitpoints;

			myplayer[i].playermagic.magiccount = 0;

			myplayer[i].playerweapons.damage = damage[myplayer[i].randomitem];
			myplayer[i].playerweapons.rangey = rangey[myplayer[i].randomitem];
			myplayer[i].playerweapons.rangex = rangex[myplayer[i].randomitem];
			myplayer[i].playerweapons.numberitems = allitems;

			for(int j = 0; j < allitems; j++)
			{
				myplayer[i].playerweaponsdamage.damage[j] = damage[j];
				myplayer[i].playerweaponsdamage.rangey[j] = rangey[j];
				myplayer[i].playerweaponsdamage.rangex[j] = rangex[j];
			}

			myplayer[i].playershield.equiped = itemdamage[myplayer[i].shieldsrandomitem];

			myplayer[i].shield = myplayer[i].playershield.equiped;

			myplayer[i].playershield.damage = shielddamage[myplayer[i].shieldsrandomitem];
			myplayer[i].playershield.numberitems = alldefenseitems;

			myplayer[i].playershielddamage.item = itemdamage[myplayer[i].shieldsrandomitem];

			for(int j = 0; j < alldefenseitems; j++)
			{
				myplayer[i].playershielddamage.damage[j] = shielddamage[j];
			}

			myplayer[i].playermagic.equiped = playermagicitems[myplayer[i].playermagic.randommagic[0]];
			myplayer[i].playermagic.rangey = playermagicdistance[myplayer[i].playermagic.randommagic[0]];
			myplayer[i].playermagic.rangex = playermagicdistance[myplayer[i].playermagic.randommagic[0]];
			myplayer[i].playermagic.damage = playermagicdamage[myplayer[i].playermagic.randommagic[0]];

			myplayer[i].magicattack = myplayer[i].playermagic.damage;

			myplayer[i].playercharacter.magicresist = playermagicresist[myplayer[i].playercharacter.randomcharacter];

			myplayer[i].magicpoints = playermagicpoints[myplayer[i].playercharacter.randomcharacter];

			myplayer[i].playermagic.cost = playermagiccost[myplayer[i].playermagic.randommagic[0]];

			myplayer[i].playerweapons.numberitems = allitems;

			myplayer[i].playermagic.magicitems[myplayer[i].playermagic.magiccount] = playermagicitems[myplayer[i].playermagic.randommagic[0]];
			
			myplayer[i].playermagic.magiccount++;

			myplayer[i].playermagic.randommagic[1] = myplayer[i].playermagic.randommagic[0];

			while(myplayer[i].playermagic.randommagic[1] == myplayer[i].playermagic.randommagic[0])
			{
				myplayer[i].playermagic.randommagic[1] = rand() % playermagiclist;
			}

			myplayer[i].playermagic.magicitems[myplayer[i].playermagic.magiccount] = playermagicitems[myplayer[i].playermagic.randommagic[1]];

			myplayer[i].playermagic.magiccount++;

			myplayer[i].playermagic.randommagic[2] = myplayer[i].playermagic.randommagic[0];

			while(myplayer[i].playermagic.randommagic[2] == myplayer[i].playermagic.randommagic[0] || myplayer[i].playermagic.randommagic[2] == myplayer[i].playermagic.randommagic[1])
			{
				myplayer[i].playermagic.randommagic[2] = rand() % playermagiclist;
			}

			myplayer[i].playermagic.magicitems[myplayer[i].playermagic.magiccount] = playermagicitems[myplayer[i].playermagic.randommagic[2]];

			myplayer[i].playermagic.magiccount++;

			myplayer[i].playerweapons.weaponcount = 0;

			myplayer[i].playerweapons.randomweapon[0] = myplayer[i].randomitem;

			myplayer[i].playerweapons.item[myplayer[i].playerweapons.weaponcount] = item[myplayer[i].playerweapons.randomweapon[0]];

			myplayer[i].playerweapons.weaponcount++;

			myplayer[i].playerweapons.randomweapon[1] = myplayer[i].playerweapons.randomweapon[0];

			while(myplayer[i].playerweapons.randomweapon[1] == myplayer[i].playerweapons.randomweapon[0])
			{
				myplayer[i].playerweapons.randomweapon[1] = rand() % allitems;
			}

			myplayer[i].playerweapons.item[myplayer[i].playerweapons.weaponcount] = item[myplayer[i].playerweapons.randomweapon[1]];

			myplayer[i].playerweapons.equiped = item[myplayer[i].playerweapons.randomweapon[0]];

			myplayer[i].weapon = myplayer[i].playerweapons.equiped;

			myplayer[i].playerweapons.weaponcount++;

			myplayer[i].playerweapons.randomweapon[2] = myplayer[i].playerweapons.randomweapon[0];

			while(myplayer[i].playerweapons.randomweapon[2] == myplayer[i].playerweapons.randomweapon[1] || myplayer[i].playerweapons.randomweapon[2] == myplayer[i].playerweapons.randomweapon[0])
			{
				myplayer[i].playerweapons.randomweapon[2] = rand() % allitems;
			}

			myplayer[i].playerweapons.item[myplayer[i].playerweapons.weaponcount] = item[myplayer[i].playerweapons.randomweapon[2]];

			myplayer[i].playerweapons.weaponcount++;

			myplayer[i].playershield.shieldcount = 0;

			myplayer[i].playershield.randomshield[0] = myplayer[i].shieldsrandomitem;

			myplayer[i].playershield.item[myplayer[i].playershield.shieldcount] = itemdamage[myplayer[i].playershield.randomshield[0]];

			myplayer[i].playershield.equiped = myplayer[i].playershield.item[0];

			myplayer[i].playershield.shieldcount++;

			myplayer[i].playershield.randomshield[1] = myplayer[i].playershield.randomshield[0];

			while(myplayer[i].playershield.randomshield[1] == myplayer[i].playershield.randomshield[0])
			{
				myplayer[i].playershield.randomshield[1] = rand() % alldefenseitems;
			}

			myplayer[i].playershield.item[myplayer[i].playershield.shieldcount] = itemdamage[myplayer[i].playershield.randomshield[1]];

			myplayer[i].playershield.shieldcount++;

			myplayer[i].playershield.randomshield[2] = myplayer[i].playershield.randomshield[0];

			while(myplayer[i].playershield.randomshield[2] == myplayer[i].playershield.randomshield[1] || myplayer[i].playershield.randomshield[2] == myplayer[i].playershield.randomshield[0])
			{
				myplayer[i].playershield.randomshield[2] = rand() % alldefenseitems;
			}

			myplayer[i].playershield.item[myplayer[i].playershield.shieldcount] = itemdamage[myplayer[i].playershield.randomshield[2]];

			myplayer[i].playershield.shieldcount++;

			myplayer[i].playerarmor.armorcount = 0;

			myplayer[i].playerarmor.item[myplayer[i].playerarmor.armorcount] = playerarmor[myplayer[i].playerarmor.randomarmor[0]];

			myplayer[i].playerarmor.armorcount++;

			myplayer[i].playerarmor.randomarmor[1] = myplayer[i].playerarmor.randomarmor[0];

			while(myplayer[i].playerarmor.randomarmor[1] == myplayer[i].playerarmor.randomarmor[0])
			{
				myplayer[i].playerarmor.randomarmor[1] = rand() % allarmor;
			}

			myplayer[i].playerarmor.item[myplayer[i].playerarmor.armorcount] = playerarmor[myplayer[i].playerarmor.randomarmor[1]];

			myplayer[i].playerarmor.armorcount++;

			myplayer[i].playerarmor.randomarmor[2] = myplayer[i].playerarmor.randomarmor[0];

			while(myplayer[i].playerarmor.randomarmor[2] == myplayer[i].playerarmor.randomarmor[1] || myplayer[i].playerarmor.randomarmor[2] == myplayer[i].playerarmor.randomarmor[0])
			{
				myplayer[i].playerarmor.randomarmor[2] = rand() % allarmor;
			}

			myplayer[i].playerarmor.item[myplayer[i].playerarmor.armorcount] = playerarmor[myplayer[i].playerarmor.randomarmor[2]];

			myplayer[i].playerarmor.armorcount++;

			for (int j = 0; j < allarmor; j++)
			{
				myplayer[i].playerarmor.protections[j] = playerarmorpts[j];
			}

			myplayer[i].playerarmor.rangey = playerarmordistancey[myplayer[i].playerarmor.randomarmor[0]];

			myplayer[i].playerarmor.rangex = playerarmordistancex[myplayer[i].playerarmor.randomarmor[0]];

			myplayer[i].playerarmor.protection = playerarmorpts[myplayer[i].playerarmor.randomarmor[0]];

			myplayer[i].playerarmor.equiped = playerarmor[myplayer[i].playerarmor.randomarmor[0]];
		}

		for(int i = 0; i < maxplayers; i++)
		{
			for(int j = 1; j < maxplayers; j++)
			{
				if(i != j && myplayer[i].y == myplayer[j].y && myplayer[i].x == myplayer[j].x)
				{
					myplayer[j].y = rand() % (terminalend - (maxplayers + maxenemies));
					myplayer[j].x = rand() % (terminalendx - 1);

					myplayer[j].prevy = myplayer[j].y;
					myplayer[j].prevx = myplayer[j].x;
				
					i = -1;
					j = j - 1;

					break;
				}
			}
		}

		for(int i = 0; i < maxenemies; i++)
		{
			for(int j = 0; j < allmagicsenemies; j++)
			{
				myai[i].aimagic.magicitems[j] = const_cast<char *>("Empty");
			}

			for(int j = 0; j < allitemsenemies; j++)
			{
				myai[i].aiweapons.item[j] = const_cast<char *>("Empty");
			}

			for(int j = 0; j < alldefenseitemsenemies; j++)
			{
				myai[i].aishield.item[j] = const_cast<char *>("Empty");
			}

			for(int j = 0; j < allarmorenemies; j++)
			{
				myai[i].aiarmor.item[j] = const_cast<char *>("Empty");
			}

			myai[i].y = 10;
			myai[i].x = 70;
			myai[i].hitpoints = 500;
			myai[i].magicpoints = 500;
			myai[i].defensepoints = 20;
			myai[i].weapon = const_cast<char *>("Gun");
			myai[i].shield = const_cast<char *>("SmallShield");
			myai[i].charactersign = const_cast<char *>("a");
			myai[i].prevy = 10;
			myai[i].prevx = 70;
			myai[i].magicattack = 40;
			myai[i].count = i+1;
			myai[i].replayer =  0;
			myai[i].playerturn = 0;
			myai[i].aiweapons.equiped = const_cast<char *>("NULL");

			myai[i].thenumber = i + 1;
			myai[i].aicharacter.character = aicharacter1[myai[i].aicharacter.randomcharacter];
			myai[i].aicharacter.sign = aisigns[myai[i].aicharacter.randomcharacter];
			myai[i].aicharacter.hitpoints = aihitpoints[myai[i].aicharacter.randomcharacter];
			myai[i].aicharacter.defense = aidefense[myai[i].aicharacter.randomcharacter];
			myai[i].aicharacter.attack = aiattack[myai[i].aicharacter.randomcharacter];

			myai[i].aiweaponsdamage.item = itemenemies[myai[i].randomitem];

			myai[i].charactersign = myai[i].aicharacter.sign;
			myai[i].defensepoints = myai[i].aicharacter.defense;
			myai[i].hitpoints = myai[i].aicharacter.hitpoints;

			myai[i].aiweapons.damage = damageenemies[myai[i].randomitem];
			myai[i].aiweapons.rangey = rangeyenemies[myai[i].randomitem];
			myai[i].aiweapons.rangex = rangexenemies[myai[i].randomitem];

			for(int j = 0; j < allitemsenemies; j++)
			{
				myai[i].aiweaponsdamage.damage[j] = damageenemies[j];
				myai[i].aiweaponsdamage.rangey[j] = rangeyenemies[j];
				myai[i].aiweaponsdamage.rangex[j] = rangexenemies[j];
			}

			myai[i].aishield.equiped = itemdamageenemies[myai[i].shieldsrandomitem];

			myai[i].shield = myai[i].aishield.equiped;

			myai[i].aishield.damage = shielddamageenemies[myai[i].shieldsrandomitem];
			myai[i].aishield.numberitems = alldefenseitemsenemies;

			myai[i].aishielddamage.item = itemdamageenemies[myai[i].shieldsrandomitem];

			myai[i].aimagic.magiccount = 0;

			myai[i].aimagic.equiped = aimagicitems[myai[i].aimagic.randommagic[0]];
			myai[i].aimagic.rangey = aimagicdistance[myai[i].aimagic.randommagic[0]];
			myai[i].aimagic.rangex = aimagicdistance[myai[i].aimagic.randommagic[0]];
			myai[i].aimagic.damage = aimagicdamage[myai[i].aimagic.randommagic[0]];

			myai[i].magicattack = myai[i].aimagic.damage;

			myai[i].aicharacter.magicresist = aimagicresist[myai[i].aicharacter.randomcharacter];

			myai[i].magicpoints = aimagicpoints[myai[i].aicharacter.randomcharacter];
		
			myai[i].aimagic.cost = aimagiccost[myai[i].aimagic.randommagic[0]];

			if (twoplayers != 1)
			{
				myai[i].aiweapons.numberitems = allitemsenemies;
			}
			else
			{
				myai[i].aiweapons.numberitems = allitemsenemiesplayer2;
			}

			myai[i].aiarmor.equiped = aiarmor[myai[i].aiarmor.randomarmor[0]];

			myai[i].aiarmor.protection = aiarmorpts[myai[i].aiarmor.randomarmor[0]];

			myai[i].aiarmor.rangey = aiarmordistancey[myai[i].aiarmor.randomarmor[0]];

			myai[i].aiarmor.rangex = aiarmordistancex[myai[i].aiarmor.randomarmor[0]];

			/*
			for(int j = 0; j < allitemsenemies; j++)
			{
				myai[i].aiweaponsdamage.damage[j] = damageenemies[j];
				myai[i].aiweaponsdamage.rangey[j] = rangeyenemies[j];
				myai[i].aiweaponsdamage.rangex[j] = rangexenemies[j];
			}
			*/

			for(int j = 0; j < alldefenseitemsenemies; j++)
			{
				myai[i].aishielddamage.damage[j] = shielddamageenemies[j];
			}

			for(int j = 0; j < allarmorenemies; j++)
			{
				myai[i].aiarmor.protections[j] = aiarmorpts[j];
			}

			myai[i].aimagic.magiccount = 0;

			myai[i].aimagic.magicitems[myai[i].aimagic.magiccount] = aimagicitems[myai[i].aimagic.randommagic[0]];

			myai[i].aimagic.randommagic[1] = myai[i].aimagic.randommagic[0];

			myai[i].aimagic.magiccount++;

			while(myai[i].aimagic.randommagic[1] == myai[i].aimagic.randommagic[0])
			{
				myai[i].aimagic.randommagic[1] = rand() % allmagicsenemies;
			}

			myai[i].aimagic.magicitems[myai[i].aimagic.magiccount] = aimagicitems[myai[i].aimagic.randommagic[1]];

			myai[i].aimagic.magiccount++;

			myai[i].aimagic.randommagic[2] = myai[i].aimagic.randommagic[0];

			while(myai[i].aimagic.randommagic[2] == myai[i].aimagic.randommagic[1] || myai[i].aimagic.randommagic[2] == myai[i].aimagic.randommagic[0])
			{
				myai[i].aimagic.randommagic[2] = rand() % allmagicsenemies;
			}

			myai[i].aimagic.magicitems[myai[i].aimagic.magiccount] = aimagicitems[myai[i].aimagic.randommagic[2]];

			myai[i].aimagic.magiccount++;

			myai[i].aiarmor.armorcount = 0;

			myai[i].aiarmor.item[myai[i].aiarmor.armorcount] = aiarmor[myai[i].aiarmor.randomarmor[0]];
			
			myai[i].aiarmor.armorcount++;

			myai[i].aiarmor.randomarmor[1] = myai[i].aiarmor.randomarmor[0];

			while(myai[i].aiarmor.randomarmor[1] == myai[i].aiarmor.randomarmor[0])
			{
				myai[i].aiarmor.randomarmor[1] = rand() % allarmorenemies;
			}

			myai[i].aiarmor.item[myai[i].aiarmor.armorcount] = aiarmor[myai[i].aiarmor.randomarmor[1]];

			myai[i].aiarmor.armorcount++;

			myai[i].aiarmor.randomarmor[2] = myai[i].aiarmor.randomarmor[0];

			while(myai[i].aiarmor.randomarmor[2] == myai[i].aiarmor.randomarmor[1] || myai[i].aiarmor.randomarmor[2] == myai[i].aiarmor.randomarmor[0])
			{
				myai[i].aiarmor.randomarmor[2] = rand() % allarmorenemies;
			}
			
			myai[i].aiarmor.item[myai[i].aiarmor.armorcount] = aiarmor[myai[i].aiarmor.randomarmor[2]];

			myai[i].aiarmor.armorcount++;

			myai[i].aishield.shieldcount = 0;

			myai[i].aishield.randomshield[0] = myai[i].shieldsrandomitem;

			myai[i].aishield.item[myai[i].aishield.shieldcount] = itemdamageenemies[myai[i].aishield.randomshield[0]];

			myai[i].aishield.shieldcount++;

			myai[i].aishield.randomshield[1] = myai[i].aishield.randomshield[0];

			while(myai[i].aishield.randomshield[1] == myai[i].aishield.randomshield[0])
			{
				myai[i].aishield.randomshield[1] = rand() % alldefenseitemsenemies;
			}

			myai[i].aishield.item[myai[i].aishield.shieldcount] = itemdamageenemies[myai[i].aishield.randomshield[1]];

			myai[i].aishield.shieldcount++;

			myai[i].aishield.randomshield[2] = myai[i].aishield.randomshield[0];

			while(myai[i].aishield.randomshield[2] == myai[i].aishield.randomshield[1] || myai[i].aishield.randomshield[2] == myai[i].aishield.randomshield[0])
			{
				myai[i].aishield.randomshield[2] = rand() % alldefenseitemsenemies;
			}

			myai[i].aishield.item[myai[i].aishield.shieldcount] = itemdamageenemies[myai[i].aishield.randomshield[2]];

			myai[i].aishield.shieldcount++;

			myai[i].aiweapons.weaponcount = 0;

			myai[i].aiweapons.randomweapon[0] = myai[i].randomitem;

			myai[i].aiweapons.item[myai[i].aiweapons.weaponcount] = itemenemies[myai[i].aiweapons.randomweapon[0]];

			myai[i].aiweapons.equiped = itemenemies[myai[i].aiweapons.randomweapon[0]];

			myai[i].weapon = myai[i].aiweapons.equiped;

			myai[i].aiweapons.weaponcount++;

			myai[i].aiweapons.randomweapon[1] = myai[i].aiweapons.randomweapon[0];

			while(myai[i].aiweapons.randomweapon[1] == myai[i].aiweapons.randomweapon[0])
			{
				if (twoplayers != 1)
				{
					myai[i].aiweapons.randomweapon[1] = rand() % allitemsenemies;
				}
				else
				{
					myai[i].aiweapons.randomweapon[1] = rand() % allitemsenemiesplayer2;
				}
			}

			myai[i].aiweapons.item[myai[i].aiweapons.weaponcount] = itemenemies[myai[i].aiweapons.randomweapon[1]];

			myai[i].aiweapons.weaponcount++;

			myai[i].aiweapons.randomweapon[2] = myai[i].aiweapons.randomweapon[0];

			while(myai[i].aiweapons.randomweapon[2] == myai[i].aiweapons.randomweapon[1] || myai[i].aiweapons.randomweapon[2] == myai[i].aiweapons.randomweapon[0])
			{
				if (twoplayers != 1)
				{
					myai[i].aiweapons.randomweapon[2] = rand() % allitemsenemies;
				}
				else
				{
					myai[i].aiweapons.randomweapon[2] = rand() % allitemsenemiesplayer2;
				}
			}

			myai[i].aiweapons.item[myai[i].aiweapons.weaponcount] = itemenemies[myai[i].aiweapons.randomweapon[2]];

			myai[i].aiweapons.weaponcount++;
		}

		for(int i = 0; i < maxenemies; i++)
		{
			for(int j = 1; j < maxenemies; j++)
			{
				if(i != j && myai[i].y == myai[j].y && myai[i].x == myai[j].x)
				{
					myai[j].y = rand() % (terminalend - (maxplayers + maxenemies));
					myai[j].x = rand() % (terminalendx - 1);
				
					myai[j].prevy = myai[j].y;
					myai[j].prevx = myai[j].x;
				
					i = -1;
					j = j - 1;

					break;
				}
			}

			for(int j = 0; j < maxplayers; j++)
			{
				if(myai[i].y == myplayer[j].y && myai[i].x == myplayer[j].x)
				{
					myai[i].y = rand() % (terminalend - (maxplayers + maxenemies));
					myai[i].x = rand() % (terminalendx - 1);

					myai[i].prevy = myai[i].y;
					myai[i].prevx = myai[i].x;
				
					i = -1;
					j = -1;

					break;
				}
			}
		}

		/*
		for(int i = 0; i < maxenemies; i++)
		{
			myai[i].weapontype.equiped = myai[i].weapontype.item[myai[i].randomitem];
		}
		*/
		
#if defined(_MSC_VER)
		if(fileExists("Data/SaveFile.txt"))
#else
		if(access("Data/SaveFile.txt", F_OK ) != -1)
#endif
		{
			int j = 0;
		
			fp1 = fopen("Data/SaveFile.txt", "r");
			
			for(int i = 0; i < maxplayers; i++)
			{
				loadnumber(lineamount, &maxplayers1, fp1);

				loadnumber(lineamount, &commandlineset, fp1);

				int temp1;
				loadnumber(lineamount, &temp1, fp1);
				theseed = static_cast<long>(temp1);

				loadnumber(lineamount, &myplayer[i].randomitem, fp1);

				loadnumber(lineamount, &myplayer[i].shieldsrandomitem, fp1);

				loadnumber(lineamount, &myplayer[i].playercharacter.randomcharacter, fp1);

				loadnumber(lineamount, &myplayer[i].playermagic.randommagic[0], fp1);

				loadnumber(lineamount, &myplayer[i].y, fp1);

				loadnumber(lineamount, &myplayer[i].x, fp1);

				loadnumber(lineamount, &myplayer[i].hitpoints, fp1);

				loadnumber(lineamount, &myplayer[i].magicpoints, fp1);

				loadnumber(lineamount, &myplayer[i].defensepoints, fp1);

				loadstring(lineamount, &myplayer[i].weapon, fp1);

				loadstring(lineamount, &myplayer[i].shield, fp1);

				loadstring(lineamount, &myplayer[i].charactersign, fp1);

				loadnumber(lineamount, &myplayer[i].prevy, fp1);

				loadnumber(lineamount, &myplayer[i].prevx, fp1);

				loadnumber(lineamount, &myplayer[i].magicattack, fp1);

				loadnumber(lineamount, &myplayer[i].count, fp1);

				loadnumber(lineamount, &myplayer[i].replayer, fp1);

				loadnumber(lineamount, &myplayer[i].playerturn, fp1);

				loadstring(lineamount, &myplayer[i].playerweapons.equiped, fp1);

				loadstring(lineamount, &myplayer[i].playercharacter.character, fp1);

				loadstring(lineamount, &myplayer[i].playercharacter.sign, fp1);

				loadnumber(lineamount, &myplayer[i].playercharacter.hitpoints, fp1);

				loadnumber(lineamount, &myplayer[i].playercharacter.defense, fp1);

				loadnumber(lineamount, &myplayer[i].playercharacter.attack, fp1);

				loadstring(lineamount, &myplayer[i].playerweaponsdamage.item, fp1);

				loadnumber(lineamount, &myplayer[i].defensepoints, fp1);

				loadnumber(lineamount, &myplayer[i].hitpoints, fp1);

				for(int q = 0; q < allitems; q++)
				{
					loadstring(lineamount, &myplayer[i].playerweapons.item[q], fp1);
				}

				loadnumber(lineamount, &myplayer[i].playerweapons.damage, fp1);

				loadnumber(lineamount, &myplayer[i].playerweapons.rangey, fp1);

				loadnumber(lineamount, &myplayer[i].playerweapons.rangex, fp1);

				loadnumber(lineamount, &myplayer[i].playerweapons.numberitems, fp1);

				for(int q = 0; q < allitems; q++)
				{
					loadnumber(lineamount, &myplayer[i].playerweaponsdamage.damage[q], fp1);
				}

				for(int q = 0; q < allitems; q++)
				{
					loadnumber(lineamount, &myplayer[i].playerweaponsdamage.rangey[q], fp1);
				}

				for(int q = 0; q < allitems; q++)
				{
					loadnumber(lineamount, &myplayer[i].playerweaponsdamage.rangex[q], fp1);
				}

				for(int q = 0; q < alldefenseitems; q++)
				{
					loadstring(lineamount, &myplayer[i].playershield.item[q], fp1);
				}

				loadstring(lineamount, &myplayer[i].playershield.equiped, fp1);

				loadnumber(lineamount, &myplayer[i].playershield.damage, fp1);

				loadnumber(lineamount, &myplayer[i].playershield.numberitems, fp1);

				loadstring(lineamount, &myplayer[i].playershielddamage.item, fp1);

				for(int q = 0; q < alldefenseitems; q++)
				{
					loadnumber(lineamount, &myplayer[i].playershielddamage.damage[q], fp1);
				}

				loadstring(lineamount, &myplayer[i].playermagic.equiped, fp1);

				loadnumber(lineamount, &myplayer[i].playermagic.rangey, fp1);

				loadnumber(lineamount, &myplayer[i].playermagic.rangex, fp1);

				loadnumber(lineamount, &myplayer[i].playermagic.damage, fp1);

				loadnumber(lineamount, &myplayer[i].magicattack, fp1);

				loadnumber(lineamount, &myplayer[i].playercharacter.magicresist, fp1);

				loadnumber(lineamount, &myplayer[i].magicpoints, fp1);

				loadnumber(lineamount, &myplayer[i].playermagic.cost, fp1);

				loadnumber(lineamount, &myplayer[i].playerweapons.numberitems, fp1);

				loadstring(lineamount, &myplayer[i].playerweapons.equiped, fp1);

				loadnumber(lineamount, &myplayer[i].playermagic.magiccount, fp1);

				loadnumber(lineamount, &myplayer[i].playermagic.randommagic[1], fp1);
				
				for(int l = 0; l < allmagics; l++)
				{
					loadstring(lineamount, &myplayer[i].playermagic.magicitems[l], fp1);
				}

				loadnumber(lineamount, &myplayer[i].playermagic.randommagic[2], fp1);

				loadnumber(lineamount, &myplayer[i].playerweapons.randomweapon[0], fp1);

				loadnumber(lineamount, &myplayer[i].playerweapons.randomweapon[1], fp1);

				loadnumber(lineamount, &myplayer[i].playerweapons.randomweapon[2], fp1);

				for(int l = 0; l < allitems; l++)
				{
					loadstring(lineamount, &myplayer[i].playerweapons.item[l], fp1);
				}

				loadnumber(lineamount, &myplayer[i].playershield.randomshield[0], fp1);

				loadnumber(lineamount, &myplayer[i].playershield.randomshield[1], fp1);

				loadnumber(lineamount, &myplayer[i].playershield.randomshield[2], fp1);

				for(int l = 0; l < alldefenseitems; l++)
				{
					loadstring(lineamount, &myplayer[i].playershield.item[l], fp1);
				}

				loadnumber(lineamount, &myplayer[i].playerarmor.randomarmor[0], fp1);
				
				loadnumber(lineamount, &myplayer[i].playerarmor.randomarmor[1], fp1);
				
				loadnumber(lineamount, &myplayer[i].playerarmor.randomarmor[2], fp1);
				
				loadstring(lineamount, &myplayer[i].playerarmor.equiped, fp1);
				
				loadnumber(lineamount, &myplayer[i].playerarmor.rangey, fp1);
				
				loadnumber(lineamount, &myplayer[i].playerarmor.rangex, fp1);
				
				loadnumber(lineamount, &myplayer[i].playerarmor.protection, fp1);
				
				for(int q = 0; q < allarmor; q++)
				{
					loadstring(lineamount, &myplayer[i].playerarmor.item[q], fp1);
				}
				
				for(int q = 0; q < allarmor; q++)
				{
					loadnumber(lineamount, &myplayer[i].playerarmor.protections[q], fp1);
				}
				
				loadnumber(lineamount, &myplayer[i].playerweapons.weaponcount, fp1);
				
				loadnumber(lineamount, &myplayer[i].playershield.shieldcount, fp1);
				
				loadnumber(lineamount, &myplayer[i].playerarmor.armorcount, fp1);

				loadnumber(lineamount, &myplayer[i].thenumber, fp1);
			}
		
			for(int i = 0; i < maxenemies; i++)
			{
				loadnumber(lineamount, &myai[i].randomitem, fp1);

				loadnumber(lineamount, &myai[i].shieldsrandomitem, fp1);

				loadnumber(lineamount, &myai[i].aicharacter.randomcharacter, fp1);

				loadnumber(lineamount, &myai[i].aimagic.randommagic[0], fp1);

				loadnumber(lineamount, &myai[i].y, fp1);

				loadnumber(lineamount, &myai[i].x, fp1);

				loadnumber(lineamount, &myai[i].hitpoints, fp1);

				loadnumber(lineamount, &myai[i].magicpoints, fp1);

				loadnumber(lineamount, &myai[i].defensepoints, fp1);

				loadstring(lineamount, &myai[i].weapon, fp1);

				loadstring(lineamount, &myai[i].shield, fp1);

				loadstring(lineamount, &myai[i].charactersign, fp1);

				loadnumber(lineamount, &myai[i].prevy, fp1);

				loadnumber(lineamount, &myai[i].prevx, fp1);

				loadnumber(lineamount, &myai[i].magicattack, fp1);

				loadnumber(lineamount, &myai[i].count, fp1);

				loadnumber(lineamount, &myai[i].replayer, fp1);

				loadnumber(lineamount, &myai[i].playerturn, fp1);

				loadstring(lineamount, &myai[i].aiweapons.equiped, fp1);

				loadstring(lineamount, &myai[i].aicharacter.character, fp1);

				loadstring(lineamount, &myai[i].aicharacter.sign, fp1);

				loadnumber(lineamount, &myai[i].aicharacter.hitpoints, fp1);

				loadnumber(lineamount, &myai[i].aicharacter.defense, fp1);

				loadnumber(lineamount, &myai[i].aicharacter.attack, fp1);

				loadstring(lineamount, &myai[i].aiweaponsdamage.item, fp1);

				loadnumber(lineamount, &myai[i].defensepoints, fp1);

				loadnumber(lineamount, &myai[i].hitpoints, fp1);

				for (int q = 0; q < allitemsenemies; q++)
				{
					loadstring(lineamount, &myai[i].aiweapons.item[q], fp1);
				}

				loadnumber(lineamount, &myai[i].aiweapons.damage, fp1);

				loadnumber(lineamount, &myai[i].aiweapons.rangey, fp1);

				loadnumber(lineamount, &myai[i].aiweapons.rangex, fp1);

				loadnumber(lineamount, &myai[i].aiweapons.numberitems, fp1);

				for (int q = 0; q < allitemsenemies; q++)
				{
					loadnumber(lineamount, &myai[i].aiweaponsdamage.damage[q], fp1);
				}
	
				for (int q = 0; q < allitemsenemies; q++)
				{
					loadnumber(lineamount, &myai[i].aiweaponsdamage.rangey[q], fp1);
				}

				for (int q = 0; q < allitemsenemies; q++)
				{
					loadnumber(lineamount, &myai[i].aiweaponsdamage.rangex[q], fp1);
				}

				for(int q = 0; q < alldefenseitemsenemies; q++)
				{
					loadstring(lineamount, &myai[i].aishield.item[q], fp1);
				}

				loadstring(lineamount, &myai[i].aishield.equiped, fp1);

				loadnumber(lineamount, &myai[i].aishield.damage, fp1);

				loadnumber(lineamount, &myai[i].aishield.numberitems, fp1);

				loadstring(lineamount, &myai[i].aishielddamage.item, fp1);

				for(int q = 0; q < alldefenseitemsenemies; q++)
				{
					loadnumber(lineamount, &myai[i].aishielddamage.damage[q], fp1);
				}

				loadstring(lineamount, &myai[i].aimagic.equiped, fp1);

				loadnumber(lineamount, &myai[i].aimagic.rangey, fp1);

				loadnumber(lineamount, &myai[i].aimagic.rangex, fp1);

				loadnumber(lineamount, &myai[i].aimagic.damage, fp1);

				loadnumber(lineamount, &myai[i].magicattack, fp1);

				loadnumber(lineamount, &myai[i].aicharacter.magicresist, fp1);

				loadnumber(lineamount, &myai[i].magicpoints, fp1);

				loadnumber(lineamount, &myai[i].aimagic.cost, fp1);

				loadnumber(lineamount, &myai[i].aiweapons.numberitems, fp1);

				loadstring(lineamount, &myai[i].aiweapons.equiped, fp1);

				loadnumber(lineamount, &myai[i].aimagic.magiccount, fp1);
				
				loadnumber(lineamount, &myai[i].aimagic.randommagic[1], fp1);
								
				for(int l = 0; l < allmagicsenemies; l++)
				{
					loadstring(lineamount, &myai[i].aimagic.magicitems[l], fp1);
				}
				
				loadnumber(lineamount, &myai[i].aimagic.randommagic[2], fp1);
				
				loadnumber(lineamount, &myai[i].aiweapons.randomweapon[0], fp1);
				
				loadnumber(lineamount, &myai[i].aiweapons.randomweapon[1], fp1);
				
				loadnumber(lineamount, &myai[i].aiweapons.randomweapon[2], fp1);
				
				for (int l = 0; l < allitemsenemies; l++)
				{
					loadstring(lineamount, &myai[i].aiweapons.item[l], fp1);
				}

				loadnumber(lineamount, &myai[i].aishield.randomshield[0], fp1);
				
				loadnumber(lineamount, &myai[i].aishield.randomshield[1], fp1);
				
				loadnumber(lineamount, &myai[i].aishield.randomshield[2], fp1);
				
				for(int l = 0; l < alldefenseitemsenemies; l++)
				{
					loadstring(lineamount, &myai[i].aishield.item[l], fp1);
				}
				
				loadnumber(lineamount, &myai[i].aiarmor.randomarmor[0], fp1);
								
				loadnumber(lineamount, &myai[i].aiarmor.randomarmor[1], fp1);
								
				loadnumber(lineamount, &myai[i].aiarmor.randomarmor[2], fp1);
								
				loadstring(lineamount, &myai[i].aiarmor.equiped, fp1);
								
				loadnumber(lineamount, &myai[i].aiarmor.rangey, fp1);
								
				loadnumber(lineamount, &myai[i].aiarmor.rangex, fp1);
								
				loadnumber(lineamount, &myai[i].aiarmor.protection, fp1);
								
				for(int q = 0; q < allarmorenemies; q++)
				{
					loadstring(lineamount, &myai[i].aiarmor.item[q], fp1);
				}
								
				for(int q = 0; q < allarmorenemies; q++)
				{
					loadnumber(lineamount, &myai[i].aiarmor.protections[q], fp1);
				}
								
				loadnumber(lineamount, &myai[i].aiweapons.weaponcount, fp1);
								
				loadnumber(lineamount, &myai[i].aishield.shieldcount, fp1);
								
				loadnumber(lineamount, &myai[i].aiarmor.armorcount, fp1);

				loadnumber(lineamount, &myai[i].thenumber, fp1);
			}

			loadnumber(lineamount, &roundssofar, fp1);

			loadnumber(lineamount, &positiony, fp1);

			loadnumber(lineamount, &rounds, fp1);

			loadnumber(lineamount, &positionx, fp1);
		
			loadnumber(lineamount, &twoplayers, fp1);

			loadnumber(lineamount, &whosturn, fp1);

			fclose(fp1);

			remove("Data/SaveFile.txt");
			
			savefile = 1;
		}
	
		char* winner = const_cast<char *>("ai");
	
		int replayer = 0;
	
		int positionxdiff;
	
		int positionydiff;
	
		struct hitpointspos hitpointspos1 = { terminalend - (maxplayers + maxenemies), 0, terminalend - (maxenemies), terminalendx};
	
		initvideo(hitpointsy, hitpointsx);

#ifdef INITLIBTCODNOW
	TCOD_console_set_default_foreground(NULL, TCOD_color_RGB(255, 255, 255));
	TCOD_console_set_default_background(NULL, TCOD_color_RGB(0, 0, 0));
#endif

		positiony = (myplayer[0].y / hitpointsy) * hitpointsy;
		positionx = (myplayer[0].x / hitpointsx) * hitpointsx;

		if(positiony > 0)
		{
			positiony++;
		}

		if(positionx > 0)
		{
			positionx++;
		}
	
		for(int i = 0; i < maxplayers; i++)
		{
			if(myplayer[i].hitpoints > 0 && myplayer[i].y >= (positiony - hitpointsy) && myplayer[i].x >= (positionx - hitpointsx))
			{
				videoprinternorm(myplayer[i].y - positiony, myplayer[i].x - positionx, myplayer[i].charactersign);
			}
		}
	
		for(int i = 0; i < maxenemies; i++)
		{
			if(myai[i].hitpoints > 0 && myai[i].y >= (positiony - hitpointsy) && myai[i].x >= (positionx - hitpointsx))
			{
				   videoprinternorm(myai[i].y - positiony, myai[i].x - positionx, myai[i].charactersign);
			}
		}
	
		for(int i = 0; i < maxplayers; i++)
		{
			if((hitpointspos1.y + i) > positiony)
			{
				videoprinterstats(hitpointspos1.y + i - positiony, 0, "Player %d is %s hp:%d mp:%d at:%d ma:%s %d def:%d w:%s sh:%s ar:%s md:%d", myplayer[i].count, myplayer[i].playercharacter.character, myplayer[i].hitpoints, myplayer[i].magicpoints, myplayer[i].playerweapons.damage + myplayer[i].playercharacter.attack, myplayer[i].playermagic.equiped, myplayer[i].playermagic.damage, myplayer[i].defensepoints + myplayer[i].playershield.damage, myplayer[i].playerweapons.equiped, myplayer[i].playershield.equiped, myplayer[i].playerarmor.equiped, myplayer[i].playerarmor.protection);
			}
		}

		for(int i = 0; i < maxenemies; i++)
		{
			if((hitpointspos1.ay + i) >= (positiony) && (positiony > (maxenemies)))
			{
				videoprinterstats(hitpointspos1.ay + i - positiony, 0, "AI %d is %s hp:%d mp:%d at:%d ma:%s %d def:%d w:%s sh:%s ar:%s md:%d", myai[i].count, myai[i].aicharacter.character, myai[i].hitpoints, myai[i].magicpoints, myai[i].aiweapons.damage + myai[i].aicharacter.attack, myai[i].aimagic.equiped, myai[i].aimagic.damage, myai[i].defensepoints + myai[i].aishield.damage, myai[i].aiweapons.equiped, myai[i].aishield.equiped, myai[i].aiarmor.equiped, myai[i].aiarmor.protection);
			}
		}
		
		if(whosturn == 0)
		{
			inputmove(myplayer[0].y - positiony, myplayer[0].x - positionx);
		}

		if(whosturn == 1)
		{
			inputmove(myai[0].y - positiony, myai[0].x - positionx);
		}
		screenrefresh();

		int i = 0;
		int iai = 0;

		while((ch = (RETURNTYPEVIDEO)inputgetter()) != 'q')
		{
			if(inputcompare(ch, 'x'))
			{
				screenclear();

				videoprinternorm(0, 0, "Saving now and then exiting");

				screenrefresh();

				fp1 = fopen("Data/SaveFile.txt", "w");

				for(int i = 0; i < maxplayers; i++)
				{
					writenumber(lineBuffer, lineamount, maxplayers1, fp1);

					writenumber(lineBuffer, lineamount, commandlineset, fp1);

					writenumber(lineBuffer, lineamount, theseed, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].randomitem, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].shieldsrandomitem, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playercharacter.randomcharacter, fp1);
					
					writenumber(lineBuffer, lineamount, myplayer[i].playermagic.randommagic[0], fp1);
				
					writenumber(lineBuffer, lineamount, myplayer[i].y, fp1);
					
					writenumber(lineBuffer, lineamount, myplayer[i].x, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].hitpoints, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].magicpoints, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].defensepoints, fp1);

					writestring(lineBuffer, lineamount, myplayer[i].weapon, fp1);

					writestring(lineBuffer, lineamount, myplayer[i].shield, fp1);

					writestring(lineBuffer, lineamount, myplayer[i].charactersign, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].prevy, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].prevx, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].magicattack, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].count, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].replayer, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playerturn, fp1);

					writestring(lineBuffer, lineamount, myplayer[i].playerweapons.equiped, fp1);

					writestring(lineBuffer, lineamount, myplayer[i].playercharacter.character, fp1);

					writestring(lineBuffer, lineamount, myplayer[i].playercharacter.sign, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playercharacter.hitpoints, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playercharacter.defense, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playercharacter.attack, fp1);

					writestring(lineBuffer, lineamount, myplayer[i].playerweaponsdamage.item, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].defensepoints, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].hitpoints, fp1);

					for(int q = 0; q < allitems; q++)
					{
						writestring(lineBuffer, lineamount, myplayer[i].playerweapons.item[q], fp1);
						
					}

					writenumber(lineBuffer, lineamount, myplayer[i].playerweapons.damage, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playerweapons.rangey, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playerweapons.rangex, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playerweapons.numberitems, fp1);

					for(int q = 0; q < allitems; q++)
					{
						writenumber(lineBuffer, lineamount, myplayer[i].playerweaponsdamage.damage[q], fp1);
					}

					for(int q = 0; q < allitems; q++)
					{
						writenumber(lineBuffer, lineamount, myplayer[i].playerweaponsdamage.rangey[q], fp1);
					}

					for(int q = 0; q < allitems; q++)
					{
						writenumber(lineBuffer, lineamount, myplayer[i].playerweaponsdamage.rangex[q], fp1);
					}

					for(int q = 0; q < alldefenseitems; q++)
					{
						writestring(lineBuffer, lineamount, myplayer[i].playershield.item[q], fp1);
					}

					writestring(lineBuffer, lineamount, myplayer[i].playershield.equiped, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playershield.damage, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playershield.numberitems, fp1);

					writestring(lineBuffer, lineamount, myplayer[i].playershielddamage.item, fp1);

					for(int q = 0; q < alldefenseitems; q++)
					{
						writenumber(lineBuffer, lineamount, myplayer[i].playershielddamage.damage[q], fp1);
					}

					writestring(lineBuffer, lineamount, myplayer[i].playermagic.equiped, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playermagic.rangey, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playermagic.rangex, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playermagic.damage, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].magicattack, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playercharacter.magicresist, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].magicpoints, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playermagic.cost, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playerweapons.numberitems, fp1);

					writestring(lineBuffer, lineamount, myplayer[i].playerweapons.equiped, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playermagic.magiccount, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playermagic.randommagic[1], fp1);
					
					for(int q = 0; q < allmagics; q++)
					{
						writestring(lineBuffer, lineamount, myplayer[i].playermagic.magicitems[q], fp1);
					}

					writenumber(lineBuffer, lineamount, myplayer[i].playermagic.randommagic[2], fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playerweapons.randomweapon[0], fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playerweapons.randomweapon[1], fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playerweapons.randomweapon[2], fp1);

					for(int q = 0; q < allitems; q++)
					{
						writestring(lineBuffer, lineamount, myplayer[i].playerweapons.item[q], fp1);
					}
					
					writenumber(lineBuffer, lineamount, myplayer[i].playershield.randomshield[0], fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playershield.randomshield[1], fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playershield.randomshield[2], fp1);

					for(int q = 0; q < alldefenseitems; q++)
					{
						writestring(lineBuffer, lineamount, myplayer[i].playershield.item[q], fp1);
					}

					writenumber(lineBuffer, lineamount, myplayer[i].playerarmor.randomarmor[0], fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playerarmor.randomarmor[1], fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playerarmor.randomarmor[2], fp1);

					writestring(lineBuffer, lineamount, myplayer[i].playerarmor.equiped, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playerarmor.rangey, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playerarmor.rangex, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playerarmor.protection, fp1);

					for(int q = 0; q < allarmor; q++)
					{
						writestring(lineBuffer, lineamount, myplayer[i].playerarmor.item[q], fp1);
					}

					for(int q = 0; q < allarmor; q++)
					{
						writenumber(lineBuffer, lineamount, myplayer[i].playerarmor.protections[q], fp1);
					}

					writenumber(lineBuffer, lineamount, myplayer[i].playerweapons.weaponcount, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playershield.shieldcount, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].playerarmor.armorcount, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].thenumber, fp1);
				}

				for(int i = 0; i < maxenemies; i++)
				{
					writenumber(lineBuffer, lineamount, myai[i].randomitem, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].shieldsrandomitem, fp1);

					writenumber(lineBuffer, lineamount, myai[i].aicharacter.randomcharacter, fp1);

					writenumber(lineBuffer, lineamount, myai[i].aimagic.randommagic[0], fp1);
				
					writenumber(lineBuffer, lineamount, myai[i].y, fp1);

					writenumber(lineBuffer, lineamount, myai[i].x, fp1);

					writenumber(lineBuffer, lineamount, myai[i].hitpoints, fp1);

					writenumber(lineBuffer, lineamount, myai[i].magicpoints, fp1);

					writenumber(lineBuffer, lineamount, myai[i].defensepoints, fp1);

					writestring(lineBuffer, lineamount, myai[i].weapon, fp1);

					writestring(lineBuffer, lineamount, myai[i].shield, fp1);

					writestring(lineBuffer, lineamount, myai[i].charactersign, fp1);

					writenumber(lineBuffer, lineamount, myai[i].prevy, fp1);

					writenumber(lineBuffer, lineamount, myai[i].prevx, fp1);

					writenumber(lineBuffer, lineamount, myai[i].magicattack, fp1);

					writenumber(lineBuffer, lineamount, myai[i].count, fp1);

					writenumber(lineBuffer, lineamount, myai[i].replayer, fp1);

					writenumber(lineBuffer, lineamount, myai[i].playerturn, fp1);

					writestring(lineBuffer, lineamount, myai[i].aiweapons.equiped, fp1);

					writestring(lineBuffer, lineamount, myai[i].aicharacter.character, fp1);

					writestring(lineBuffer, lineamount, myai[i].aicharacter.sign, fp1);

					writenumber(lineBuffer, lineamount, myai[i].aicharacter.hitpoints, fp1);

					writenumber(lineBuffer, lineamount, myai[i].aicharacter.defense, fp1);

					writenumber(lineBuffer, lineamount, myai[i].aicharacter.attack, fp1);

					writestring(lineBuffer, lineamount, myai[i].aiweaponsdamage.item, fp1);

					writenumber(lineBuffer, lineamount, myai[i].defensepoints, fp1);

					writenumber(lineBuffer, lineamount, myai[i].hitpoints, fp1);

					for (int q = 0; q < allitemsenemies; q++)
					{
						writestring(lineBuffer, lineamount, myai[i].aiweapons.item[q], fp1);
					}
					
					writenumber(lineBuffer, lineamount, myai[i].aiweapons.damage, fp1);

					writenumber(lineBuffer, lineamount, myai[i].aiweapons.rangey, fp1);

					writenumber(lineBuffer, lineamount, myai[i].aiweapons.rangex, fp1);

					writenumber(lineBuffer, lineamount, myai[i].aiweapons.numberitems, fp1);

					for (int q = 0; q < allitemsenemies; q++)
					{
						writenumber(lineBuffer, lineamount, myai[i].aiweaponsdamage.damage[q], fp1);
					}

					for (int q = 0; q < allitemsenemies; q++)
					{
						writenumber(lineBuffer, lineamount, myai[i].aiweaponsdamage.rangey[q], fp1);
					}

					for (int q = 0; q < allitemsenemies; q++)
					{
						writenumber(lineBuffer, lineamount, myai[i].aiweaponsdamage.rangex[q], fp1);
					}

					for(int q = 0; q < alldefenseitemsenemies; q++)
					{
						writestring(lineBuffer, lineamount, myai[i].aishield.item[q], fp1);
					}

					writestring(lineBuffer, lineamount, myai[i].aishield.equiped, fp1);

					writenumber(lineBuffer, lineamount, myai[i].aishield.damage, fp1);

					writenumber(lineBuffer, lineamount, myai[i].aishield.numberitems, fp1);

					writestring(lineBuffer, lineamount, myai[i].aishielddamage.item, fp1);

					for(int q = 0; q < alldefenseitemsenemies; q++)
					{
						writenumber(lineBuffer, lineamount, myai[i].aishielddamage.damage[q], fp1);
					}

					writestring(lineBuffer, lineamount, myai[i].aimagic.equiped, fp1);

					writenumber(lineBuffer, lineamount, myai[i].aimagic.rangey, fp1);

					writenumber(lineBuffer, lineamount, myai[i].aimagic.rangex, fp1);

					writenumber(lineBuffer, lineamount, myai[i].aimagic.damage, fp1);

					writenumber(lineBuffer, lineamount, myai[i].magicattack, fp1);

					writenumber(lineBuffer, lineamount, myai[i].aicharacter.magicresist, fp1);

					writenumber(lineBuffer, lineamount, myai[i].magicpoints, fp1);

					writenumber(lineBuffer, lineamount, myai[i].aimagic.cost, fp1);

					writenumber(lineBuffer, lineamount, myai[i].aiweapons.numberitems, fp1);

					writestring(lineBuffer, lineamount, myai[i].aiweapons.equiped, fp1);

					writenumber(lineBuffer, lineamount, myai[i].aimagic.magiccount, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].aimagic.randommagic[1], fp1);
										
					for(int q = 0; q < allmagicsenemies; q++)
					{
						writestring(lineBuffer, lineamount, myai[i].aimagic.magicitems[q], fp1);
					}
					
					writenumber(lineBuffer, lineamount, myai[i].aimagic.randommagic[2], fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].aiweapons.randomweapon[0], fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].aiweapons.randomweapon[1], fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].aiweapons.randomweapon[2], fp1);
					
					for (int q = 0; q < allitemsenemies; q++)
					{
						writestring(lineBuffer, lineamount, myai[i].aiweapons.item[q], fp1);
					}

					writenumber(lineBuffer, lineamount, myai[i].aishield.randomshield[0], fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].aishield.randomshield[1], fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].aishield.randomshield[2], fp1);
					
					for(int q = 0; q < alldefenseitemsenemies; q++)
					{
						writestring(lineBuffer, lineamount, myai[i].aishield.item[q], fp1);
					}
					
					writenumber(lineBuffer, lineamount, myai[i].aiarmor.randomarmor[0], fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].aiarmor.randomarmor[1], fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].aiarmor.randomarmor[2], fp1);
					
					writestring(lineBuffer, lineamount, myai[i].aiarmor.equiped, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].aiarmor.rangey, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].aiarmor.rangex, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].aiarmor.protection, fp1);
					
					for(int q = 0; q < allarmorenemies; q++)
					{
						writestring(lineBuffer, lineamount, myai[i].aiarmor.item[q], fp1);
					}
					
					for(int q = 0; q < allarmorenemies; q++)
					{
						writenumber(lineBuffer, lineamount, myai[i].aiarmor.protections[q], fp1);
					}
					
					writenumber(lineBuffer, lineamount, myai[i].aiweapons.weaponcount, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].aishield.shieldcount, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].aiarmor.armorcount, fp1);

					writenumber(lineBuffer, lineamount, myai[i].thenumber, fp1);
				}

				writenumber(lineBuffer, lineamount, roundssofar, fp1);

				writenumber(lineBuffer, lineamount, positiony, fp1);

				writenumber(lineBuffer, lineamount, rounds, fp1);
				
				writenumber(lineBuffer, lineamount, positionx, fp1);

				writenumber(lineBuffer, lineamount, twoplayers, fp1);

				writenumber(lineBuffer, lineamount, whosturn, fp1);

				fclose(fp1);

#ifdef INITNCURSESNOW
				endwin();
#endif

				return 0;
			}

			if(inputcompare(ch, 'h'))
			{
				screenclear();

				videoprinternorm(0, 0, "Press a to move left");
				videoprinternorm(1, 0, "Press d to move right");
				videoprinternorm(2, 0, "Press w to move up");
				videoprinternorm(3, 0, "Press s to move down");
				videoprinternorm(4, 0, "Press m to use magic");
				videoprinternorm(5, 0, "Press b to equip different magic, weapon, shield, and armor");
				videoprinternorm(6, 0, "Press n to cycle through player characters forward");
				videoprinternorm(7, 0, "Press p to cycle through player characters backward");
				videoprinternorm(8, 0, "Press c to see what magics, weapons, shields, and armor you have");
				videoprinternorm(9, 0, "Press i to see what magics, weapons, shields, and armor ai have");
				videoprinternorm(10, 0, "Press h to display this during game to see this screen");
				videoprinternorm(11, 0, "The H is a player human and the h is a ai human");
				videoprinternorm(12, 0, "The O is a player orc and the o is a ai orc");
				videoprinternorm(13, 0, "The E is a player elf and the e is a ai elf");
				videoprinternorm(14, 0, "The D is a player dwarf and the d is a ai elf");
				videoprinternorm(15, 0, "Press q from battle screen to quit game");
				videoprinternorm(16, 0, "Press x to save and quit");
				videoprinternorm(17, 0, "Press u to scroll up");
				videoprinternorm(18, 0, "Press j to scroll down");
				videoprinternorm(19, 0, "Press r to scroll left");
				videoprinternorm(20, 0, "Press f to scroll right");
				videoprinternorm(21, 0, "Press key to quit help");

				screenrefresh();

				(RETURNTYPEVIDEO)inputgetter();

#ifdef INITLIBTCODNOW
				key = TCODConsole::waitForKeypress(true);
#endif

				if(whosturn == 0)
				{
					inputmove(myplayer[i].y, myplayer[i].x);
				}
				
				if(whosturn == 1)
				{
					inputmove(myai[iai].y, myai[iai].x);
				}

				screenrefresh();
			}

			screenclear();


			if(inputcompare(ch, 'p') && whosturn == 0)
			{
				i--;

				if(i < 0)
				{
					i = maxplayers - 1;
				}

				for(int j = 0; j < maxplayers; j++)
				{	
					for(int j = 0; j < maxplayers; j++)
					{
						myplayer[j].playerturn--;
					}
			
					if(i < 0)
					{
						i = maxplayers - 1;
					}
			
					if(myplayer[0].playerturn < 0)
					{
						for(int i = 0; i < maxplayers; i++)
						{
							myplayer[i].playerturn = maxplayers - 1;
						}
					}

					if(myplayer[i].hitpoints > 0)
					{
						positiony = (myplayer[i].y / hitpointsy) * hitpointsy;
						positionx = (myplayer[i].x / hitpointsx) * hitpointsx;

						break;
					}
				
					if(myplayer[i].hitpoints <= 0)
					{
						i--;
					
						if(i < 0)
						{
							i = maxplayers - 1;
						}
					}
				}
			}
			
			if(inputcompare(ch, 'p') && whosturn == 1 && twoplayers == 1)
			{
				iai--;

				if(iai < 0)
				{
						  iai = maxenemies - 1;
				}

				for(int j = 0; j < maxenemies; j++)
				{
						  for(int j = 0; j < maxenemies; j++)
						  {
									 myai[j].playerturn--;
						  }

						  if(iai < 0)
						  {
									 iai = maxenemies - 1;
						  }

						  if(myai[0].playerturn < 0)
						  {
									 for(int i = 0; i < maxenemies; i++)
									 {
												myai[i].playerturn = maxenemies - 1;
									 }
						  }

						  if(myai[iai].hitpoints > 0)
						  {
									 positiony = (myai[iai].y / hitpointsy) * hitpointsy;
									 positionx = (myai[iai].x / hitpointsx) * hitpointsx;

									 break;
						  }

						  if(myai[iai].hitpoints <= 0)
						  {
									 iai--;

									 if(iai < 0)
									 {
												iai = maxenemies - 1;
									 }
						  }
				}
			}
			
			if(inputcompare(ch, 'n') && whosturn == 0)
			{
				i++;
				
				if(i >= maxplayers)
				{
					i = 0;
				}
			
				for(int j = 0; j < maxplayers; j++)
				{	
					for(int j = 0; j < maxplayers; j++)
					{
						myplayer[j].playerturn++;
					}
			
					if(i == maxplayers)
					{
						i = 0;
					}
			
					if(myplayer[0].playerturn == maxplayers)
					{
						for(int i = 0; i < maxplayers; i++)
						{
							myplayer[i].playerturn = 0;
						}
					}

					if(myplayer[i].hitpoints > 0)
					{
						positiony = ((myplayer[i].y) / hitpointsy) * hitpointsy;
						positionx = ((myplayer[i].x) / hitpointsx) * hitpointsx;

						break;
					}
				
					if(myplayer[i].hitpoints <= 0)
					{
						i++;
					
						if(i >= maxplayers)
						{
							i = 0;
						}
					}
				}
			}

			if(inputcompare(ch, 'n') && whosturn == 1 && twoplayers == 1)
			{
				iai++;

				if(iai >= maxenemies)
				{
					iai = 0;
				}

				for(int j = 0; j < maxenemies; j++)
				{
					for(int j = 0; j < maxenemies; j++)
					{
							  myai[j].playerturn++;
					}

					if(iai == maxenemies)
					{
						iai = 0;
					}

					if(myai[0].playerturn == maxenemies)
					{
						for(int i = 0; i < maxenemies; i++)
						{
							myai[i].playerturn = 0;
						}
					}

					if(myai[iai].hitpoints > 0)
					{
						positiony = ((myai[iai].y) / hitpointsy) * hitpointsy;
						positionx = ((myai[iai].x) / hitpointsx) * hitpointsx;

						break;
					}

					if(myai[iai].hitpoints <= 0)
					{
						iai++;

						if(iai >= maxenemies)
						{
							iai = 0;
						}
					}
				}
			}
		
			if(inputcompare(ch, 'a') && whosturn == 0)
			{
				myplayer[i].x = myplayer[i].x - 1;
			
				if(myplayer[i].x < 0)
				{
					myplayer[i].x = 0;
				}

				positionx = ((myplayer[i].x) / hitpointsx) * hitpointsx;
			}

			if(inputcompare(ch, 'a') && whosturn == 1 && twoplayers == 1)
			{
				myai[iai].x = myai[iai].x - 1;

				if(myai[iai].x < 0)
				{
					myai[iai].x = 0;
				}

				positionx = ((myai[iai].x) / hitpointsx) * hitpointsx;
			}
		
			if(inputcompare(ch, 'd') && whosturn == 0)
			{
				myplayer[i].x = myplayer[i].x + 1;
			
				if(myplayer[i].x > hitpointspos1.ax - 1)
				{
					myplayer[i].x = hitpointspos1.ax - 1;
				}

				positionx = ((myplayer[i].x) / hitpointsx) * hitpointsx;
			}

			if(inputcompare(ch, 'd') && whosturn == 1 && twoplayers == 1)
			{
				myai[iai].x = myai[iai].x + 1;

				if(myai[iai].x > hitpointspos1.ax - 1)
				{
					myai[iai].x = hitpointspos1.ax - 1;
				}

				positionx = ((myai[iai].x) / hitpointsx) * hitpointsx;
			}
		
			if(inputcompare(ch, 'w') && whosturn == 0)
			{
				myplayer[i].y = myplayer[i].y - 1;
			
				if(myplayer[i].y < 0)
				{
					myplayer[i].y = 0;
				}

				positiony = ((myplayer[i].y) / hitpointsy) * hitpointsy;
			}

			if(inputcompare(ch, 'w') && whosturn == 1 && twoplayers == 1)
			{
				myai[iai].y = myai[iai].y - 1;

				if(myai[iai].y < 0)
				{
					myai[iai].y = 0;
				}

				positiony = ((myai[iai].y) / hitpointsy) * hitpointsy;
			}

			if(inputcompare(ch, 'u'))
			{
				screenclear();

				positiony--;
				
				if(positiony < 0)
				{
					positiony = 0;
				}

				inputmove(positiony, 0);

				screenrefresh();
			}

			if(inputcompare(ch, 'j'))
			{

				screenclear();

				positiony++;
				
				if(positiony > (terminalend + 1 - hitpointsy))
				{
					positiony = (terminalend + 1 - hitpointsy);
				}

				inputmove(positiony, 0);

				screenrefresh();
			}

			if(inputcompare(ch, 'r'))
			{
				screenclear();

				positionx--;

				if(positionx < 0)
				{
					positionx = 0;
				}

				inputmove(positionx, 0);

				screenrefresh();
			}

			if(inputcompare(ch, 'f'))
			{
				screenclear();

				positionx++;
				
				if(positionx > (terminalendx + 1 - hitpointsx))
				{
					positionx = (terminalendx + 1 - hitpointsx);
				}

				inputmove(positionx, 0);

				screenrefresh();
			}
		
			if(inputcompare(ch, 's') && whosturn == 0)
			{
				myplayer[i].y = myplayer[i].y + 1;
			
				if(myplayer[i].y > (hitpointspos1.y - 1))
				{
					myplayer[i].y = (hitpointspos1.y - 1);
				}

				positiony = ((myplayer[i].y) / hitpointsy) * hitpointsy;
			}

			if(inputcompare(ch, 's') && whosturn == 1 && twoplayers == 1)
			{
				myai[iai].y = myai[iai].y + 1;

				if(myai[iai].y > (hitpointspos1.y - 1))
				{
					myai[iai].y = (hitpointspos1.y - 1);
				}

				positiony = ((myai[iai].y) / hitpointsy) * hitpointsy;
			}

			if (inputcompare(ch, 'c'))
			{
				screenclear();

				int list = 0;
				int l = 0;
#ifdef INITNCURSESNOW
				int gotcharacter = '0';
#endif

#ifdef INITLIBTCODNOW
				char gotcharacter = '0';
#endif
				do
				{
					screenclear();

					if (gotcharacter == 'd')
					{
						list++;
					}

					if (list > 4)
					{
						list = 0;
					}

					videoprinterarg1(l, 0, "Player %d", i + 1);
					l++;

					if (list == 0)
					{
						videoprinterstats(l, 0, "Player %d is %s hp:%d mp:%d at:%d ma:%s %d def:%d w:%s sh:%s ar:%s md:%d", myplayer[i].count, myplayer[i].playercharacter.character, myplayer[i].hitpoints, myplayer[i].magicpoints, myplayer[i].playerweapons.damage + myplayer[i].playercharacter.attack, myplayer[i].playermagic.equiped, myplayer[i].playermagic.damage, myplayer[i].defensepoints + myplayer[i].playershield.damage, myplayer[i].playerweapons.equiped, myplayer[i].playershield.equiped, myplayer[i].playerarmor.equiped, myplayer[i].playerarmor.protection);
						l++;
					}

					if (list == 1)
					{
						while (strcmp(myplayer[i].playermagic.magicitems[l - 1], "Empty") != 0)
						{
							videoprinterarg2(l, 0, "Magic item %d is %s", l, myplayer[i].playermagic.magicitems[l - 1]);
							l++;
						}
					}

					if (list == 2)
					{
						while (strcmp(myplayer[i].playerweapons.item[l - 1], "Empty") != 0)
						{
							videoprinterarg2(l, 0, "Weapon item %d is %s", l, myplayer[i].playerweapons.item[l - 1]);
							l++;
						}
					}

					if (list == 3)
					{
						while (strcmp(myplayer[i].playershield.item[l - 1], "Empty") != 0)
						{
							videoprinterarg2(l, 0, "Shield item %d is %s", l, myplayer[i].playershield.item[l - 1]);
							l++;
						}
					}

					if (list == 4)
					{
						while (strcmp(myplayer[i].playerarmor.item[l - 1], "Empty") != 0)
						{
							videoprinterarg2(l, 0, "Armor item %d is %s", l, myplayer[i].playerarmor.item[l - 1]);
							l++;
						}
					}

					videoprinternorm(l, 0, "Press d to move to next category\n");

					l++;

					videoprinternorm(l, 0, "Press anything else to exit this menu\n");

					l = 0;

					inputmove(0, 0);

					screenrefresh();
#ifdef INITLIBTCODNOW
					key = TCODConsole::waitForKeypress(true);

					gotcharacter = key.c;
				} while(gotcharacter == 'd');
#endif
#ifdef INITNCURSESNOW
				} while ((gotcharacter = (RETURNTYPEVIDEO)inputgetter()) == 'd');
#endif
				list = 0;
				l = 0;

				inputmove(myplayer[i].y, myplayer[i].x);

				screenclear();

				screenrefresh();
			}


			if(inputcompare(ch, 'i'))
			{
				screenclear();

				int list = 0;
				int l = 0;
#ifdef INITNCURSESNOW
				int gotcharacter = '0';
#endif

#ifdef INITLIBTCODNOW
				char gotcharacter = '0';
#endif

				int theenemy = 0;

				do
				{
					screenclear();

					if(gotcharacter == 'k')
					{
						theenemy++;
					}

					if(theenemy > maxenemies - 1)
					{
						theenemy = 0;
					}

					if(gotcharacter == 'd')
					{
						list++;
					}
					
					if(list > 4)
					{
						list = 0;
					}
					
					videoprinterarg1(l, 0, "AI %d", theenemy + 1);

					if(list == 0)
					{
						videoprinterstats(l+1, 0, "AI %d is %s hp:%d mp:%d at:%d ma:%s %d def:%d w:%s sh:%s ar:%s md:%d", myai[theenemy].count, myai[theenemy].aicharacter.character, myai[theenemy].hitpoints, myai[theenemy].magicpoints, myai[theenemy].aiweapons.damage + myai[theenemy].aicharacter.attack, myai[theenemy].aimagic.equiped, myai[theenemy].aimagic.damage, myai[theenemy].defensepoints + myai[theenemy].aishield.damage, myai[theenemy].aiweapons.equiped, myai[theenemy].aishield.equiped, myai[theenemy].aiarmor.equiped, myai[theenemy].aiarmor.protection);
						l++;
					}

					if(list == 1)
					{
						while(strcmp(myai[theenemy].aimagic.magicitems[l], "Empty") != 0)
						{
							videoprinterarg2(l+1, 0, "Magic item %d is %s", l + 1, myai[theenemy].aimagic.magicitems[l]);
							l++;
						}
					}
					
					if(list == 2)
					{
						while(strcmp(myai[theenemy].aiweapons.item[l], "Empty") != 0)
						{
							videoprinterarg2(l+1, 0, "Weapon item %d is %s", l + 1, myai[theenemy].aiweapons.item[l]);
							l++;
						}
					}
					
					if(list == 3)
					{
						while(strcmp(myai[theenemy].aishield.item[l], "Empty") != 0)
						{
							videoprinterarg2(l+1, 0, "Shield item %d is %s", l + 1, myai[theenemy].aishield.item[l]);
							l++;
						}
					}
					
					if(list == 4)
					{
						while(strcmp(myai[theenemy].aiarmor.item[l], "Empty") != 0)
						{
							videoprinterarg2(l+1, 0, "Armor item %d is %s", l + 1, myai[theenemy].aiarmor.item[l]);
							l++;
						}
					}
					
					videoprinternorm(l+1, 0, "Press d to move to next category\n");
					
					l++;

					videoprinternorm(l+1, 0, "Press k to move to next enemy stat\n");

					l++;
					
					videoprinternorm(l+1, 0, "Press anything else to exit this menu\n");
					
					l = 0;
					
					inputmove(0, 0);
					
					screenrefresh();

#ifdef INITLIBTCODNOW
				key = TCODConsole::waitForKeypress(true);

				gotcharacter = key.c;

				} while(gotcharacter == 'd' || gotcharacter == 'k');
#endif
#ifdef INITNCURSESNOW
				} while((gotcharacter = (RETURNTYPEVIDEO)inputgetter()) == 'd' || gotcharacter == 'k');
#endif
				list = 0;
				l = 0;
				theenemy = 0;
						
				inputmove(myplayer[i].y, myplayer[i].x);
					
				screenclear();
					
				screenrefresh();

			}
				
			if (inputcompare(ch, 'b') && whosturn == 0)
			{
#ifdef INITNCURSESNOW
				int gotcharacter;
#endif

#ifdef INITLIBTCODNOW
				char gotcharacter;
#endif

				int list = 0;

				screenclear();

				int l = 0;

				videoprinterarg1(l, 0, "Player %d", i + 1);
				l++;

				while (strcmp(myplayer[i].playermagic.magicitems[l - 1], "Empty") != 0)
				{
					videoprinterarg2(l, 0, "Magic item %d is %s.\n", l, myplayer[i].playermagic.magicitems[l - 1]);
					l++;
				}

				videoprinternorm(l, 0, "press w to move up\n");
				l++;
				videoprinternorm(l, 0, "press s to move down\n");
				l++;
				videoprinternorm(l, 0, "press e to select\n");
				l++;
				videoprinternorm(l, 0, "press d to move to next category\n");
				l++;

				int u = 1;

				inputmove(u, 0);

				screenrefresh();

				while ((gotcharacter = (RETURNTYPEVIDEO)inputgetter()) != 'e')
				{
					if (gotcharacter == 'w')
					{
						u--;

						if (u < 1)
						{
							u = 1;
						}
					}

					if (gotcharacter == 's')
					{
						u++;

						if (u > 3)
						{
							u = 3;
						}

						if (u >(myplayer[i].playermagic.magiccount) && list == 0)
						{
							u = myplayer[i].playermagic.magiccount;
						}

						if (u > (myplayer[i].playerweapons.weaponcount) && list == 1)
						{
							u = myplayer[i].playerweapons.weaponcount;
						}

						if (u > (myplayer[i].playershield.shieldcount) && list == 2)
						{
							u = myplayer[i].playershield.shieldcount;
						}

						if (u > (myplayer[i].playerarmor.armorcount) && list == 3)
						{
							u = myplayer[i].playerarmor.armorcount;
						}
					}

					if (gotcharacter == 'd')
					{
						list++;

						if (list > 3)
						{
							list = 0;
						}

						u = 1;

						screenclear();

						if (list == 0)
						{
							l = 0;

							videoprinterarg1(l, 0, "Player %d", i + 1);
							l++;

							while (strcmp(myplayer[i].playermagic.magicitems[l - 1], "Empty") != 0)
							{
								videoprinterarg2(l, 0, "Magic item %d is %s.\n", l, myplayer[i].playermagic.magicitems[l - 1]);
								l++;
							}
						}

						if (list == 1)
						{
							l = 0;

							videoprinterarg1(l, 0, "Player %d", i + 1);
							l++;

							while (strcmp(myplayer[i].playerweapons.item[l - 1], "Empty") != 0)
							{
								videoprinterarg2(l, 0, "Weapon item %d is %s.\n", l, myplayer[i].playerweapons.item[l - 1]);
								l++;
							}
						}

						if (list == 2)
						{
							l = 0;

							videoprinterarg1(l, 0, "Player %d", i + 1);
							l++;

							while (strcmp(myplayer[i].playershield.item[l - 1], "Empty") != 0)
							{
								videoprinterarg2(l, 0, "Shield item %d is %s.\n", l, myplayer[i].playershield.item[l - 1]);
								l++;
							}
						}

						if (list == 3)
						{
							l = 0;

							videoprinterarg1(l, 0, "Player %d", i + 1);
							l++;

							while (strcmp(myplayer[i].playerarmor.item[l - 1], "Empty") != 0)
							{
								videoprinterarg2(l, 0, "Armor item %d is %s.\n", l, myplayer[i].playerarmor.item[l - 1]);
								l++;
							}
						}

						videoprinternorm(l, 0, "press w to move up\n");
						l++;
						videoprinternorm(l, 0, "press s to move down\n");
						l++;
						videoprinternorm(l, 0, "press e to select\n");
						l++;
						videoprinternorm(l, 0, "press d to move to next category\n");
						l++;
					}

					inputmove(u, 0);

					screenrefresh();
				}

				if (list == 0)
				{
					myplayer[i].playermagic.equiped = myplayer[i].playermagic.magicitems[u-1];

					if (u == 1)
					{
						myplayer[i].playermagic.rangey = playermagicdistance[myplayer[i].playermagic.randommagic[0]];
						myplayer[i].playermagic.rangex = playermagicdistance[myplayer[i].playermagic.randommagic[0]];
						myplayer[i].playermagic.damage = playermagicdamage[myplayer[i].playermagic.randommagic[0]];
						myplayer[i].playermagic.cost = playermagiccost[myplayer[i].playermagic.randommagic[0]];
					}

					if (u == 2)
					{
						myplayer[i].playermagic.rangey = playermagicdistance[myplayer[i].playermagic.randommagic[1]];
						myplayer[i].playermagic.rangex = playermagicdistance[myplayer[i].playermagic.randommagic[1]];
						myplayer[i].playermagic.damage = playermagicdamage[myplayer[i].playermagic.randommagic[1]];
						myplayer[i].playermagic.cost = playermagiccost[myplayer[i].playermagic.randommagic[1]];
					}

					if (u == 3)
					{
						myplayer[i].playermagic.rangey = playermagicdistance[myplayer[i].playermagic.randommagic[2]];
						myplayer[i].playermagic.rangex = playermagicdistance[myplayer[i].playermagic.randommagic[2]];
						myplayer[i].playermagic.damage = playermagicdamage[myplayer[i].playermagic.randommagic[2]];
						myplayer[i].playermagic.cost = playermagiccost[myplayer[i].playermagic.randommagic[2]];

					}

					myplayer[i].magicattack = myplayer[i].playermagic.damage;
				}

				if (list == 1)
				{
					if (u == 1)
					{
						myplayer[i].playerweapons.equiped = item[myplayer[i].playerweapons.randomweapon[0]];
						myplayer[i].playerweapons.rangey = rangey[myplayer[i].playerweapons.randomweapon[0]];
						myplayer[i].playerweapons.rangex = rangex[myplayer[i].playerweapons.randomweapon[0]];
						myplayer[i].playerweapons.damage = damage[myplayer[i].playerweapons.randomweapon[0]];
					}

					if (u == 2)
					{
						myplayer[i].playerweapons.equiped = item[myplayer[i].playerweapons.randomweapon[1]];
						myplayer[i].playerweapons.rangey = rangey[myplayer[i].playerweapons.randomweapon[1]];
						myplayer[i].playerweapons.rangex = rangex[myplayer[i].playerweapons.randomweapon[1]];
						myplayer[i].playerweapons.damage = damage[myplayer[i].playerweapons.randomweapon[1]];
					}

					if (u == 3)
					{
						myplayer[i].playerweapons.equiped = item[myplayer[i].playerweapons.randomweapon[2]];
						myplayer[i].playerweapons.rangey = rangey[myplayer[i].playerweapons.randomweapon[2]];
						myplayer[i].playerweapons.rangex = rangex[myplayer[i].playerweapons.randomweapon[2]];
						myplayer[i].playerweapons.damage = damage[myplayer[i].playerweapons.randomweapon[2]];
					}
				}

				if (list == 2)
				{
					if (u == 1)
					{
						myplayer[i].playershield.equiped = itemdamage[myplayer[i].playershield.randomshield[0]];
						myplayer[i].playershield.damage = shielddamage[myplayer[i].playershield.randomshield[0]];
						myplayer[i].playershielddamage.item = itemdamage[myplayer[i].playershield.randomshield[0]];
					}

					if (u == 2)
					{
						myplayer[i].playershield.equiped = itemdamage[myplayer[i].playershield.randomshield[1]];
						myplayer[i].playershield.damage = shielddamage[myplayer[i].playershield.randomshield[1]];
						myplayer[i].playershielddamage.item = itemdamage[myplayer[i].playershield.randomshield[1]];
					}

					if (u == 3)
					{
						myplayer[i].playershield.equiped = itemdamage[myplayer[i].playershield.randomshield[2]];
						myplayer[i].playershield.damage = shielddamage[myplayer[i].playershield.randomshield[2]];
						myplayer[i].playershielddamage.item = itemdamage[myplayer[i].playershield.randomshield[2]];
					}

					myplayer[i].shield = myplayer[i].playershield.equiped;
				}

				if (list == 3)
				{
					if (u == 1)
					{
						myplayer[i].playerarmor.equiped = playerarmor[myplayer[i].playerarmor.randomarmor[0]];
						myplayer[i].playerarmor.protection = playerarmorpts[myplayer[i].playerarmor.randomarmor[0]];
						myplayer[i].playerarmor.rangey = playerarmordistancey[myplayer[i].playerarmor.randomarmor[0]];
						myplayer[i].playerarmor.rangex = playerarmordistancex[myplayer[i].playerarmor.randomarmor[0]];
					}

					if (u == 2)
					{
						myplayer[i].playerarmor.equiped = playerarmor[myplayer[i].playerarmor.randomarmor[1]];
						myplayer[i].playerarmor.protection = playerarmorpts[myplayer[i].playerarmor.randomarmor[1]];
						myplayer[i].playerarmor.rangey = playerarmordistancey[myplayer[i].playerarmor.randomarmor[1]];
						myplayer[i].playerarmor.rangex = playerarmordistancex[myplayer[i].playerarmor.randomarmor[1]];
					}

					if (u == 3)
					{
						myplayer[i].playerarmor.equiped = playerarmor[myplayer[i].playerarmor.randomarmor[2]];
						myplayer[i].playerarmor.protection = playerarmorpts[myplayer[i].playerarmor.randomarmor[2]];
						myplayer[i].playerarmor.rangey = playerarmordistancey[myplayer[i].playerarmor.randomarmor[2]];
						myplayer[i].playerarmor.rangex = playerarmordistancex[myplayer[i].playerarmor.randomarmor[2]];
					}
				}

				l = 0;
				u = 1;

				inputmove(myplayer[i].y, myplayer[i].x);

				screenclear();

				screenrefresh();

			}

			if (inputcompare(ch, 'b') && whosturn == 1 && twoplayers == 1)
			{
#ifdef INITNCURSESNOW
				int gotcharacter;
#endif

#ifdef INITLIBTCODNOW
				char gotcharacter;
#endif

				int list = 0;

				screenclear();

				int l = 0;

				videoprinterarg1(l, 0, "AI %d", i + 1);
				l++;

				while (strcmp(myai[iai].aimagic.magicitems[l - 1], "Empty") != 0)
				{
					videoprinterarg2(l, 0, "Magic item %d is %s.\n", l, myai[iai].aimagic.magicitems[l - 1]);
					l++;
				}

				videoprinternorm(l, 0, "press w to move up\n");
				l++;
				videoprinternorm(l, 0, "press s to move down\n");
				l++;
				videoprinternorm(l, 0, "press e to select\n");
				l++;
				videoprinternorm(l, 0, "press d to move to next category\n");
				l++;

				int u = 1;

				inputmove(u, 0);

				screenrefresh();

				while ((gotcharacter = (RETURNTYPEVIDEO)inputgetter()) != 'e')
				{
					if (gotcharacter == 'w')
					{
						u--;

						if (u < 1)
						{
							u = 1;
						}
					}

					if (gotcharacter == 's')
					{
						u++;

						if (u > 3)
						{
							u = 3;
						}

						if (u > (myai[iai].aimagic.magiccount) && list == 0)
						{
							u = myai[iai].aimagic.magiccount;
						}

						if (u > (myai[iai].aiweapons.weaponcount) && list == 1)
						{
							u = myai[iai].aiweapons.weaponcount;
						}

						if (u > (myai[iai].aishield.shieldcount) && list == 2)
						{
							u = myai[iai].aishield.shieldcount;
						}

						if (u > (myai[iai].aiarmor.armorcount) && list == 3)
						{
							u = myai[iai].aiarmor.armorcount;
						}
					}

					if (gotcharacter == 'd')
					{
						list++;

						if (list > 3)
						{
							list = 0;
						}

						u = 1;

						screenclear();

						if (list == 0)
						{
							l = 0;

							videoprinterarg1(l, 0, "AI %d", i + 1);
							l++;

							while (strcmp(myai[iai].aimagic.magicitems[l - 1], "Empty") != 0)
							{
								videoprinterarg2(l, 0, "Magic item %d is %s.\n", l, myai[iai].aimagic.magicitems[l - 1]);
								l++;
							}
						}

						if (list == 1)
						{
							l = 0;

							videoprinterarg1(l, 0, "AI %d", i + 1);
							l++;

							while (strcmp(myai[iai].aiweapons.item[l - 1], "Empty") != 0)
							{
								videoprinterarg2(l, 0, "Weapon item %d is %s.\n", l, myai[iai].aiweapons.item[l - 1]);
								l++;
							}
						}

						if (list == 2)
						{
							l = 0;

							videoprinterarg1(l, 0, "AI %d", i + 1);
							l++;

							while (strcmp(myai[iai].aishield.item[l - 1], "Empty") != 0)
							{
								videoprinterarg2(l, 0, "Shield item %d is %s.\n", l, myai[iai].aishield.item[l - 1]);
								l++;
							}
						}

						if (list == 3)
						{
							l = 0;

							videoprinterarg1(l, 0, "AI %d", i + 1);
							l++;

							while (strcmp(myai[iai].aiarmor.item[l - 1], "Empty") != 0)
							{
								videoprinterarg2(l, 0, "Armor item %d is %s.\n", l, myai[iai].aiarmor.item[l - 1]);
								l++;
							}
						}

						videoprinternorm(l, 0, "press w to move up\n");
						l++;
						videoprinternorm(l, 0, "press s to move down\n");
						l++;
						videoprinternorm(l, 0, "press e to select\n");
						l++;
						videoprinternorm(l, 0, "press d to move to next category\n");
						l++;
					}

					inputmove(u, 0);

					screenrefresh();
				}

				if (list == 0)
				{
					myai[iai].aimagic.equiped = myai[iai].aimagic.magicitems[u - 1];

					if (u == 1)
					{
						myai[iai].aimagic.rangey = aimagicdistance[myai[iai].aimagic.randommagic[0]];
						myai[iai].aimagic.rangex = aimagicdistance[myai[iai].aimagic.randommagic[0]];
						myai[iai].aimagic.damage = aimagicdamage[myai[iai].aimagic.randommagic[0]];
						myai[iai].aimagic.cost = aimagiccost[myai[iai].aimagic.randommagic[0]];
					}

					if (u == 2)
					{
						myai[iai].aimagic.rangey = aimagicdistance[myai[iai].aimagic.randommagic[1]];
						myai[iai].aimagic.rangex = aimagicdistance[myai[iai].aimagic.randommagic[1]];
						myai[iai].aimagic.damage = aimagicdamage[myai[iai].aimagic.randommagic[1]];
						myai[iai].aimagic.cost = aimagiccost[myai[iai].aimagic.randommagic[1]];
					}

					if (u == 3)
					{
						myai[iai].aimagic.rangey = aimagicdistance[myai[iai].aimagic.randommagic[2]];
						myai[iai].aimagic.rangex = aimagicdistance[myai[iai].aimagic.randommagic[2]];
						myai[iai].aimagic.damage = aimagicdamage[myai[iai].aimagic.randommagic[2]];
						myai[iai].aimagic.cost = aimagiccost[myai[iai].aimagic.randommagic[2]];
					}

					myai[iai].magicattack = myai[iai].aimagic.damage;
				}

				if (list == 1)
				{
					if (u == 1)
					{
						myai[iai].aiweapons.equiped = itemenemies[myai[iai].aiweapons.randomweapon[0]];
						myai[iai].aiweapons.rangey = rangeyenemies[myai[iai].aiweapons.randomweapon[0]];
						myai[iai].aiweapons.rangex = rangexenemies[myai[iai].aiweapons.randomweapon[0]];
						myai[iai].aiweapons.damage = damageenemies[myai[iai].aiweapons.randomweapon[0]];
					}

					if (u == 2)
					{
						myai[iai].aiweapons.equiped = itemenemies[myai[iai].aiweapons.randomweapon[1]];
						myai[iai].aiweapons.rangey = rangeyenemies[myai[iai].aiweapons.randomweapon[1]];
						myai[iai].aiweapons.rangex = rangexenemies[myai[iai].aiweapons.randomweapon[1]];
						myai[iai].aiweapons.damage = damageenemies[myai[iai].aiweapons.randomweapon[1]];
					}

					if (u == 3)
					{
						myai[iai].aiweapons.equiped = itemenemies[myai[iai].aiweapons.randomweapon[2]];
						myai[iai].aiweapons.rangey = rangeyenemies[myai[iai].aiweapons.randomweapon[2]];
						myai[iai].aiweapons.rangex = rangexenemies[myai[iai].aiweapons.randomweapon[2]];
						myai[iai].aiweapons.damage = damageenemies[myai[iai].aiweapons.randomweapon[2]];
					}
				}

				if (list == 2)
				{
					if (u == 1)
					{
						myai[iai].aishield.equiped = itemdamageenemies[myai[iai].aishield.randomshield[0]];
						myai[iai].aishield.damage = shielddamageenemies[myai[iai].aishield.randomshield[0]];
						myai[iai].aishielddamage.item = itemdamageenemies[myai[iai].aishield.randomshield[0]];
					}

					if (u == 2)
					{
						myai[iai].aishield.equiped = itemdamageenemies[myai[iai].aishield.randomshield[1]];
						myai[iai].aishield.damage = shielddamageenemies[myai[iai].aishield.randomshield[1]];
						myai[iai].aishielddamage.item = itemdamageenemies[myai[iai].aishield.randomshield[1]];
					}

					if (u == 3)
					{
						myai[iai].aishield.equiped = itemdamageenemies[myai[iai].aishield.randomshield[2]];
						myai[iai].aishield.damage = shielddamageenemies[myai[iai].aishield.randomshield[2]];
						myai[iai].aishielddamage.item = itemdamageenemies[myai[iai].aishield.randomshield[2]];
					}

					myai[iai].shield = myai[iai].aishield.equiped;
				}

				if (list == 3)
				{
					if (u == 1)
					{
						myai[iai].aiarmor.equiped = aiarmor[myai[iai].aiarmor.randomarmor[0]];
						myai[iai].aiarmor.protection = aiarmorpts[myai[iai].aiarmor.randomarmor[0]];
						myai[iai].aiarmor.rangey = aiarmordistancey[myai[iai].aiarmor.randomarmor[0]];
						myai[iai].aiarmor.rangex = aiarmordistancex[myai[iai].aiarmor.randomarmor[0]];
					}

					if (u == 2)
					{
						myai[iai].aiarmor.equiped = aiarmor[myai[iai].aiarmor.randomarmor[1]];
						myai[iai].aiarmor.protection = aiarmorpts[myai[iai].aiarmor.randomarmor[1]];
						myai[iai].aiarmor.rangey = aiarmordistancey[myai[iai].aiarmor.randomarmor[1]];
						myai[iai].aiarmor.rangex = aiarmordistancex[myai[iai].aiarmor.randomarmor[1]];
					}

					if (u == 3)
					{
						myai[iai].aiarmor.equiped = aiarmor[myai[iai].aiarmor.randomarmor[2]];
						myai[iai].aiarmor.protection = aiarmorpts[myai[iai].aiarmor.randomarmor[2]];
						myai[iai].aiarmor.rangey = aiarmordistancey[myai[iai].aiarmor.randomarmor[2]];
						myai[iai].aiarmor.rangex = aiarmordistancex[myai[iai].aiarmor.randomarmor[2]];
					}
				}

				l = 0;
				u = 1;

				inputmove(myai[iai].y, myai[iai].x);

				screenclear();

				screenrefresh();

			}

			if(inputcompare(ch, 'm'))
			{
				int t = -1;

				int aimagicdamage2 = -1;
				int themagicchoose = -1;
				int aiarmorprotection = -1;
				int thearmorchoose = -1;
				
				for (int j = 0; j < maxenemies; j++)
				{
					if (twoplayers != 1)
					{
						myai[j].aiarmor.equiped = aiarmor[myai[j].aiarmor.randomarmor[0]];
						myai[j].aiarmor.rangey = aiarmordistancey[myai[j].aiarmor.randomarmor[0]];
						myai[j].aiarmor.rangex = aiarmordistancex[myai[j].aiarmor.randomarmor[0]];
						myai[j].aiarmor.protection = aiarmorpts[myai[j].aiarmor.randomarmor[0]];

						if ((abs(myplayer[i].y - myai[j].y) <= myai[j].aiarmor.rangey) && (abs(myplayer[i].x - myai[j].x) <= myai[j].aiarmor.rangex) && myai[j].aiarmor.protection > aiarmorprotection)
						{
							aiarmorprotection = aiarmorpts[myai[j].aiarmor.randomarmor[0]];
							thearmorchoose = myai[j].aiarmor.randomarmor[0];
						}

						myai[j].aiarmor.equiped = aiarmor[myai[j].aiarmor.randomarmor[1]];
						myai[j].aiarmor.rangey = aiarmordistancey[myai[j].aiarmor.randomarmor[1]];
						myai[j].aiarmor.rangex = aiarmordistancex[myai[j].aiarmor.randomarmor[1]];
						myai[j].aiarmor.protection = aiarmorpts[myai[j].aiarmor.randomarmor[1]];

						if ((abs(myplayer[i].y - myai[j].y) <= myai[j].aiarmor.rangey) && (abs(myplayer[i].x - myai[j].x) <= myai[j].aiarmor.rangex) && myai[j].aiarmor.protection > aiarmorprotection)
						{
							aiarmorprotection = aiarmorpts[myai[j].aiarmor.randomarmor[1]];
							thearmorchoose = myai[j].aiarmor.randomarmor[1];
						}

						myai[j].aiarmor.equiped = aiarmor[myai[j].aiarmor.randomarmor[2]];
						myai[j].aiarmor.rangey = aiarmordistancey[myai[j].aiarmor.randomarmor[2]];
						myai[j].aiarmor.rangex = aiarmordistancex[myai[j].aiarmor.randomarmor[2]];
						myai[j].aiarmor.protection = aiarmorpts[myai[j].aiarmor.randomarmor[2]];

						if ((abs(myplayer[i].y - myai[j].y) <= myai[j].aiarmor.rangey) && (abs(myplayer[i].x - myai[j].x) <= myai[j].aiarmor.rangex) && myai[j].aiarmor.protection > aiarmorprotection)
						{
							aiarmorprotection = aiarmorpts[myai[j].aiarmor.randomarmor[2]];
							thearmorchoose = myai[j].aiarmor.randomarmor[2];
						}

						myai[j].aiarmor.equiped = aiarmor[thearmorchoose];
						myai[j].aiarmor.rangey = aiarmordistancey[thearmorchoose];
						myai[j].aiarmor.rangex = aiarmordistancex[thearmorchoose];
						myai[j].aiarmor.protection = aiarmorpts[thearmorchoose];

						if (thearmorchoose == -1)
						{
							myai[j].aiarmor.equiped = aiarmor[myai[j].aiarmor.randomarmor[0]];
							myai[j].aiarmor.rangey = aiarmordistancey[myai[j].aiarmor.randomarmor[0]];
							myai[j].aiarmor.rangex = aiarmordistancex[myai[j].aiarmor.randomarmor[0]];
							myai[j].aiarmor.protection = aiarmorpts[myai[j].aiarmor.randomarmor[0]];
						}

						myai[j].aimagic.equiped = aimagicitems[myai[j].aimagic.randommagic[0]];
						myai[j].aimagic.rangey = aimagicdistance[myai[j].aimagic.randommagic[0]];
						myai[j].aimagic.rangex = aimagicdistance[myai[j].aimagic.randommagic[0]];
						myai[j].aimagic.damage = aimagicdamage[myai[j].aimagic.randommagic[0]];
						myai[j].aimagic.cost = aimagiccost[myai[j].aimagic.randommagic[0]];

						if ((positionydiff = abs(myplayer[i].y - myai[j].y)) <= myai[j].aimagic.rangey && (positionxdiff = abs(myplayer[i].x - myai[j].x)) <= myai[j].aimagic.rangex && (myai[j].magicpoints - myai[j].aimagic.cost) >= 0)
						{
							if (myai[j].aimagic.damage > aimagicdamage2)
							{
								aimagicdamage2 = aimagicdamage[myai[j].aimagic.randommagic[0]];
								themagicchoose = myai[j].aimagic.randommagic[0];
								t = j;
							}
						}

						myai[j].aimagic.equiped = aimagicitems[myai[j].aimagic.randommagic[1]];
						myai[j].aimagic.rangey = aimagicdistance[myai[j].aimagic.randommagic[1]];
						myai[j].aimagic.rangex = aimagicdistance[myai[j].aimagic.randommagic[1]];
						myai[j].aimagic.damage = aimagicdamage[myai[j].aimagic.randommagic[1]];
						myai[j].aimagic.cost = aimagiccost[myai[j].aimagic.randommagic[1]];

						if ((positionydiff = abs(myplayer[i].y - myai[j].y)) <= myai[j].aimagic.rangey && (positionxdiff = abs(myplayer[i].x - myai[j].x)) <= myai[j].aimagic.rangex && (myai[j].magicpoints - myai[j].aimagic.cost) >= 0)
						{
							if (myai[j].aimagic.damage > aimagicdamage2)
							{
								aimagicdamage2 = aimagicdamage[myai[j].aimagic.randommagic[1]];
								themagicchoose = myai[j].aimagic.randommagic[1];
								t = j;
							}
						}

						myai[j].aimagic.equiped = aimagicitems[myai[j].aimagic.randommagic[2]];
						myai[j].aimagic.rangey = aimagicdistance[myai[j].aimagic.randommagic[2]];
						myai[j].aimagic.rangex = aimagicdistance[myai[j].aimagic.randommagic[2]];
						myai[j].aimagic.damage = aimagicdamage[myai[j].aimagic.randommagic[2]];
						myai[j].aimagic.cost = aimagiccost[myai[j].aimagic.randommagic[2]];

						if ((positionydiff = abs(myplayer[i].y - myai[j].y)) <= myai[j].aimagic.rangey && (positionxdiff = abs(myplayer[i].x - myai[j].x)) <= myai[j].aimagic.rangex && (myai[j].magicpoints - myai[j].aimagic.cost) >= 0)
						{
							if (myai[j].aimagic.damage > aimagicdamage2)
							{
								aimagicdamage2 = aimagicdamage[myai[j].aimagic.randommagic[2]];
								themagicchoose = myai[j].aimagic.randommagic[2];
								t = j;
							}
						}
					}
					
					if ((t == -1) && (positionydiff = abs(myplayer[i].y - myai[j].y)) <= myplayer[i].playermagic.rangey && (positionxdiff = abs(myplayer[i].x - myai[j].x)) <= myplayer[i].playermagic.rangex)
					{
						t = j;
					}

					if (twoplayers != 1)
					{
						if (themagicchoose != -1)
						{
							myai[j].aimagic.equiped = aimagicitems[themagicchoose];
							myai[j].aimagic.rangey = aimagicdistance[themagicchoose];
							myai[j].aimagic.rangex = aimagicdistance[themagicchoose];
							myai[j].aimagic.damage = aimagicdamage[themagicchoose];
							myai[j].aimagic.cost = aimagiccost[themagicchoose];
						}
						else
						{
							myai[j].aimagic.equiped = aimagicitems[myai[j].aimagic.randommagic[0]];
							myai[j].aimagic.rangey = aimagicdistance[myai[j].aimagic.randommagic[0]];
							myai[j].aimagic.rangex = aimagicdistance[myai[j].aimagic.randommagic[0]];
							myai[j].aimagic.damage = aimagicdamage[myai[j].aimagic.randommagic[0]];
							myai[j].aimagic.cost = aimagiccost[myai[j].aimagic.randommagic[0]];
						}
					}
				}

				if(t == -1)
				{
					t = 0;
				}

				for(int p = 0; p < maxenemies; p++)
				{
					for(int j = 0; j < maxplayers; j++)
					{
						if(t != -1)
						{
							p = t;

							if((myai[p].magicpoints >= myai[p].aimagic.cost) && (positionydiff = abs(myplayer[j].y - myai[p].y)) <= myai[p].aimagic.rangey && (positionxdiff = abs(myplayer[j].x - myai[p].x)) <= myai[p].aimagic.rangex && inputcompare(ch, 'm') && myai[p].hitpoints > 0 && myplayer[j].hitpoints > 0)
							{
								if(j == i)
								{
									if((abs(myplayer[j].y - myai[p].y) <= myai[p].aiarmor.rangey) && (abs(myplayer[j].x - myai[p].x) <= myai[p].aiarmor.rangex))
									{
										myplayer[j].hitpoints = myplayer[j].hitpoints - myai[p].magicattack + myplayer[j].playercharacter.magicresist + myplayer[j].playerarmor.protection;
									}
									else
									{
										myplayer[j].hitpoints = myplayer[j].hitpoints - myai[p].magicattack + myplayer[j].playercharacter.magicresist;
									}
								}

								if(i == j)
								{
									myai[p].magicpoints = myai[p].magicpoints - myai[p].aimagic.cost;
								}

								for(int k = 0; k < maxplayers; k++)
								{
									if(myplayer[k].hitpoints > 0)
									{
										break;
									}

									if(k == maxplayers - 1)
									{
										winner = const_cast<char *>("ai");

										goto ended;
									}
								}
							}
						}
					}

					if(t != -1)
					{
						break;
					}
				}


				for(int p = 0; p < maxenemies; p++)
				{
					
					if(t != -1)
					{
						p = t;
					}

					for(int j = 0; j < maxplayers; j++)
					{
						if(t != -1)
						{
							p = t;

							if(j == i)
							{
								if((myplayer[j].magicpoints >= myplayer[j].playermagic.cost) && (positionydiff = abs(myplayer[j].y - myai[p].y)) <= myplayer[j].playermagic.rangey  && (positionxdiff = abs(myplayer[j].x - myai[p].x)) <= myplayer[j].playermagic.rangex && inputcompare(ch, 'm') && myai[p].hitpoints > 0 && myplayer[j].hitpoints > 0)
								{
									myai[p].hitpoints = myai[p].hitpoints - myplayer[j].magicattack + myai[p].aicharacter.magicresist;
						
									myplayer[j].magicpoints = myplayer[j].magicpoints - myplayer[j].playermagic.cost;
					
									for(int k = 0; k < maxenemies; k++)
									{
										if(myai[k].hitpoints > 0)
										{
											break;
										}
						
										if(k == maxenemies - 1)
										{
											winner = const_cast<char *>("player");
						
											goto ended;
										}
									}
								}
							}
						}
					}

					if(t != -1)
					{
						break;
					}
				}

				t = -1;
			}

			for(int p = 0; p < maxenemies; p++)
			{
				for(int j = 0; j < maxplayers; j++)
				{
					int aiequipedweapon = -1;
					int thechoose = -1;
					int aishieldweapon = -1;
					int thechooseshield = -1;

					if (twoplayers != 1)
					{
						myai[p].aishield.equiped = itemdamageenemies[myai[p].aishield.randomshield[0]];
						myai[p].aishield.damage = shielddamageenemies[myai[p].aishield.randomshield[0]];

						if (myai[p].aishield.damage > aishieldweapon)
						{
							thechooseshield = myai[p].aishield.randomshield[0];
							aishieldweapon = shielddamageenemies[myai[p].aishield.randomshield[0]];
						}

						myai[p].aishield.equiped = itemdamageenemies[myai[p].aishield.randomshield[1]];
						myai[p].aishield.damage = shielddamageenemies[myai[p].aishield.randomshield[1]];

						if (myai[p].aishield.damage > aishieldweapon)
						{
							thechooseshield = myai[p].aishield.randomshield[1];
							aishieldweapon = shielddamageenemies[myai[p].aishield.randomshield[1]];
						}

						myai[p].aishield.equiped = itemdamageenemies[myai[p].aishield.randomshield[2]];
						myai[p].aishield.damage = shielddamageenemies[myai[p].aishield.randomshield[2]];

						if (myai[p].aishield.damage > aishieldweapon)
						{
							thechooseshield = myai[p].aishield.randomshield[2];
							aishieldweapon = shielddamageenemies[myai[p].aishield.randomshield[2]];
						}

						myai[p].aishield.equiped = itemdamageenemies[thechooseshield];
						myai[p].aishield.damage = shielddamageenemies[thechooseshield];

						myai[p].aiweapons.equiped = itemenemies[myai[p].aiweapons.randomweapon[0]];
						myai[p].aiweapons.rangey = rangeyenemies[myai[p].aiweapons.randomweapon[0]];
						myai[p].aiweapons.rangex = rangexenemies[myai[p].aiweapons.randomweapon[0]];
						myai[p].aiweapons.damage = damageenemies[myai[p].aiweapons.randomweapon[0]];

						if ((positionydiff = abs(myplayer[i].y - myai[p].y)) <= myai[p].aiweapons.rangey && (positionxdiff = abs(myplayer[i].x - myai[p].x)) <= myai[p].aiweapons.rangex && myai[p].hitpoints > 0 && myplayer[i].hitpoints > 0 && (inputcompare(ch, 'a') || inputcompare(ch, 'd') || inputcompare(ch, 'w') || inputcompare(ch, 's')))
						{
							if (myai[p].aiweapons.damage > aiequipedweapon)
							{
								aiequipedweapon = myai[p].aiweapons.damage;
								thechoose = myai[p].aiweapons.randomweapon[0];
							}
						}

						myai[p].aiweapons.equiped = itemenemies[myai[p].aiweapons.randomweapon[1]];
						myai[p].aiweapons.rangey = rangeyenemies[myai[p].aiweapons.randomweapon[1]];
						myai[p].aiweapons.rangex = rangexenemies[myai[p].aiweapons.randomweapon[1]];
						myai[p].aiweapons.damage = damageenemies[myai[p].aiweapons.randomweapon[1]];

						if ((positionydiff = abs(myplayer[i].y - myai[p].y)) <= myai[p].aiweapons.rangey && (positionxdiff = abs(myplayer[i].x - myai[p].x)) <= myai[p].aiweapons.rangex && myai[p].hitpoints > 0 && myplayer[i].hitpoints > 0 && (inputcompare(ch, 'a') || inputcompare(ch, 'd') || inputcompare(ch, 'w') || inputcompare(ch, 's')))
						{
							if (myai[i].aiweapons.damage > aiequipedweapon)
							{
								aiequipedweapon = myai[p].aiweapons.damage;
								thechoose = myai[p].aiweapons.randomweapon[1];
							}
						}

						myai[p].aiweapons.equiped = itemenemies[myai[p].aiweapons.randomweapon[2]];
						myai[p].aiweapons.rangey = rangeyenemies[myai[p].aiweapons.randomweapon[2]];
						myai[p].aiweapons.rangex = rangexenemies[myai[p].aiweapons.randomweapon[2]];
						myai[p].aiweapons.damage = damageenemies[myai[p].aiweapons.randomweapon[2]];

						if ((positionydiff = abs(myplayer[i].y - myai[p].y)) <= myai[p].aiweapons.rangey && (positionxdiff = abs(myplayer[i].x - myai[p].x)) <= myai[p].aiweapons.rangex && myai[p].hitpoints > 0 && myplayer[i].hitpoints > 0 && (inputcompare(ch, 'a') || inputcompare(ch, 'd') || inputcompare(ch, 'w') || inputcompare(ch, 's')))
						{
							if (myai[i].aiweapons.damage > aiequipedweapon)
							{
								aiequipedweapon = myai[p].aiweapons.damage;
								thechoose = myai[p].aiweapons.randomweapon[2];
							}
						}

						if (thechoose != -1)
						{
							myai[p].aiweapons.equiped = itemenemies[thechoose];
							myai[p].aiweapons.rangey = rangeyenemies[thechoose];
							myai[p].aiweapons.rangex = rangexenemies[thechoose];
							myai[p].aiweapons.damage = damageenemies[thechoose];
						}
						else
						{
							myai[p].aiweapons.equiped = itemenemies[myai[p].aiweapons.randomweapon[0]];
							myai[p].aiweapons.rangey = rangeyenemies[myai[p].aiweapons.randomweapon[0]];
							myai[p].aiweapons.rangex = rangexenemies[myai[p].aiweapons.randomweapon[0]];
							myai[p].aiweapons.damage = damageenemies[myai[p].aiweapons.randomweapon[0]];
						}
					}

					if(j == i)
					{
						if( (positionydiff = abs(myplayer[j].y - myai[p].y)) <= myplayer[j].playerweapons.rangey  && (positionxdiff = abs(myplayer[j].x - myai[p].x)) <= myplayer[j].playerweapons.rangex && myai[p].hitpoints > 0 && myplayer[j].hitpoints > 0 && (inputcompare(ch, 'a') || inputcompare(ch, 'd') || inputcompare(ch, 'w') || inputcompare(ch, 's')))
						{	
							myai[p].hitpoints = myai[p].hitpoints - myplayer[j].playerweapons.damage - myplayer[j].playercharacter.attack + myai[p].aishield.damage + myai[p].defensepoints;
					
							for(int k = 0; k < maxenemies; k++)
							{
								if(myai[k].hitpoints > 0)
								{
									break;
								}
						
								if(k == maxenemies - 1)
								{
									winner = const_cast<char *>("player");
				
									goto ended;
								}
							}
						}
					}

					if(j == i)
					{
						if( (positionydiff = abs(myplayer[j].y - myai[p].y)) <= myai[p].aiweapons.rangey  && (positionxdiff = abs(myplayer[j].x - myai[p].x)) <= myai[p].aiweapons.rangex && myai[p].hitpoints > 0 && myplayer[j].hitpoints > 0 && (inputcompare(ch, 'a') || inputcompare(ch, 'd') || inputcompare(ch, 'w') || inputcompare(ch, 's')))
						{	
							myplayer[j].hitpoints = myplayer[j].hitpoints - myai[p].aiweapons.damage - myai[p].aicharacter.attack + myplayer[j].playershield.damage + myplayer[j].defensepoints;

							for(int k = 0; k < maxplayers; k++)
							{
								if(myplayer[k].hitpoints > 0)
								{
									break;
								}

								if(k == maxenemies - 1)
								{
									winner = const_cast<char *>("ai");

									goto ended;
								}
							}
						}
					}

					thechoose = -1;
					thechooseshield = -1;
					aiequipedweapon = -1;
					aishieldweapon = -1;
				}
			}

			for(int j = 0; j < maxplayers; j++)
			{
				if(myplayer[i].hitpoints <= 0)
				{
					i++;
				}
			
				if(i >= maxplayers)
				{
					i = 0;
				}
			
				if(myplayer[i].hitpoints > 0)
				{
					break;
				}
			}
		
			for(int j = 0; j < maxenemies; j++)
			{
				if(myplayer[i].y == myai[j].y && myplayer[i].x == myai[j].x && myai[j].hitpoints > 0)
				{
					myplayer[i].y = myplayer[i].prevy;
					myplayer[i].x = myplayer[i].prevx;
					
					if(whosturn == 0)
					{
						positiony = (myplayer[i].y / hitpointsy) * hitpointsy;
						positionx = (myplayer[i].x / hitpointsx) * hitpointsx;
					}

					if(whosturn == 1)
					{
						positiony = (myai[iai].y / hitpointsy) * hitpointsy;
						positionx = (myai[iai].x / hitpointsx) * hitpointsx;
					}

					if(positiony > 0)
					{
						positiony++;
					}

					if(positionx > 0)
					{
						positionx++;
					}
			
					myplayer[i].replayer = 1;
				}
				
				for(int l = 0; l < maxplayers; l++)
				{
					if(i != l)
					{
						if(myplayer[l].y == myplayer[i].y && myplayer[l].x == myplayer[i].x && myplayer[l].hitpoints > 0)
						{
							myplayer[i].y = myplayer[i].prevy;
							myplayer[i].x = myplayer[i].prevx;

							if(whosturn == 0)
							{
								positiony = (myplayer[i].y / hitpointsy) * hitpointsy;
								positionx = (myplayer[i].x / hitpointsx) * hitpointsx;
							}
							
							if(whosturn == 1)
							{
								positiony = (myai[iai].y / hitpointsy) * hitpointsy;
								positionx = (myai[iai].x / hitpointsx) * hitpointsx;
							}

							if(positiony > 0)
							{
								positiony++;
							}

							if(positionx > 0)
							{
								positionx++;
							}
							
							myplayer[i].replayer = 1;
						}
					}
				}
			}

			if(myplayer[i].replayer == 0)
			{
				myplayer[i].prevy = myplayer[i].y;
				myplayer[i].prevx = myplayer[i].x;
			}
		
			for(int i = 0; i < maxplayers; i++)
			{
				myplayer[i].replayer = 0;
			}

			for(int i = 0; i < maxenemies; i++)
			{
				myai[i].replayer = 0;
			}
		
			for(int i = 0; i < maxplayers; i++)
			{
				if(myplayer[i].hitpoints > 0 && myplayer[i].y >= (positiony - hitpointsy) && myplayer[i].x >= (positionx - hitpointsx))
				{
					videoprinternorm(myplayer[i].y - positiony, myplayer[i].x - positionx, myplayer[i].charactersign);
				}
			}
		
			for(int i = 0; i < maxenemies; i++)
			{
				if(myai[i].hitpoints > 0 && myai[i].y >= (positiony - hitpointsy) && myai[i].x >= (positionx - hitpointsx))
				{
					videoprinternorm(myai[i].y - positiony, myai[i].x - positionx, myai[i].charactersign);
				}
			}
		
			for(int i = 0; i < maxplayers; i++)
			{
				if((hitpointspos1.y + i) > positiony)
				{
					videoprinterstats(hitpointspos1.y + i - positiony, 0, "Player %d is %s hp:%d mp:%d at:%d ma:%s %d def:%d w:%s sh:%s ar:%s md:%d", myplayer[i].count, myplayer[i].playercharacter.character, myplayer[i].hitpoints, myplayer[i].magicpoints, myplayer[i].playerweapons.damage + myplayer[i].playercharacter.attack, myplayer[i].playermagic.equiped, myplayer[i].playermagic.damage, myplayer[i].defensepoints + myplayer[i].playershield.damage, myplayer[i].playerweapons.equiped, myplayer[i].playershield.equiped, myplayer[i].playerarmor.equiped, myplayer[i].playerarmor.protection);
				}
			}

			for(int i = 0; i < maxenemies; i++)
			{
				if((hitpointspos1.ay + i) >= (positiony) && (positiony > (maxenemies)))
				{
					videoprinterstats(hitpointspos1.ay + i - positiony, 0, "AI %d is %s hp:%d mp:%d at:%d ma:%s %d def:%d w:%s sh:%s ar:%s md:%d", myai[i].count, myai[i].aicharacter.character, myai[i].hitpoints, myai[i].magicpoints, myai[i].aiweapons.damage + myai[i].aicharacter.attack, myai[i].aimagic.equiped, myai[i].aimagic.damage, myai[i].defensepoints + myai[i].aishield.damage, myai[i].aiweapons.equiped, myai[i].aishield.equiped, myai[i].aiarmor.equiped, myai[i].aiarmor.protection);
				}
			}

			for(int i = 0; i < maxplayers; i++)
			{
				if(myplayer[i].hitpoints > 0)
				{
					break;
				}

				if(i == maxplayers - 1)
				{
					goto ended;
				}
			}

			if(whosturn == 0)
			{
				inputmove(myplayer[i].y - positiony, myplayer[i].x - positionx);
			}

			if(whosturn == 1)
			{
				inputmove(myai[iai].y - positiony, myai[iai].x - positionx);
			}

			screenrefresh();


			if((inputcompare(ch, 'w') || inputcompare(ch, 's') || inputcompare(ch, 'd') || inputcompare(ch, 'a') || inputcompare(ch, 'm')) && twoplayers == 1)
			{
				whosturn++;

#if !defined(_MSC_VER)
				sleep(2);
#elif defined(_MSC_VER)
				Sleep(2000);
#endif
			}

			if(twoplayers == 0)
			{
				whosturn = 0;
			}

			if(whosturn > 1)
			{
					  whosturn = 0;
			}

			if(whosturn == 0)
			{
					  inputmove(myplayer[i].y - positiony, myplayer[i].x - positionx);
			}

			if(whosturn == 1)
			{
					  inputmove(myai[iai].y - positiony, myai[iai].x - positionx);
			}

			screenrefresh();
		}

	ended:

		screenclear();

		if (inputcompare(ch, 'q'))
		{
#if defined(_MSC_VER)
			if(fileExists("Data/SaveFile.txt"))
#else
			if (access("Data/SaveFile.txt", F_OK) != -1)
#endif
			{
				remove("Data/SaveFile.txt");
			}

			goto endmenow;
		}
	
		if(strcmp(winner, "ai") == 0)
		{
			videoprinternorm(0, 0, "You lose the ai won the game is over.");
			videoprinternorm(1, 0, "Press y to end");

			screenrefresh();

#if defined(_MSC_VER)
			if(fileExists("Data/SaveFile.txt"))
#else
			if(access("Data/SaveFile.txt", F_OK ) != -1)
#endif
			{
				remove("Data/SaveFile.txt");
			}

			ch = (RETURNTYPEVIDEO)inputgetter();

			if(ch != 'y')
			{
				roundssofar = 1;

				screenclear();

				screenrefresh();

				goto beginning;
			}
		
#ifdef INITNCURSESNOW
			endwin();
#endif

			return 0;
		}

		if(roundssofar == rounds)
		{
			videoprinternorm(0, 0, "You have beat the game. Congratulations.");
			
			if(rounds >= 50)
			{
				videoprinternorm(1, 0, "You achieved a real accomplishment by beating 50 or more rounds.");
				videoprinternorm(2, 0, "Press y to end");
			}
			else
			{
				videoprinternorm(1, 0, "Press y to end");
			}

			screenrefresh();

#if defined(_MSC_VER)
			if(fileExists("Data/SaveFile.txt"))
#else
			if(access("Data/SaveFile.txt", F_OK ) != -1)
#endif
			{
				remove("Data/SaveFile.txt");
			}

			ch = (RETURNTYPEVIDEO)inputgetter();

			if(ch != 'y')
			{
				roundssofar = 1;

				screenclear();

				screenrefresh();

				goto beginning;
			}

#ifdef INITNCURSESNOW
			endwin();
#endif

			return 0;
		}

		videoprinterarg2(0, 0, "The winner of the %d battle is %s.", roundssofar, winner);
		videoprinterarg1(1, 0, "You have %d battle to go", rounds - roundssofar);
		videoprinternorm(2, 0, "Press y to end"); 
	
		screenrefresh();

		ch = (RETURNTYPEVIDEO)inputgetter();

		if(ch != 'y')
		{
			roundssofar++;

			screenclear();

			screenrefresh();

			goto beginning;
		}

	endmenow:
#ifdef INITNCURSESNOW
		endwin();
#endif
	
		return 0;
	}
}
