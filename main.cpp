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

#include "alldefines.h"

#include "initvideo.h"

#include "ncursesinput.h"

#include "inputgetter.h"

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

	if(argc == 2)
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

#if defined(_MSC_VER)
                if(!fileExists("SaveFile.txt"))
#else
                if(access("SaveFile.txt", F_OK ) == -1)
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
                if(fileExists("SaveFile.txt"))
#else
                if(access("SaveFile.txt", F_OK ) != -1)
#endif
 		{
			FILE *fp11 = fopen("SaveFile.txt", "r");
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
	#define aicharacters 4
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

	#endif

	ch = 'l';

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
			myplayer[i].weaponsdamage1.damage = (int *)malloc(sizeof(int) * allitems);
			myplayer[i].weaponsdamage1.rangex = (int *)malloc(sizeof(int) * allitems);
			myplayer[i].weaponsdamage1.rangey = (int *)malloc(sizeof(int) * allitems);
		}

		for(int i = 0; i < maxplayers; i++)
		{
			myplayer[i].shieldsdamage1.damage = (int *)malloc(sizeof(int) * alldefenseitems);
		}

		for(int i = 0; i < maxenemies; i++)
		{
			myai[i].weaponsdamage1.damage = (int *)malloc(sizeof(int) * allitemsenemies);
			myai[i].weaponsdamage1.rangex = (int *)malloc(sizeof(int) * allitemsenemies);
			myai[i].weaponsdamage1.rangey = (int *)malloc(sizeof(int) * allitemsenemies);
		}

		for(int i = 0; i < maxenemies; i++)
		{
			myai[i].shieldsdamage1.damage = (int *)malloc(sizeof(int) * alldefenseitemsenemies);
		}
		
		char* item[allitems];

		fp1 = fopen("PLAYERWEAPONS.txt", "r");

		for(int i = 0; i < allitems; i++)
		{
			loadstring(lineamount, &item[i], fp1);
		}

		fclose(fp1);

		char* itemdamage[alldefenseitems];

		fp1 = fopen("PLAYERDEFENSE.txt", "r");

		for(int i = 0; i < alldefenseitems; i++)
		{
			loadstring(lineamount, &itemdamage[i], fp1);
		}

		fclose(fp1);

		char* itemenemies[allitemsenemies];
		
		fp1 = fopen("AIWEAPONS.txt", "r");

		for(int i = 0; i < allitemsenemies; i++)
		{
			loadstring(lineamount, &itemenemies[i], fp1);
		}

		fclose(fp1);

		char* itemdamageenemies[alldefenseitemsenemies];
		itemdamageenemies[0] = const_cast<char *>("Short_Shield");
		itemdamageenemies[1] = const_cast<char *>("Long_Shield");
		itemdamageenemies[2] = const_cast<char *>("Metal_Shield");
		itemdamageenemies[3] = const_cast<char *>("Iron_Shield");
		itemdamageenemies[4] = const_cast<char *>("Steel_Shield");


		int* damage = (int *)malloc(sizeof(int) * allitems);

		fp1 = fopen("PLAYERWEAPONSDAMAGE.txt", "r");

		for(int i = 0; i < allitems; i++)
		{
			loadnumber(lineamount, &damage[i], fp1);
		}

		fclose(fp1);

		int* rangey = (int *)malloc(sizeof(int) * allitems);

		fp1 = fopen("PLAYERWEAPONSRANGEY.txt", "r");

		for(int i = 0; i < allitems; i++)
		{
			loadnumber(lineamount, &rangey[i], fp1);
		}

		fclose(fp1);

		int* rangex = (int *)malloc(sizeof(int) * allitems);

		fp1 = fopen("PLAYERWEAPONSRANGEX.txt", "r");

		for(int i = 0; i < allitems; i++)
		{
			loadnumber(lineamount, &rangex[i], fp1);
		}

		fclose(fp1);

		int* damageenemies = (int *)malloc(sizeof(int) * allitemsenemies);

		fp1 = fopen("AIWEAPONSDAMAGE.txt", "r");

		for(int i = 0; i < allitemsenemies; i++)
		{
			loadnumber(lineamount, &damageenemies[i], fp1);
		}

		fclose(fp1);

		int* rangeyenemies = (int *)malloc(sizeof(int) * allitemsenemies);

		fp1 = fopen("AIWEAPONSRANGEY.txt", "r");

		for(int i = 0; i < allitemsenemies; i++)
		{
			loadnumber(lineamount, &rangeyenemies[i], fp1);
		}

		fclose(fp1);

		int* rangexenemies = (int *)malloc(sizeof(int) * allitemsenemies);

		fp1 = fopen("AIWEAPONSRANGEX.txt", "r");

		for(int i = 0; i < allitemsenemies; i++)
		{
			loadnumber(lineamount, &rangexenemies[i], fp1);
		}

		fclose(fp1);

		int* shielddamage = (int *)malloc(sizeof(int) * alldefenseitems);

		fp1 = fopen("PLAYERSHIELDDAMAGE.txt", "r");

		for(int i = 0; i < alldefenseitems; i++)
		{
			loadnumber(lineamount, &shielddamage[i], fp1);
		}

		fclose(fp1);

		int* shielddamageenemies = (int *)malloc(sizeof(int) * alldefenseitemsenemies);

		fp1 = fopen("AISHIELDDAMAGE.txt", "r");

		for(int i = 0; i < alldefenseitemsenemies; i++)
		{
			loadnumber(lineamount, &shielddamageenemies[i], fp1);
		}

		fclose(fp1);

		char* playercharacter1[playercharacters];

		fp1 = fopen("PLAYERCHARACTER.txt", "r");

		for(int i = 0; i < playercharacters; i++)
		{
			loadstring(lineamount, &playercharacter1[i], fp1);
		}

		fclose(fp1);

		char* aicharacter1[aicharacters];
		aicharacter1[0] = const_cast<char *>("Human");
		aicharacter1[1] = const_cast<char *>("Orc");
		aicharacter1[2] = const_cast<char *>("Elf");
		aicharacter1[3] = const_cast<char *>("Dwarf");

		char* playersigns[playercharacters];

		fp1 = fopen("PLAYERSIGN.txt", "r");

		for(int i = 0; i < playercharacters; i++)
		{
			loadstring(lineamount, &playersigns[i], fp1);
		}

		fclose(fp1);

		char* aisigns[aicharacters];
		aisigns[0] = const_cast<char *>("h");
		aisigns[1] = const_cast<char *>("o");
		aisigns[2] = const_cast<char *>("e");
		aisigns[3] = const_cast<char *>("d");

		int playerhitpoints[playercharacters];
		
		fp1 = fopen("PLAYERHITPOINTS.txt", "r");

		for(int i = 0; i < playercharacters; i++)
		{
			loadnumber(lineamount, &playerhitpoints[i], fp1);
		}

		fclose(fp1);

		int aihitpoints[aicharacters];
		aihitpoints[0] = 1500;
		aihitpoints[1] = 2000;
		aihitpoints[2] = 1000;
		aihitpoints[3] = 2200;

		int playerdefense[playercharacters];
		
		fp1 = fopen("PLAYERDEFENSEVALUES.txt", "r");

		for(int i = 0; i < playercharacters; i++)
		{
			loadnumber(lineamount, &playerdefense[i], fp1);
		}

		fclose(fp1);

		int aidefense[aicharacters];
		aidefense[0] = 10;
		aidefense[1] = 30;
		aidefense[2] = 3;
		aidefense[3] = 20;

		int playerattack[playercharacters];

		fp1 = fopen("PLAYERATTACK.txt", "r");

		for(int i = 0; i < playercharacters; i++)
		{
			loadnumber(lineamount, &playerattack[i], fp1);
		}

		fclose(fp1);

		int aiattack[aicharacters];
		aiattack[0] = 10;
		aiattack[1] = 20;
		aiattack[2] = 8;
		aiattack[3] = 15;


		char* playermagicitems[playermagiclist];
		
		fp1 = fopen("PLAYERMAGICS.txt", "r");

		for(int i = 0; i < playermagiclist; i++)
		{
			loadstring(lineamount, &playermagicitems[i], fp1);
		}

		fclose(fp1);

		char* aimagicitems[aimagiclist];
		aimagicitems[0] = const_cast<char *>("Fire");
		aimagicitems[1] = const_cast<char *>("Wind");
		aimagicitems[2] = const_cast<char *>("Ice");
		aimagicitems[3] = const_cast<char *>("Water");
		aimagicitems[4] = const_cast<char *>("Lightning");

		int playermagicdamage[playermagiclist];
		
		fp1 = fopen("PLAYERMAGICSDAMAGE.txt", "r");

		for(int i = 0; i < playermagiclist; i++)
		{
			loadnumber(lineamount, &playermagicdamage[i], fp1);
		}

		fclose(fp1);

		int aimagicdamage[aimagiclist];
		aimagicdamage[0] = 80;
		aimagicdamage[1] = 70;
		aimagicdamage[2] = 60;
		aimagicdamage[3] = 50;
		aimagicdamage[4] = 40;

		int playermagicdistance[playermagiclist];
		
		fp1 = fopen("PLAYERMAGICSDISTANCE.txt", "r");

		for(int i = 0; i < playermagiclist; i++)
		{
			loadnumber(lineamount, &playermagicdistance[i], fp1);
		}

		fclose(fp1);

		int aimagicdistance[aimagiclist];
		aimagicdistance[0] = 8;
		aimagicdistance[1] = 8;
		aimagicdistance[2] = 8;
		aimagicdistance[3] = 8;
		aimagicdistance[4] = 8;

		int playermagicresist[playercharacters];
		
		fp1 = fopen("PLAYERMAGICRESISTANCE.txt", "r");

		for(int i = 0; i < playercharacters; i++)
		{
			loadnumber(lineamount, &playermagicresist[i], fp1);
		}

		fclose(fp1);

		int aimagicresist[aicharacters];
		aimagicresist[0] = 20;
		aimagicresist[1] = 5;
		aimagicresist[2] = 40;
		aimagicresist[3] = 10;

		int playermagicpoints[playercharacters];
		
		fp1 = fopen("PLAYERMAGICPOINTS.txt", "r");

		for(int i = 0; i < playercharacters; i++)
		{
			loadnumber(lineamount, &playermagicpoints[i], fp1);
		}

		fclose(fp1);

		int aimagicpoints[aicharacters];
		aimagicpoints[0] = 400;
		aimagicpoints[1] = 200;
		aimagicpoints[2] = 500;
		aimagicpoints[3] = 100;

		int playermagiccost[playermagiclist];

		fp1 = fopen("PLAYERMAGICSCOST.txt", "r");

		for(int i = 0; i < playermagiclist; i++)
		{
			loadnumber(lineamount, &playermagiccost[i], fp1);
		}

		fclose(fp1);

		int aimagiccost[aimagiclist];
		aimagiccost[0] = 40;
		aimagiccost[1] = 40;
		aimagiccost[2] = 40;
		aimagiccost[3] = 40;
		aimagiccost[4] = 40;

		char* playerarmor[allarmor];

		fp1 = fopen("PLAYERARMOR.txt", "r");

		for(int i = 0; i < allarmor; i++)
		{
			loadstring(lineamount, &playerarmor[i], fp1);
		}

		fclose(fp1);

		char* aiarmor[allarmorenemies];
		aiarmor[0] = const_cast<char *>("Weak armor");
		aiarmor[1] = const_cast<char *>("Light armor");
		aiarmor[2] = const_cast<char *>("Medium armor");
		aiarmor[3] = const_cast<char *>("Heavy armor");
		aiarmor[4] = const_cast<char *>("Super armor");

		int playerarmorpts[allarmor];
		
		fp1 = fopen("PLAYERARMORPOINTS.txt", "r");

		for(int i = 0; i < allarmor; i++)
		{
			loadnumber(lineamount, &playerarmorpts[i], fp1);
		}

		fclose(fp1);

		int aiarmorpts[allarmorenemies];
		aiarmorpts[0] = 3;
		aiarmorpts[1] = 6;
		aiarmorpts[2] = 9;
		aiarmorpts[3] = 12;
		aiarmorpts[4] = 15;

		int playerarmordistancex[allarmor];

		fp1 = fopen("PLAYERARMORDISTANCEX.txt", "r");

		for(int i = 0; i < allarmor; i++)
		{
			loadnumber(lineamount, &playerarmordistancex[i], fp1);
		}

		fclose(fp1);

		int aiarmordistancex[allarmorenemies];
		aiarmordistancex[0] = 3;
		aiarmordistancex[1] = 4;
		aiarmordistancex[2] = 5;
		aiarmordistancex[3] = 6;
		aiarmordistancex[4] = 7;

		int playerarmordistancey[allarmor];
		
		fp1 = fopen("PLAYERARMORDISTANCEY.txt", "r");

		for(int i = 0; i < allarmor; i++)
		{
			loadnumber(lineamount, &playerarmordistancey[i], fp1);
		}

		fclose(fp1);

		int aiarmordistancey[allarmorenemies];
		aiarmordistancey[0] = 3;
		aiarmordistancey[1] = 4;
		aiarmordistancey[2] = 5;
		aiarmordistancey[3] = 6;
		aiarmordistancey[4] = 7;

		for(int i = 0; i < maxplayers; i++)
		{
			myplayer[i].randomitem = rand() % allitems;
		}
	
		for(int i = 0; i < maxenemies; i++)
		{
			myai[i].randomitem = rand() % allitemsenemies;
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
			myplayer[i].character1.randomcharacter = rand() % playercharacters;
		}

		for(int i = 0; i < maxenemies; i++)
		{
			myai[i].character1.randomcharacter = rand() % aicharacters;
		}

		for(int i = 0; i < maxplayers; i++)
		{
			myplayer[i].magic1.randommagic = rand() % playermagiclist;
		}

		for(int i = 0; i < maxenemies; i++)
		{
			myai[i].magic1.randommagic = rand() % aimagiclist;
		}

		for(int i = 0; i < maxplayers; i++)
		{
			myplayer[i].armor1.randomarmor = rand() % allarmor;
		}

		for(int i = 0; i < maxenemies; i++)
		{
			myai[i].armor1.randomarmor = rand() % allarmorenemies;
		}

		for(int i = 0; i < maxplayers; i++)
		{
			for(int j = 0; j < allmagics; j++)
			{
				myplayer[i].magic1.magicitems[j] = const_cast<char *>("Empty");
			}

			for(int j = 0; j < allitems; j++)
			{
				myplayer[i].weapontype.item[j] = const_cast<char *>("Empty");
			}

			for(int j = 0; j < alldefenseitems; j++)
			{
				myplayer[i].shieldstype.item[j] = const_cast<char *>("Empty");
			}

			for(int j = 0; j < allarmor; j++)
			{
				myplayer[i].armor1.item[j] = const_cast<char *>("Empty");
			}

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
			myplayer[i].weapontype.equiped = const_cast<char *>("NULL");

			myplayer[i].character1.character = playercharacter1[myplayer[i].character1.randomcharacter];
			myplayer[i].character1.sign = playersigns[myplayer[i].character1.randomcharacter];
			myplayer[i].character1.hitpoints = playerhitpoints[myplayer[i].character1.randomcharacter];
			myplayer[i].character1.defense = playerdefense[myplayer[i].character1.randomcharacter];
			myplayer[i].character1.attack = playerattack[myplayer[i].character1.randomcharacter];

			myplayer[i].weaponsdamage1.item = item[myplayer[i].randomitem];

			myplayer[i].charactersign = myplayer[i].character1.sign;
			myplayer[i].defensepoints = myplayer[i].character1.defense;
			myplayer[i].hitpoints = myplayer[i].character1.hitpoints;

			myplayer[i].magic1.magiccount = 0;

			myplayer[i].weapontype.damage = damage[myplayer[i].randomitem];
			myplayer[i].weapontype.rangey = rangey[myplayer[i].randomitem];
			myplayer[i].weapontype.rangex = rangex[myplayer[i].randomitem];
			myplayer[i].weapontype.numberitems = allitems;

			for(int j = 0; j < allitems; j++)
			{
				myplayer[i].weaponsdamage1.damage[j] = damage[j];
				myplayer[i].weaponsdamage1.rangey[j] = rangey[j];
				myplayer[i].weaponsdamage1.rangex[j] = rangex[j];
			}

			myplayer[i].shieldstype.equiped = itemdamage[myplayer[i].shieldsrandomitem];

			myplayer[i].shield = myplayer[i].shieldstype.equiped;

			myplayer[i].shieldstype.damage = shielddamage[myplayer[i].shieldsrandomitem];
			myplayer[i].shieldstype.numberitems = alldefenseitems;

			myplayer[i].shieldsdamage1.item = itemdamage[myplayer[i].shieldsrandomitem];

			for(int j = 0; j < alldefenseitems; j++)
			{
				myplayer[i].shieldsdamage1.damage[j] = shielddamage[j];
			}

			myplayer[i].magic1.equiped = playermagicitems[myplayer[i].magic1.randommagic];
			myplayer[i].magic1.rangey = playermagicdistance[myplayer[i].magic1.randommagic];
			myplayer[i].magic1.rangex = playermagicdistance[myplayer[i].magic1.randommagic];
			myplayer[i].magic1.damage = playermagicdamage[myplayer[i].magic1.randommagic];

			myplayer[i].magicattack = myplayer[i].magic1.damage;

			myplayer[i].character1.magicresist = playermagicresist[myplayer[i].character1.randomcharacter];

			myplayer[i].magicpoints = playermagicpoints[myplayer[i].character1.randomcharacter];

			myplayer[i].magic1.cost = playermagiccost[myplayer[i].magic1.randommagic];

			myplayer[i].weapontype.numberitems = allitems;

			myplayer[i].magic1.magicitems[myplayer[i].magic1.magiccount] = playermagicitems[myplayer[i].magic1.randommagic];
			
			myplayer[i].magic1.magiccount++;

			myplayer[i].magic1.nextrandommagic = myplayer[i].magic1.randommagic;

			while(myplayer[i].magic1.nextrandommagic == myplayer[i].magic1.randommagic)
			{
				myplayer[i].magic1.nextrandommagic = rand() % playermagiclist;
			}

			myplayer[i].magic1.magicitems[myplayer[i].magic1.magiccount] = playermagicitems[myplayer[i].magic1.nextrandommagic];

			myplayer[i].magic1.magiccount++;

			myplayer[i].magic1.nextrandommagic2 = myplayer[i].magic1.randommagic;

			while(myplayer[i].magic1.nextrandommagic2 == myplayer[i].magic1.randommagic || myplayer[i].magic1.nextrandommagic2 == myplayer[i].magic1.nextrandommagic)
			{
				myplayer[i].magic1.nextrandommagic2 = rand() % playermagiclist;
			}

			myplayer[i].magic1.magicitems[myplayer[i].magic1.magiccount] = playermagicitems[myplayer[i].magic1.nextrandommagic2];

			myplayer[i].magic1.magiccount++;

			myplayer[i].weapontype.weaponcount = 0;

			myplayer[i].weapontype.randomweapon = myplayer[i].randomitem;

			myplayer[i].weapontype.item[myplayer[i].weapontype.weaponcount] = item[myplayer[i].weapontype.randomweapon];

			myplayer[i].weapontype.weaponcount++;

			myplayer[i].weapontype.nextrandomweapon = myplayer[i].weapontype.randomweapon;

			while(myplayer[i].weapontype.nextrandomweapon == myplayer[i].weapontype.randomweapon)
			{
				myplayer[i].weapontype.nextrandomweapon = rand() % allitems;
			}

			myplayer[i].weapontype.item[myplayer[i].weapontype.weaponcount] = item[myplayer[i].weapontype.nextrandomweapon];

			myplayer[i].weapontype.equiped = item[myplayer[i].weapontype.randomweapon];

			myplayer[i].weapon = myplayer[i].weapontype.equiped;

			myplayer[i].weapontype.weaponcount++;

			myplayer[i].weapontype.nextrandomweapon2 = myplayer[i].weapontype.randomweapon;

			while(myplayer[i].weapontype.nextrandomweapon2 == myplayer[i].weapontype.nextrandomweapon || myplayer[i].weapontype.nextrandomweapon2 == myplayer[i].weapontype.randomweapon)
			{
				myplayer[i].weapontype.nextrandomweapon2 = rand() % allitems;
			}

			myplayer[i].weapontype.item[myplayer[i].weapontype.weaponcount] = item[myplayer[i].weapontype.nextrandomweapon2];

			myplayer[i].weapontype.weaponcount++;

			myplayer[i].shieldstype.shieldcount = 0;

			myplayer[i].shieldstype.randomshield = myplayer[i].shieldsrandomitem;

			myplayer[i].shieldstype.item[myplayer[i].shieldstype.shieldcount] = itemdamage[myplayer[i].shieldstype.randomshield];

			myplayer[i].shieldstype.equiped = myplayer[i].shieldstype.item[0];

			myplayer[i].shieldstype.shieldcount++;

			myplayer[i].shieldstype.nextrandomshield = myplayer[i].shieldstype.randomshield;

			while(myplayer[i].shieldstype.nextrandomshield == myplayer[i].shieldstype.randomshield)
			{
				myplayer[i].shieldstype.nextrandomshield = rand() % alldefenseitems;
			}

			myplayer[i].shieldstype.item[myplayer[i].shieldstype.shieldcount] = itemdamage[myplayer[i].shieldstype.nextrandomshield];

			myplayer[i].shieldstype.shieldcount++;

			myplayer[i].shieldstype.nextrandomshield2 = myplayer[i].shieldstype.randomshield;

			while(myplayer[i].shieldstype.nextrandomshield2 == myplayer[i].shieldstype.nextrandomshield || myplayer[i].shieldstype.nextrandomshield2 == myplayer[i].shieldstype.randomshield)
			{
				myplayer[i].shieldstype.nextrandomshield2 = rand() % alldefenseitems;
			}

			myplayer[i].shieldstype.item[myplayer[i].shieldstype.shieldcount] = itemdamage[myplayer[i].shieldstype.nextrandomshield2];

			myplayer[i].shieldstype.shieldcount++;

			myplayer[i].armor1.armorcount = 0;

			myplayer[i].armor1.item[myplayer[i].armor1.armorcount] = playerarmor[myplayer[i].armor1.randomarmor];

			myplayer[i].armor1.armorcount++;

			myplayer[i].armor1.nextrandomarmor = myplayer[i].armor1.randomarmor;

			while(myplayer[i].armor1.nextrandomarmor == myplayer[i].armor1.randomarmor)
			{
				myplayer[i].armor1.nextrandomarmor = rand() % allarmor;
			}

			myplayer[i].armor1.item[myplayer[i].armor1.armorcount] = playerarmor[myplayer[i].armor1.nextrandomarmor];

			myplayer[i].armor1.armorcount++;

			myplayer[i].armor1.nextrandomarmor2 = myplayer[i].armor1.randomarmor;

			while(myplayer[i].armor1.nextrandomarmor2 == myplayer[i].armor1.nextrandomarmor || myplayer[i].armor1.nextrandomarmor2 == myplayer[i].armor1.randomarmor)
			{
				myplayer[i].armor1.nextrandomarmor2 = rand() % allarmor;
			}

			myplayer[i].armor1.item[myplayer[i].armor1.armorcount] = playerarmor[myplayer[i].armor1.nextrandomarmor2];

			myplayer[i].armor1.armorcount++;

			for (int j = 0; j < allarmor; j++)
			{
				myplayer[i].armor1.protections[j] = playerarmorpts[j];
			}

			myplayer[i].armor1.rangey = playerarmordistancey[myplayer[i].armor1.randomarmor];

			myplayer[i].armor1.rangex = playerarmordistancex[myplayer[i].armor1.randomarmor];

			myplayer[i].armor1.protection = playerarmorpts[myplayer[i].armor1.randomarmor];

			myplayer[i].armor1.equiped = playerarmor[myplayer[i].armor1.randomarmor];
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
				myai[i].magic1.magicitems[j] = const_cast<char *>("Empty");
			}

			for(int j = 0; j < allitemsenemies; j++)
			{
				myai[i].weapontype.item[j] = const_cast<char *>("Empty");
			}

			for(int j = 0; j < alldefenseitemsenemies; j++)
			{
				myai[i].shieldstype.item[j] = const_cast<char *>("Empty");
			}

			for(int j = 0; j < allarmorenemies; j++)
			{
				myai[i].armor1.item[j] = const_cast<char *>("Empty");
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
			myai[i].weapontype.equiped = const_cast<char *>("NULL");

			myai[i].character1.character = aicharacter1[myai[i].character1.randomcharacter];
			myai[i].character1.sign = aisigns[myai[i].character1.randomcharacter];
			myai[i].character1.hitpoints = aihitpoints[myai[i].character1.randomcharacter];
			myai[i].character1.defense = aidefense[myai[i].character1.randomcharacter];
			myai[i].character1.attack = aiattack[myai[i].character1.randomcharacter];

			myai[i].weaponsdamage1.item = itemenemies[myai[i].randomitem];

			myai[i].charactersign = myai[i].character1.sign;
			myai[i].defensepoints = myai[i].character1.defense;
			myai[i].hitpoints = myai[i].character1.hitpoints;

			myai[i].weapontype.damage = damageenemies[myai[i].randomitem];
			myai[i].weapontype.rangey = rangeyenemies[myai[i].randomitem];
			myai[i].weapontype.rangex = rangexenemies[myai[i].randomitem];

			for(int j = 0; j < allitemsenemies; j++)
			{
				myai[i].weaponsdamage1.damage[j] = damageenemies[j];
				myai[i].weaponsdamage1.rangey[j] = rangeyenemies[j];
				myai[i].weaponsdamage1.rangex[j] = rangexenemies[j];
			}

			myai[i].shieldstype.equiped = itemdamageenemies[myai[i].shieldsrandomitem];

			myai[i].shield = myai[i].shieldstype.equiped;

			myai[i].shieldstype.damage = shielddamageenemies[myai[i].shieldsrandomitem];
			myai[i].shieldstype.numberitems = alldefenseitemsenemies;

			myai[i].shieldsdamage1.item = itemdamageenemies[myai[i].shieldsrandomitem];

			myai[i].magic1.magiccount = 0;

			myai[i].magic1.equiped = aimagicitems[myai[i].magic1.randommagic];
			myai[i].magic1.rangey = aimagicdistance[myai[i].magic1.randommagic];
			myai[i].magic1.rangex = aimagicdistance[myai[i].magic1.randommagic];
			myai[i].magic1.damage = aimagicdamage[myai[i].magic1.randommagic];

			myai[i].magicattack = myai[i].magic1.damage;

			myai[i].character1.magicresist = aimagicresist[myai[i].character1.randomcharacter];

			myai[i].magicpoints = aimagicpoints[myai[i].character1.randomcharacter];
		
			myai[i].magic1.cost = aimagiccost[myai[i].magic1.randommagic];

			myai[i].weapontype.numberitems = allitemsenemies;

			myai[i].armor1.equiped = aiarmor[myai[i].armor1.randomarmor];

			myai[i].armor1.protection = aiarmorpts[myai[i].armor1.randomarmor];

			myai[i].armor1.rangey = aiarmordistancey[myai[i].armor1.randomarmor];

			myai[i].armor1.rangex = aiarmordistancex[myai[i].armor1.randomarmor];

			for(int j = 0; j < allitemsenemies; j++)
			{
				myai[i].weaponsdamage1.damage[j] = damageenemies[j];
				myai[i].weaponsdamage1.rangey[j] = rangeyenemies[j];
				myai[i].weaponsdamage1.rangex[j] = rangexenemies[j];
			}

			for(int j = 0; j < alldefenseitemsenemies; j++)
			{
				myai[i].shieldsdamage1.damage[j] = shielddamageenemies[j];
			}

			for(int j = 0; j < allarmorenemies; j++)
			{
				myai[i].armor1.protections[j] = aiarmorpts[j];
			}

			myai[i].magic1.magiccount = 0;

			myai[i].magic1.magicitems[myai[i].magic1.magiccount] = aimagicitems[myai[i].magic1.randommagic];

			myai[i].magic1.nextrandommagic = myai[i].magic1.randommagic;

			myai[i].magic1.magiccount++;

			while(myai[i].magic1.nextrandommagic == myai[i].magic1.randommagic)
			{
				myai[i].magic1.nextrandommagic = rand() % allmagicsenemies;
			}

			myai[i].magic1.magicitems[myai[i].magic1.magiccount] = aimagicitems[myai[i].magic1.nextrandommagic];

			myai[i].magic1.magiccount++;

			myai[i].magic1.nextrandommagic2 = myai[i].magic1.randommagic;

			while(myai[i].magic1.nextrandommagic2 == myai[i].magic1.nextrandommagic || myai[i].magic1.nextrandommagic2 == myai[i].magic1.randommagic)
			{
				myai[i].magic1.nextrandommagic2 = rand() % allmagicsenemies;
			}

			myai[i].magic1.magicitems[myai[i].magic1.magiccount] = aimagicitems[myai[i].magic1.nextrandommagic2];

			myai[i].magic1.magiccount++;

			myai[i].armor1.armorcount = 0;

			myai[i].armor1.item[myai[i].armor1.armorcount] = aiarmor[myai[i].armor1.randomarmor];
			
			myai[i].armor1.armorcount++;

			myai[i].armor1.nextrandomarmor = myai[i].armor1.randomarmor;

			while(myai[i].armor1.nextrandomarmor == myai[i].armor1.randomarmor)
			{
				myai[i].armor1.nextrandomarmor = rand() % allarmorenemies;
			}

			myai[i].armor1.item[myai[i].armor1.armorcount] = aiarmor[myai[i].armor1.nextrandomarmor];

			myai[i].armor1.armorcount++;

			myai[i].armor1.nextrandomarmor2 = myai[i].armor1.randomarmor;

			while(myai[i].armor1.nextrandomarmor2 == myai[i].armor1.nextrandomarmor || myai[i].armor1.nextrandomarmor2 == myai[i].armor1.randomarmor)
			{
				myai[i].armor1.nextrandomarmor2 = rand() % allarmorenemies;
			}
			
			myai[i].armor1.item[myai[i].armor1.armorcount] = aiarmor[myai[i].armor1.nextrandomarmor2];

			myai[i].armor1.armorcount++;

			myai[i].shieldstype.shieldcount = 0;

			myai[i].shieldstype.randomshield = myai[i].shieldsrandomitem;

			myai[i].shieldstype.item[myai[i].shieldstype.shieldcount] = itemdamageenemies[myai[i].shieldstype.randomshield];

			myai[i].shieldstype.shieldcount++;

			myai[i].shieldstype.nextrandomshield = myai[i].shieldstype.randomshield;

			while(myai[i].shieldstype.nextrandomshield == myai[i].shieldstype.randomshield)
			{
				myai[i].shieldstype.nextrandomshield = rand() % alldefenseitemsenemies;
			}

			myai[i].shieldstype.item[myai[i].shieldstype.shieldcount] = itemdamageenemies[myai[i].shieldstype.nextrandomshield];

			myai[i].shieldstype.shieldcount++;

			myai[i].shieldstype.nextrandomshield2 = myai[i].shieldstype.randomshield;

			while(myai[i].shieldstype.nextrandomshield2 == myai[i].shieldstype.nextrandomshield || myai[i].shieldstype.nextrandomshield2 == myai[i].shieldstype.randomshield)
			{
				myai[i].shieldstype.nextrandomshield2 = rand() % alldefenseitemsenemies;
			}

			myai[i].shieldstype.item[myai[i].shieldstype.shieldcount] = itemdamageenemies[myai[i].shieldstype.nextrandomshield2];

			myai[i].shieldstype.shieldcount++;

			myai[i].weapontype.weaponcount = 0;

			myai[i].weapontype.randomweapon = myai[i].randomitem;

			myai[i].weapontype.item[myai[i].weapontype.weaponcount] = itemenemies[myai[i].weapontype.randomweapon];

			myai[i].weapontype.weaponcount++;

			myai[i].weapontype.nextrandomweapon = myai[i].weapontype.randomweapon;

			while(myai[i].weapontype.nextrandomweapon == myai[i].weapontype.randomweapon)
			{
				myai[i].weapontype.nextrandomweapon = rand() % allitemsenemies;
			}

			myai[i].weapontype.item[myai[i].weapontype.weaponcount] = itemenemies[myai[i].weapontype.nextrandomweapon];

			myai[i].weapontype.weaponcount++;

			myai[i].weapontype.nextrandomweapon2 = myai[i].weapontype.randomweapon;

			while(myai[i].weapontype.nextrandomweapon2 == myai[i].weapontype.nextrandomweapon || myai[i].weapontype.nextrandomweapon2 == myai[i].weapontype.randomweapon)
			{
				myai[i].weapontype.nextrandomweapon2 = rand() % allitemsenemies;
			}

			myai[i].weapontype.item[myai[i].weapontype.weaponcount] = itemenemies[myai[i].weapontype.nextrandomweapon2];

			myai[i].weapontype.weaponcount++;
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

		for(int i = 0; i < maxenemies; i++)
		{
			myai[i].weapontype.equiped = myai[i].weapontype.item[myai[i].randomitem];
		}
		
#if defined(_MSC_VER)
		if(fileExists("SaveFile.txt"))
#else
		if(access("SaveFile.txt", F_OK ) != -1)
#endif
		{
			int j = 0;
		
			fp1 = fopen("SaveFile.txt", "r");
			
			for(int i = 0; i < maxplayers; i++)
			{
				loadnumber(lineamount, &maxplayers1, fp1);

				loadnumber(lineamount, &commandlineset, fp1);

				int temp1;
				loadnumber(lineamount, &temp1, fp1);
				theseed = static_cast<long>(temp1);

				loadnumber(lineamount, &myplayer[i].randomitem, fp1);

				loadnumber(lineamount, &myplayer[i].shieldsrandomitem, fp1);

				loadnumber(lineamount, &myplayer[i].character1.randomcharacter, fp1);

				loadnumber(lineamount, &myplayer[i].magic1.randommagic, fp1);

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

				loadstring(lineamount, &myplayer[i].weapontype.equiped, fp1);

				loadstring(lineamount, &myplayer[i].character1.character, fp1);

				loadstring(lineamount, &myplayer[i].character1.sign, fp1);

				loadnumber(lineamount, &myplayer[i].character1.hitpoints, fp1);

				loadnumber(lineamount, &myplayer[i].character1.defense, fp1);

				loadnumber(lineamount, &myplayer[i].character1.attack, fp1);

				loadstring(lineamount, &myplayer[i].weaponsdamage1.item, fp1);

				loadnumber(lineamount, &myplayer[i].defensepoints, fp1);

				loadnumber(lineamount, &myplayer[i].hitpoints, fp1);

				for(int q = 0; q < allitems; q++)
				{
					loadstring(lineamount, &myplayer[i].weapontype.item[q], fp1);
				}

				loadnumber(lineamount, &myplayer[i].weapontype.damage, fp1);

				loadnumber(lineamount, &myplayer[i].weapontype.rangey, fp1);

				loadnumber(lineamount, &myplayer[i].weapontype.rangex, fp1);

				loadnumber(lineamount, &myplayer[i].weapontype.numberitems, fp1);

				for(int q = 0; q < allitems; q++)
				{
					loadnumber(lineamount, &myplayer[i].weaponsdamage1.damage[q], fp1);
				}

				for(int q = 0; q < allitems; q++)
				{
					loadnumber(lineamount, &myplayer[i].weaponsdamage1.rangey[q], fp1);
				}

				for(int q = 0; q < allitems; q++)
				{
					loadnumber(lineamount, &myplayer[i].weaponsdamage1.rangex[q], fp1);
				}

				for(int q = 0; q < alldefenseitems; q++)
				{
					loadstring(lineamount, &myplayer[i].shieldstype.item[q], fp1);
				}

				loadstring(lineamount, &myplayer[i].shieldstype.equiped, fp1);

				loadnumber(lineamount, &myplayer[i].shieldstype.damage, fp1);

				loadnumber(lineamount, &myplayer[i].shieldstype.numberitems, fp1);

				loadstring(lineamount, &myplayer[i].shieldsdamage1.item, fp1);

				for(int q = 0; q < alldefenseitems; q++)
				{
					loadnumber(lineamount, &myplayer[i].shieldsdamage1.damage[q], fp1);
				}

				loadstring(lineamount, &myplayer[i].magic1.equiped, fp1);

				loadnumber(lineamount, &myplayer[i].magic1.rangey, fp1);

				loadnumber(lineamount, &myplayer[i].magic1.rangex, fp1);

				loadnumber(lineamount, &myplayer[i].magic1.damage, fp1);

				loadnumber(lineamount, &myplayer[i].magicattack, fp1);

				loadnumber(lineamount, &myplayer[i].character1.magicresist, fp1);

				loadnumber(lineamount, &myplayer[i].magicpoints, fp1);

				loadnumber(lineamount, &myplayer[i].magic1.cost, fp1);

				loadnumber(lineamount, &myplayer[i].weapontype.numberitems, fp1);

				loadstring(lineamount, &myplayer[i].weapontype.equiped, fp1);

				loadnumber(lineamount, &myplayer[i].magic1.magiccount, fp1);

				loadnumber(lineamount, &myplayer[i].magic1.nextrandommagic, fp1);
				
				for(int l = 0; l < allmagics; l++)
				{
					loadstring(lineamount, &myplayer[i].magic1.magicitems[l], fp1);
				}

				loadnumber(lineamount, &myplayer[i].magic1.nextrandommagic2, fp1);

				loadnumber(lineamount, &myplayer[i].weapontype.randomweapon, fp1);

				loadnumber(lineamount, &myplayer[i].weapontype.nextrandomweapon, fp1);

				loadnumber(lineamount, &myplayer[i].weapontype.nextrandomweapon2, fp1);

				for(int l = 0; l < allitems; l++)
				{
					loadstring(lineamount, &myplayer[i].weapontype.item[l], fp1);
				}

				loadnumber(lineamount, &myplayer[i].shieldstype.randomshield, fp1);

				loadnumber(lineamount, &myplayer[i].shieldstype.nextrandomshield, fp1);

				loadnumber(lineamount, &myplayer[i].shieldstype.nextrandomshield2, fp1);

				for(int l = 0; l < alldefenseitems; l++)
				{
					loadstring(lineamount, &myplayer[i].shieldstype.item[l], fp1);
				}

				loadnumber(lineamount, &myplayer[i].armor1.randomarmor, fp1);
				
				loadnumber(lineamount, &myplayer[i].armor1.nextrandomarmor, fp1);
				
				loadnumber(lineamount, &myplayer[i].armor1.nextrandomarmor2, fp1);
				
				loadstring(lineamount, &myplayer[i].armor1.equiped, fp1);
				
				loadnumber(lineamount, &myplayer[i].armor1.rangey, fp1);
				
				loadnumber(lineamount, &myplayer[i].armor1.rangex, fp1);
				
				loadnumber(lineamount, &myplayer[i].armor1.protection, fp1);
				
				for(int q = 0; q < allarmor; q++)
				{
					loadstring(lineamount, &myplayer[i].armor1.item[q], fp1);
				}
				
				for(int q = 0; q < allarmor; q++)
				{
					loadnumber(lineamount, &myplayer[i].armor1.protections[q], fp1);
				}
				
				loadnumber(lineamount, &myplayer[i].weapontype.weaponcount, fp1);
				
				loadnumber(lineamount, &myplayer[i].shieldstype.shieldcount, fp1);
				
				loadnumber(lineamount, &myplayer[i].armor1.armorcount, fp1);
			}
		
			for(int i = 0; i < maxenemies; i++)
			{
				loadnumber(lineamount, &myai[i].randomitem, fp1);

				loadnumber(lineamount, &myai[i].shieldsrandomitem, fp1);

				loadnumber(lineamount, &myai[i].character1.randomcharacter, fp1);

				loadnumber(lineamount, &myai[i].magic1.randommagic, fp1);

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

				loadstring(lineamount, &myai[i].weapontype.equiped, fp1);

				loadstring(lineamount, &myai[i].character1.character, fp1);

				loadstring(lineamount, &myai[i].character1.sign, fp1);

				loadnumber(lineamount, &myai[i].character1.hitpoints, fp1);

				loadnumber(lineamount, &myai[i].character1.defense, fp1);

				loadnumber(lineamount, &myai[i].character1.attack, fp1);

				loadstring(lineamount, &myai[i].weaponsdamage1.item, fp1);

				loadnumber(lineamount, &myai[i].defensepoints, fp1);

				loadnumber(lineamount, &myai[i].hitpoints, fp1);

				for(int q = 0; q < allitemsenemies; q++)
				{
					loadstring(lineamount, &myai[i].weapontype.item[q], fp1);
				}

				loadnumber(lineamount, &myai[i].weapontype.damage, fp1);

				loadnumber(lineamount, &myai[i].weapontype.rangey, fp1);

				loadnumber(lineamount, &myai[i].weapontype.rangex, fp1);

				loadnumber(lineamount, &myai[i].weapontype.numberitems, fp1);

				for(int q = 0; q < allitemsenemies; q++)
				{
					loadnumber(lineamount, &myai[i].weaponsdamage1.damage[q], fp1);
				}

				for(int q = 0; q < allitemsenemies; q++)
				{
					loadnumber(lineamount, &myai[i].weaponsdamage1.rangey[q], fp1);
				}

				for(int q = 0; q < allitemsenemies; q++)
				{
					loadnumber(lineamount, &myai[i].weaponsdamage1.rangex[q], fp1);
				}

				for(int q = 0; q < alldefenseitemsenemies; q++)
				{
					loadstring(lineamount, &myai[i].shieldstype.item[q], fp1);
				}

				loadstring(lineamount, &myai[i].shieldstype.equiped, fp1);

				loadnumber(lineamount, &myai[i].shieldstype.damage, fp1);

				loadnumber(lineamount, &myai[i].shieldstype.numberitems, fp1);

				loadstring(lineamount, &myai[i].shieldsdamage1.item, fp1);

				for(int q = 0; q < alldefenseitemsenemies; q++)
				{
					loadnumber(lineamount, &myai[i].shieldsdamage1.damage[q], fp1);
				}

				loadstring(lineamount, &myai[i].magic1.equiped, fp1);

				loadnumber(lineamount, &myai[i].magic1.rangey, fp1);

				loadnumber(lineamount, &myai[i].magic1.rangex, fp1);

				loadnumber(lineamount, &myai[i].magic1.damage, fp1);

				loadnumber(lineamount, &myai[i].magicattack, fp1);

				loadnumber(lineamount, &myai[i].character1.magicresist, fp1);

				loadnumber(lineamount, &myai[i].magicpoints, fp1);

				loadnumber(lineamount, &myai[i].magic1.cost, fp1);

				loadnumber(lineamount, &myai[i].weapontype.numberitems, fp1);

				loadstring(lineamount, &myai[i].weapontype.equiped, fp1);

				loadnumber(lineamount, &myai[i].magic1.magiccount, fp1);
				
				loadnumber(lineamount, &myai[i].magic1.nextrandommagic, fp1);
								
				for(int l = 0; l < allmagicsenemies; l++)
				{
					loadstring(lineamount, &myai[i].magic1.magicitems[l], fp1);
				}
				
				loadnumber(lineamount, &myai[i].magic1.nextrandommagic2, fp1);
				
				loadnumber(lineamount, &myai[i].weapontype.randomweapon, fp1);
				
				loadnumber(lineamount, &myai[i].weapontype.nextrandomweapon, fp1);
				
				loadnumber(lineamount, &myai[i].weapontype.nextrandomweapon2, fp1);
				
				for(int l = 0; l < allitemsenemies; l++)
				{
					loadstring(lineamount, &myai[i].weapontype.item[l], fp1);
				}
				
				loadnumber(lineamount, &myai[i].shieldstype.randomshield, fp1);
				
				loadnumber(lineamount, &myai[i].shieldstype.nextrandomshield, fp1);
				
				loadnumber(lineamount, &myai[i].shieldstype.nextrandomshield2, fp1);
				
				for(int l = 0; l < alldefenseitemsenemies; l++)
				{
					loadstring(lineamount, &myai[i].shieldstype.item[l], fp1);
				}
				
				loadnumber(lineamount, &myai[i].armor1.randomarmor, fp1);
								
				loadnumber(lineamount, &myai[i].armor1.nextrandomarmor, fp1);
								
				loadnumber(lineamount, &myai[i].armor1.nextrandomarmor2, fp1);
								
				loadstring(lineamount, &myai[i].armor1.equiped, fp1);
								
				loadnumber(lineamount, &myai[i].armor1.rangey, fp1);
								
				loadnumber(lineamount, &myai[i].armor1.rangex, fp1);
								
				loadnumber(lineamount, &myai[i].armor1.protection, fp1);
								
				for(int q = 0; q < allarmorenemies; q++)
				{
					loadstring(lineamount, &myai[i].armor1.item[q], fp1);
				}
								
				for(int q = 0; q < allarmorenemies; q++)
				{
					loadnumber(lineamount, &myai[i].armor1.protections[q], fp1);
				}
								
				loadnumber(lineamount, &myai[i].weapontype.weaponcount, fp1);
								
				loadnumber(lineamount, &myai[i].shieldstype.shieldcount, fp1);
								
				loadnumber(lineamount, &myai[i].armor1.armorcount, fp1);
			}

			loadnumber(lineamount, &roundssofar, fp1);

			loadnumber(lineamount, &positiony, fp1);

			loadnumber(lineamount, &rounds, fp1);

			loadnumber(lineamount, &positionx, fp1);
			
			fclose(fp1);

			remove("SaveFile.txt");
			
			savefile = 1;
		}
	
		char* winner = const_cast<char *>("ai");
	
		int replayer = 0;
	
		int positionxdiff;
	
		int positionydiff;
	
		struct hitpointspos hitpointspos1 = { terminalend - (maxplayers + maxenemies), 0, terminalend - (maxenemies), terminalendx};
	
		initvideo(hitpointsy, hitpointsx);

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
				videoprinterstats(hitpointspos1.y + i - positiony, 0, "Player %d is %s hp:%d mp:%d at:%d ma:%s %d def:%d w:%s sh:%s ar:%s md:%d", myplayer[i].count, myplayer[i].character1.character, myplayer[i].hitpoints, myplayer[i].magicpoints, myplayer[i].weapontype.damage + myplayer[i].character1.attack, myplayer[i].magic1.equiped, myplayer[i].magic1.damage, myplayer[i].defensepoints + myplayer[i].shieldstype.damage, myplayer[i].weapontype.equiped, myplayer[i].shieldstype.equiped, myplayer[i].armor1.equiped, myplayer[i].armor1.protection);
			}
		}

		for(int i = 0; i < maxenemies; i++)
		{
			if((hitpointspos1.ay + i) >= (positiony) && (positiony > (maxenemies)))
			{
				videoprinterstats(hitpointspos1.ay + i - positiony, 0, "AI %d is %s hp:%d mp:%d at:%d ma:%s %d def:%d w:%s sh:%s ar:%s md:%d", myai[i].count, myai[i].character1.character, myai[i].hitpoints, myai[i].magicpoints, myai[i].weapontype.damage + myai[i].character1.attack, myai[i].magic1.equiped, myai[i].magic1.damage, myai[i].defensepoints + myai[i].shieldstype.damage, myai[i].weapontype.equiped, myai[i].shieldstype.equiped, myai[i].armor1.equiped, myai[i].armor1.protection);
			}
		}
#ifdef INITNCURSESNOW
		move(myplayer[0].y - positiony, myplayer[0].x - positionx);

		refresh();
#endif

		int i = 0;
	
		while((ch = (RETURNTYPEVIDEO)inputgetter()) != 'q')
		{
			if(ch == 'S')
			{
#ifdef INITNCURSESNOW
				clear();
#endif
				videoprinternorm(0, 0, "Saving now and then exiting");
#ifdef INITNCURSESNOW
				refresh();
#endif

				fp1 = fopen("SaveFile.txt", "w");

				for(int i = 0; i < maxplayers; i++)
				{
					writenumber(lineBuffer, lineamount, maxplayers1, fp1);

					writenumber(lineBuffer, lineamount, commandlineset, fp1);

					writenumber(lineBuffer, lineamount, theseed, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].randomitem, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].shieldsrandomitem, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].character1.randomcharacter, fp1);
					
					writenumber(lineBuffer, lineamount, myplayer[i].magic1.randommagic, fp1);
				
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

					writestring(lineBuffer, lineamount, myplayer[i].weapontype.equiped, fp1);

					writestring(lineBuffer, lineamount, myplayer[i].character1.character, fp1);

					writestring(lineBuffer, lineamount, myplayer[i].character1.sign, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].character1.hitpoints, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].character1.defense, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].character1.attack, fp1);

					writestring(lineBuffer, lineamount, myplayer[i].weaponsdamage1.item, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].defensepoints, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].hitpoints, fp1);

					for(int q = 0; q < allitems; q++)
					{
						writestring(lineBuffer, lineamount, myplayer[i].weapontype.item[q], fp1);
						
					}

					writenumber(lineBuffer, lineamount, myplayer[i].weapontype.damage, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].weapontype.rangey, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].weapontype.rangex, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].weapontype.numberitems, fp1);

					for(int q = 0; q < allitems; q++)
					{
						writenumber(lineBuffer, lineamount, myplayer[i].weaponsdamage1.damage[q], fp1);
					}

					for(int q = 0; q < allitems; q++)
					{
						writenumber(lineBuffer, lineamount, myplayer[i].weaponsdamage1.rangey[q], fp1);
					}

					for(int q = 0; q < allitems; q++)
					{
						writenumber(lineBuffer, lineamount, myplayer[i].weaponsdamage1.rangex[q], fp1);
					}

					for(int q = 0; q < alldefenseitems; q++)
					{
						writestring(lineBuffer, lineamount, myplayer[i].shieldstype.item[q], fp1);
					}

					writestring(lineBuffer, lineamount, myplayer[i].shieldstype.equiped, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].shieldstype.damage, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].shieldstype.numberitems, fp1);

					writestring(lineBuffer, lineamount, myplayer[i].shieldsdamage1.item, fp1);

					for(int q = 0; q < alldefenseitems; q++)
					{
						writenumber(lineBuffer, lineamount, myplayer[i].shieldsdamage1.damage[q], fp1);
					}

					writestring(lineBuffer, lineamount, myplayer[i].magic1.equiped, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].magic1.rangey, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].magic1.rangex, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].magic1.damage, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].magicattack, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].character1.magicresist, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].magicpoints, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].magic1.cost, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].weapontype.numberitems, fp1);

					writestring(lineBuffer, lineamount, myplayer[i].weapontype.equiped, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].magic1.magiccount, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].magic1.nextrandommagic, fp1);
					
					for(int q = 0; q < allmagics; q++)
					{
						writestring(lineBuffer, lineamount, myplayer[i].magic1.magicitems[q], fp1);
					}

					writenumber(lineBuffer, lineamount, myplayer[i].magic1.nextrandommagic2, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].weapontype.randomweapon, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].weapontype.nextrandomweapon, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].weapontype.nextrandomweapon2, fp1);

					for(int q = 0; q < allitems; q++)
					{
						writestring(lineBuffer, lineamount, myplayer[i].weapontype.item[q], fp1);
					}
					
					writenumber(lineBuffer, lineamount, myplayer[i].shieldstype.randomshield, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].shieldstype.nextrandomshield, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].shieldstype.nextrandomshield2, fp1);

					for(int q = 0; q < alldefenseitems; q++)
					{
						writestring(lineBuffer, lineamount, myplayer[i].shieldstype.item[q], fp1);
					}

					writenumber(lineBuffer, lineamount, myplayer[i].armor1.randomarmor, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].armor1.nextrandomarmor, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].armor1.nextrandomarmor2, fp1);

					writestring(lineBuffer, lineamount, myplayer[i].armor1.equiped, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].armor1.rangey, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].armor1.rangex, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].armor1.protection, fp1);

					for(int q = 0; q < allarmor; q++)
					{
						writestring(lineBuffer, lineamount, myplayer[i].armor1.item[q], fp1);
					}

					for(int q = 0; q < allarmor; q++)
					{
						writenumber(lineBuffer, lineamount, myplayer[i].armor1.protections[q], fp1);
					}

					writenumber(lineBuffer, lineamount, myplayer[i].weapontype.weaponcount, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].shieldstype.shieldcount, fp1);

					writenumber(lineBuffer, lineamount, myplayer[i].armor1.armorcount, fp1);
				}

				for(int i = 0; i < maxenemies; i++)
				{
					writenumber(lineBuffer, lineamount, myai[i].randomitem, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].shieldsrandomitem, fp1);

					writenumber(lineBuffer, lineamount, myai[i].character1.randomcharacter, fp1);

					writenumber(lineBuffer, lineamount, myai[i].magic1.randommagic, fp1);
				
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

					writestring(lineBuffer, lineamount, myai[i].weapontype.equiped, fp1);

					writestring(lineBuffer, lineamount, myai[i].character1.character, fp1);

					writestring(lineBuffer, lineamount, myai[i].character1.sign, fp1);

					writenumber(lineBuffer, lineamount, myai[i].character1.hitpoints, fp1);

					writenumber(lineBuffer, lineamount, myai[i].character1.defense, fp1);

					writenumber(lineBuffer, lineamount, myai[i].character1.attack, fp1);

					writestring(lineBuffer, lineamount, myai[i].weaponsdamage1.item, fp1);

					writenumber(lineBuffer, lineamount, myai[i].defensepoints, fp1);

					writenumber(lineBuffer, lineamount, myai[i].hitpoints, fp1);

					for(int q = 0; q < allitemsenemies; q++)
					{
						writestring(lineBuffer, lineamount, myai[i].weapontype.item[q], fp1);
					}
					
					writenumber(lineBuffer, lineamount, myai[i].weapontype.damage, fp1);

					writenumber(lineBuffer, lineamount, myai[i].weapontype.rangey, fp1);

					writenumber(lineBuffer, lineamount, myai[i].weapontype.rangex, fp1);

					writenumber(lineBuffer, lineamount, myai[i].weapontype.numberitems, fp1);

					for(int q = 0; q < allitemsenemies; q++)
					{
						writenumber(lineBuffer, lineamount, myai[i].weaponsdamage1.damage[q], fp1);
					}

					for(int q = 0; q < allitemsenemies; q++)
					{
						writenumber(lineBuffer, lineamount, myai[i].weaponsdamage1.rangey[q], fp1);
					}

					for(int q = 0; q < allitemsenemies; q++)
					{
						writenumber(lineBuffer, lineamount, myai[i].weaponsdamage1.rangex[q], fp1);
					}

					for(int q = 0; q < alldefenseitemsenemies; q++)
					{
						writestring(lineBuffer, lineamount, myai[i].shieldstype.item[q], fp1);
					}

					writestring(lineBuffer, lineamount, myai[i].shieldstype.equiped, fp1);

					writenumber(lineBuffer, lineamount, myai[i].shieldstype.damage, fp1);

					writenumber(lineBuffer, lineamount, myai[i].shieldstype.numberitems, fp1);

					writestring(lineBuffer, lineamount, myai[i].shieldsdamage1.item, fp1);

					for(int q = 0; q < alldefenseitemsenemies; q++)
					{
						writenumber(lineBuffer, lineamount, myai[i].shieldsdamage1.damage[q], fp1);
					}

					writestring(lineBuffer, lineamount, myai[i].magic1.equiped, fp1);

					writenumber(lineBuffer, lineamount, myai[i].magic1.rangey, fp1);

					writenumber(lineBuffer, lineamount, myai[i].magic1.rangex, fp1);

					writenumber(lineBuffer, lineamount, myai[i].magic1.damage, fp1);

					writenumber(lineBuffer, lineamount, myai[i].magicattack, fp1);

					writenumber(lineBuffer, lineamount, myai[i].character1.magicresist, fp1);

					writenumber(lineBuffer, lineamount, myai[i].magicpoints, fp1);

					writenumber(lineBuffer, lineamount, myai[i].magic1.cost, fp1);

					writenumber(lineBuffer, lineamount, myai[i].weapontype.numberitems, fp1);

					writestring(lineBuffer, lineamount, myai[i].weapontype.equiped, fp1);

					writenumber(lineBuffer, lineamount, myai[i].magic1.magiccount, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].magic1.nextrandommagic, fp1);
										
					for(int q = 0; q < allmagicsenemies; q++)
					{
						writestring(lineBuffer, lineamount, myai[i].magic1.magicitems[q], fp1);
					}
					
					writenumber(lineBuffer, lineamount, myai[i].magic1.nextrandommagic2, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].weapontype.randomweapon, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].weapontype.nextrandomweapon, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].weapontype.nextrandomweapon2, fp1);
					
					for(int q = 0; q < allitemsenemies; q++)
					{
						writestring(lineBuffer, lineamount, myai[i].weapontype.item[q], fp1);
					}
										
					writenumber(lineBuffer, lineamount, myai[i].shieldstype.randomshield, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].shieldstype.nextrandomshield, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].shieldstype.nextrandomshield2, fp1);
					
					for(int q = 0; q < alldefenseitemsenemies; q++)
					{
						writestring(lineBuffer, lineamount, myai[i].shieldstype.item[q], fp1);
					}
					
					writenumber(lineBuffer, lineamount, myai[i].armor1.randomarmor, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].armor1.nextrandomarmor, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].armor1.nextrandomarmor2, fp1);
					
					writestring(lineBuffer, lineamount, myai[i].armor1.equiped, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].armor1.rangey, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].armor1.rangex, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].armor1.protection, fp1);
					
					for(int q = 0; q < allarmorenemies; q++)
					{
						writestring(lineBuffer, lineamount, myai[i].armor1.item[q], fp1);
					}
					
					for(int q = 0; q < allarmorenemies; q++)
					{
						writenumber(lineBuffer, lineamount, myai[i].armor1.protections[q], fp1);
					}
					
					writenumber(lineBuffer, lineamount, myai[i].weapontype.weaponcount, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].shieldstype.shieldcount, fp1);
					
					writenumber(lineBuffer, lineamount, myai[i].armor1.armorcount, fp1);
				}

				writenumber(lineBuffer, lineamount, roundssofar, fp1);

				writenumber(lineBuffer, lineamount, positiony, fp1);

				writenumber(lineBuffer, lineamount, rounds, fp1);
				
				writenumber(lineBuffer, lineamount, positionx, fp1);

				fclose(fp1);

#ifdef INITNCURSESNOW
				endwin();
#endif

				return 0;
			}

			if(ch == 'h')
			{
#ifdef INITNCURSESNOW
				clear();
#endif

				videoprinternorm(0, 0, "Press a to move left");
				videoprinternorm(1, 0, "Press d to move right");
				videoprinternorm(2, 0, "Press w to move up");
				videoprinternorm(3, 0, "Press s to move down");
				videoprinternorm(4, 0, "Press m to use magic");
				videoprinternorm(5, 0, "Press Shift+m to equip different magic, weapon, shield, and armor");
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
				videoprinternorm(16, 0, "Press Shift+s to save and quit");
				videoprinternorm(17, 0, "Press u to scroll up");
				videoprinternorm(18, 0, "Press j to scroll down");
				videoprinternorm(19, 0, "Press r to scroll left");
				videoprinternorm(20, 0, "Press f to scroll right");
				videoprinternorm(21, 0, "Press key to quit help");

#ifdef INITNCURSESNOW
				refresh();
#endif

				(RETURNTYPEVIDEO)inputgetter();

#ifdef INITNCURSESNOW
				move(myplayer[i].y, myplayer[i].x);

				refresh();
#endif
			}
#ifdef INITNCURSESNOW
			clear();
#endif

			if(ch == 'p')
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
			
			if(ch == 'n')
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
		
			if(ch == 'a')
			{
				myplayer[i].x = myplayer[i].x - 1;
			
				if(myplayer[i].x < 0)
				{
					myplayer[i].x = 0;
				}

				positionx = ((myplayer[i].x) / hitpointsx) * hitpointsx;
			}
		
			if(ch == 'd')
			{
				myplayer[i].x = myplayer[i].x + 1;
			
				if(myplayer[i].x > hitpointspos1.ax - 1)
				{
					myplayer[i].x = hitpointspos1.ax - 1;
				}

				positionx = ((myplayer[i].x) / hitpointsx) * hitpointsx;
			}
		
			if(ch == 'w')
			{
				myplayer[i].y = myplayer[i].y - 1;
			
				if(myplayer[i].y < 0)
				{
					myplayer[i].y = 0;
				}

				positiony = ((myplayer[i].y) / hitpointsy) * hitpointsy;
			}

			if(ch == 'u')
			{
#ifdef INITNCURSESNOW
				clear();
#endif

				positiony--;
				
				if(positiony < 0)
				{
					positiony = 0;
				}

#ifdef INITNCURSESNOW
				move(positiony, 0);

				refresh();
#endif
			}

			if(ch == 'j')
			{
#ifdef INITNCURSESNOW
				clear();
#endif

				positiony++;
				
				if(positiony > (terminalend + 1 - hitpointsy))
				{
					positiony = (terminalend + 1 - hitpointsy);
				}

#ifdef INITNCURSESNOW
				move(positiony, 0);

				refresh();
#endif
			}

			if(ch == 'r')
			{
				clear();

				positionx--;

				if(positionx < 0)
				{
					positionx = 0;
				}

				move(positionx, 0);

				refresh();
			}

			if(ch == 'f')
			{
				clear();

				positionx++;
				
				if(positionx > (terminalendx + 1 - hitpointsx))
				{
					positionx = (terminalendx + 1 - hitpointsx);
				}

				move(positionx, 0);

				refresh();
			}
		
			if(ch == 's')
			{
				myplayer[i].y = myplayer[i].y + 1;
			
				if(myplayer[i].y > (hitpointspos1.y - 1))
				{
					myplayer[i].y = (hitpointspos1.y - 1);
				}

				positiony = ((myplayer[i].y) / hitpointsy) * hitpointsy;
			}

			if (ch == 'c')
			{
#ifdef INITNCURSESNOW
				clear();
#endif

				int list = 0;
				int l = 0;
#ifdef INITNCURSESNOW
				int gotcharacter = '0';
#endif
				do
				{
#ifdef INITNCURSESNOW
					clear();
#endif

					if (gotcharacter == 'd')
					{
						list++;
					}

					if (list > 3)
					{
						list = 0;
					}

					videoprinterarg1(l, 0, "Player %d", i + 1);
					l++;

					if (list == 0)
					{
						while (strcmp(myplayer[i].magic1.magicitems[l - 1], "Empty") != 0)
						{
							videoprinterarg2(l, 0, "Magic item %d is %s", l, myplayer[i].magic1.magicitems[l - 1]);
							l++;
						}
					}

					if (list == 1)
					{
						while (strcmp(myplayer[i].weapontype.item[l - 1], "Empty") != 0)
						{
							videoprinterarg2(l, 0, "Weapon item %d is %s", l, myplayer[i].weapontype.item[l - 1]);
							l++;
						}
					}

					if (list == 2)
					{
						while (strcmp(myplayer[i].shieldstype.item[l - 1], "Empty") != 0)
						{
							videoprinterarg2(l, 0, "Shield item %d is %s", l, myplayer[i].shieldstype.item[l - 1]);
							l++;
						}
					}

					if (list == 3)
					{
						while (strcmp(myplayer[i].armor1.item[l - 1], "Empty") != 0)
						{
							videoprinterarg2(l, 0, "Armor item %d is %s", l, myplayer[i].armor1.item[l - 1]);
							l++;
						}
					}

					videoprinternorm(l, 0, "Press d to move to next category\n");

					l++;

					videoprinternorm(l, 0, "Press anything else to exit this menu\n");

					l = 0;

#ifdef INITNCURSESNOW
					move(0, 0);

					refresh();
#endif
				} while ((gotcharacter = (RETURNTYPEVIDEO)inputgetter()) == 'd');

				list = 0;
				l = 0;

#ifdef INITNCURSESNOW
				move(myplayer[i].y, myplayer[i].x);

				clear();

				refresh();
#endif
			}


			if(ch == 'i')
			{
#ifdef INITNCURSESNOW
				clear();
#endif

				int list = 0;
				int l = 0;
#ifdef INITNCURSESNOW
				int gotcharacter = '0';
#endif

				int theenemy = 0;

				do
				{
#ifdef INITNCURSESNOW
					clear();
#endif

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
					
					if(list > 3)
					{
						list = 0;
					}
					
					videoprinterarg1(l, 0, "AI %d", theenemy + 1);

					if(list == 0)
					{
						while(strcmp(myai[theenemy].magic1.magicitems[l], "Empty") != 0)
						{
							videoprinterarg2(l+1, 0, "Magic item %d is %s", l + 1, myai[theenemy].magic1.magicitems[l]);
							l++;
						}
					}
					
					if(list == 1)
					{
						while(strcmp(myai[theenemy].weapontype.item[l], "Empty") != 0)
						{
							videoprinterarg2(l+1, 0, "Weapon item %d is %s", l + 1, myai[theenemy].weapontype.item[l]);
							l++;
						}
					}
					
					if(list == 2)
					{
						while(strcmp(myai[theenemy].shieldstype.item[l], "Empty") != 0)
						{
							videoprinterarg2(l+1, 0, "Shield item %d is %s", l + 1, myai[theenemy].shieldstype.item[l]);
							l++;
						}
					}
					
					if(list == 3)
					{
						while(strcmp(myai[theenemy].armor1.item[l], "Empty") != 0)
						{
							videoprinterarg2(l+1, 0, "Armor item %d is %s", l + 1, myai[theenemy].armor1.item[l]);
							l++;
						}
					}
					
					videoprinternorm(l+1, 0, "Press d to move to next category\n");
					
					l++;

					videoprinternorm(l+1, 0, "Press k to move to next enemy stat\n");

					l++;
					
					videoprinternorm(l+1, 0, "Press anything else to exit this menu\n");
					
					l = 0;
					
#ifdef INITNCURSESNOW
					move(0, 0);
					
					refresh();
#endif
				} 
				while((gotcharacter = (RETURNTYPEVIDEO)inputgetter()) == 'd' || gotcharacter == 'k');
					
				list = 0;
				l = 0;
				theenemy = 0;
						
#ifdef INITNCURSESNOW
				move(myplayer[i].y, myplayer[i].x);
					
				clear();
					
				refresh();
#endif
			}
				
			if (ch == 'M')
			{
#ifdef INITNCURSESNOW
				int gotcharacter;
#endif

				int list = 0;

#ifdef INITNCURSESNOW
				clear();
#endif

				int l = 0;

				videoprinterarg1(l, 0, "Player %d", i + 1);
				l++;

				while (strcmp(myplayer[i].magic1.magicitems[l - 1], "Empty") != 0)
				{
					videoprinterarg2(l, 0, "Magic item %d is %s.\n", l, myplayer[i].magic1.magicitems[l - 1]);
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

#ifdef INITNCURSESNOW
				move(u, 0);

				refresh();
#endif
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

						if (u >(myplayer[i].magic1.magiccount) && list == 0)
						{
							u = myplayer[i].magic1.magiccount;
						}

						if (u > (myplayer[i].weapontype.weaponcount) && list == 1)
						{
							u = myplayer[i].weapontype.weaponcount;
						}

						if (u > (myplayer[i].shieldstype.shieldcount) && list == 2)
						{
							u = myplayer[i].shieldstype.shieldcount;
						}

						if (u > (myplayer[i].armor1.armorcount) && list == 3)
						{
							u = myplayer[i].armor1.armorcount;
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

#ifdef INITNCURSESNOW
						clear();
#endif

						if (list == 0)
						{
							l = 0;

							videoprinterarg1(l, 0, "Player %d", i + 1);
							l++;

							while (strcmp(myplayer[i].magic1.magicitems[l - 1], "Empty") != 0)
							{
								videoprinterarg2(l, 0, "Magic item %d is %s.\n", l, myplayer[i].magic1.magicitems[l - 1]);
								l++;
							}
						}

						if (list == 1)
						{
							l = 0;

							videoprinterarg1(l, 0, "Player %d", i + 1);
							l++;

							while (strcmp(myplayer[i].weapontype.item[l - 1], "Empty") != 0)
							{
								videoprinterarg2(l, 0, "Weapon item %d is %s.\n", l, myplayer[i].weapontype.item[l - 1]);
								l++;
							}
						}

						if (list == 2)
						{
							l = 0;

							videoprinterarg1(l, 0, "Player %d", i + 1);
							l++;

							while (strcmp(myplayer[i].shieldstype.item[l - 1], "Empty") != 0)
							{
								videoprinterarg2(l, 0, "Shield item %d is %s.\n", l, myplayer[i].shieldstype.item[l - 1]);
								l++;
							}
						}

						if (list == 3)
						{
							l = 0;

							videoprinterarg1(l, 0, "Player %d", i + 1);
							l++;

							while (strcmp(myplayer[i].armor1.item[l - 1], "Empty") != 0)
							{
								videoprinterarg2(l, 0, "Armor item %d is %s.\n", l, myplayer[i].armor1.item[l - 1]);
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

#ifdef INITNCURSESNOW
					move(u, 0);

					refresh();
#endif
				}

				if (list == 0)
				{
					myplayer[i].magic1.equiped = myplayer[i].magic1.magicitems[u-1];

					if (u == 1)
					{
						myplayer[i].magic1.rangey = playermagicdistance[myplayer[i].magic1.randommagic];
						myplayer[i].magic1.rangex = playermagicdistance[myplayer[i].magic1.randommagic];
						myplayer[i].magic1.damage = playermagicdamage[myplayer[i].magic1.randommagic];
						myplayer[i].magic1.cost = playermagiccost[myplayer[i].magic1.randommagic];
					}

					if (u == 2)
					{
						myplayer[i].magic1.rangey = playermagicdistance[myplayer[i].magic1.nextrandommagic];
						myplayer[i].magic1.rangex = playermagicdistance[myplayer[i].magic1.nextrandommagic];
						myplayer[i].magic1.damage = playermagicdamage[myplayer[i].magic1.nextrandommagic];
						myplayer[i].magic1.cost = playermagiccost[myplayer[i].magic1.nextrandommagic];
					}

					if (u == 3)
					{
						myplayer[i].magic1.rangey = playermagicdistance[myplayer[i].magic1.nextrandommagic2];
						myplayer[i].magic1.rangex = playermagicdistance[myplayer[i].magic1.nextrandommagic2];
						myplayer[i].magic1.damage = playermagicdamage[myplayer[i].magic1.nextrandommagic2];
						myplayer[i].magic1.cost = playermagiccost[myplayer[i].magic1.nextrandommagic2];
					}

					myplayer[i].magicattack = myplayer[i].magic1.damage;
				}

				if (list == 1)
				{
					if (u == 1)
					{
						myplayer[i].weapontype.equiped = item[myplayer[i].weapontype.randomweapon];
						myplayer[i].weapontype.rangey = rangey[myplayer[i].weapontype.randomweapon];
						myplayer[i].weapontype.rangex = rangex[myplayer[i].weapontype.randomweapon];
						myplayer[i].weapontype.damage = damage[myplayer[i].weapontype.randomweapon];
					}

					if (u == 2)
					{
						myplayer[i].weapontype.equiped = item[myplayer[i].weapontype.nextrandomweapon];
						myplayer[i].weapontype.rangey = rangey[myplayer[i].weapontype.nextrandomweapon];
						myplayer[i].weapontype.rangex = rangex[myplayer[i].weapontype.nextrandomweapon];
						myplayer[i].weapontype.damage = damage[myplayer[i].weapontype.nextrandomweapon];
					}

					if (u == 3)
					{
						myplayer[i].weapontype.equiped = item[myplayer[i].weapontype.nextrandomweapon2];
						myplayer[i].weapontype.rangey = rangey[myplayer[i].weapontype.nextrandomweapon2];
						myplayer[i].weapontype.rangex = rangex[myplayer[i].weapontype.nextrandomweapon2];
						myplayer[i].weapontype.damage = damage[myplayer[i].weapontype.nextrandomweapon2];
					}
				}

				if (list == 2)
				{
					if (u == 1)
					{
						myplayer[i].shieldstype.equiped = itemdamage[myplayer[i].shieldstype.randomshield];
						myplayer[i].shieldstype.damage = shielddamage[myplayer[i].shieldstype.randomshield];
						myplayer[i].shieldsdamage1.item = itemdamage[myplayer[i].shieldstype.randomshield];
					}

					if (u == 2)
					{
						myplayer[i].shieldstype.equiped = itemdamage[myplayer[i].shieldstype.nextrandomshield];
						myplayer[i].shieldstype.damage = shielddamage[myplayer[i].shieldstype.nextrandomshield];
						myplayer[i].shieldsdamage1.item = itemdamage[myplayer[i].shieldstype.nextrandomshield];
					}

					if (u == 3)
					{
						myplayer[i].shieldstype.equiped = itemdamage[myplayer[i].shieldstype.nextrandomshield2];
						myplayer[i].shieldstype.damage = shielddamage[myplayer[i].shieldstype.nextrandomshield2];
						myplayer[i].shieldsdamage1.item = itemdamage[myplayer[i].shieldstype.nextrandomshield2];
					}

					myplayer[i].shield = myplayer[i].shieldstype.equiped;
				}

				if (list == 3)
				{
					if (u == 1)
					{
						myplayer[i].armor1.equiped = playerarmor[myplayer[i].armor1.randomarmor];
						myplayer[i].armor1.protection = playerarmorpts[myplayer[i].armor1.randomarmor];
						myplayer[i].armor1.rangey = playerarmordistancey[myplayer[i].armor1.randomarmor];
						myplayer[i].armor1.rangex = playerarmordistancex[myplayer[i].armor1.randomarmor];
					}

					if (u == 2)
					{
						myplayer[i].armor1.equiped = playerarmor[myplayer[i].armor1.nextrandomarmor];
						myplayer[i].armor1.protection = playerarmorpts[myplayer[i].armor1.nextrandomarmor];
						myplayer[i].armor1.rangey = playerarmordistancey[myplayer[i].armor1.nextrandomarmor];
						myplayer[i].armor1.rangex = playerarmordistancex[myplayer[i].armor1.nextrandomarmor];
					}

					if (u == 3)
					{
						myplayer[i].armor1.equiped = playerarmor[myplayer[i].armor1.nextrandomarmor2];
						myplayer[i].armor1.protection = playerarmorpts[myplayer[i].armor1.nextrandomarmor2];
						myplayer[i].armor1.rangey = playerarmordistancey[myplayer[i].armor1.nextrandomarmor2];
						myplayer[i].armor1.rangex = playerarmordistancex[myplayer[i].armor1.nextrandomarmor2];
					}
				}

				l = 0;
				u = 1;

#ifdef INITNCURSESNOW
				move(myplayer[i].y, myplayer[i].x);

				clear();

				refresh();
#endif
			}

			if(ch == 'm')
			{
				int t = -1;

				int aimagicdamage2 = -1;
				int themagicchoose = -1;
				int aiarmorprotection = -1;
				int thearmorchoose = -1;
				
				for(int j = 0; j < maxenemies; j++)
				{
					myai[j].armor1.equiped = aiarmor[myai[j].armor1.randomarmor];
					myai[j].armor1.rangey = aiarmordistancey[myai[j].armor1.randomarmor];
					myai[j].armor1.rangex = aiarmordistancex[myai[j].armor1.randomarmor];
					myai[j].armor1.protection = aiarmorpts[myai[j].armor1.randomarmor];
	
					if((abs(myplayer[i].y - myai[j].y) <= myai[j].armor1.rangey) && (abs(myplayer[i].x - myai[j].x) <= myai[j].armor1.rangex) && myai[j].armor1.protection > aiarmorprotection)
					{
						aiarmorprotection = aiarmorpts[myai[j].armor1.randomarmor];
						thearmorchoose = myai[j].armor1.randomarmor;
					}

					myai[j].armor1.equiped = aiarmor[myai[j].armor1.nextrandomarmor];
					myai[j].armor1.rangey = aiarmordistancey[myai[j].armor1.nextrandomarmor];
					myai[j].armor1.rangex = aiarmordistancex[myai[j].armor1.nextrandomarmor];
					myai[j].armor1.protection = aiarmorpts[myai[j].armor1.nextrandomarmor];
	
					if((abs(myplayer[i].y - myai[j].y) <= myai[j].armor1.rangey) && (abs(myplayer[i].x - myai[j].x) <= myai[j].armor1.rangex) && myai[j].armor1.protection > aiarmorprotection)
					{
						aiarmorprotection = aiarmorpts[myai[j].armor1.nextrandomarmor];
						thearmorchoose = myai[j].armor1.nextrandomarmor;
					}

					myai[j].armor1.equiped = aiarmor[myai[j].armor1.nextrandomarmor2];
					myai[j].armor1.rangey = aiarmordistancey[myai[j].armor1.nextrandomarmor2];
					myai[j].armor1.rangex = aiarmordistancex[myai[j].armor1.nextrandomarmor2];
					myai[j].armor1.protection = aiarmorpts[myai[j].armor1.nextrandomarmor2];
	
					if((abs(myplayer[i].y - myai[j].y) <= myai[j].armor1.rangey) && (abs(myplayer[i].x - myai[j].x) <= myai[j].armor1.rangex) && myai[j].armor1.protection > aiarmorprotection)
					{
						aiarmorprotection = aiarmorpts[myai[j].armor1.nextrandomarmor2];
						thearmorchoose = myai[j].armor1.nextrandomarmor2;
					}

					myai[j].armor1.equiped = aiarmor[thearmorchoose];
					myai[j].armor1.rangey = aiarmordistancey[thearmorchoose];
					myai[j].armor1.rangex = aiarmordistancex[thearmorchoose];
					myai[j].armor1.protection = aiarmorpts[thearmorchoose];

					if(thearmorchoose == -1)
					{
						myai[j].armor1.equiped = aiarmor[myai[j].armor1.randomarmor];
						myai[j].armor1.rangey = aiarmordistancey[myai[j].armor1.randomarmor];
						myai[j].armor1.rangex = aiarmordistancex[myai[j].armor1.randomarmor];
						myai[j].armor1.protection = aiarmorpts[myai[j].armor1.randomarmor];
					}

					myai[j].magic1.equiped = aimagicitems[myai[j].magic1.randommagic];
					myai[j].magic1.rangey = aimagicdistance[myai[j].magic1.randommagic];
					myai[j].magic1.rangex = aimagicdistance[myai[j].magic1.randommagic];
					myai[j].magic1.damage = aimagicdamage[myai[j].magic1.randommagic];
					myai[j].magic1.cost = aimagiccost[myai[j].magic1.randommagic];

					if((positionydiff = abs(myplayer[i].y - myai[j].y)) <= myai[j].magic1.rangey && (positionxdiff = abs(myplayer[i].x - myai[j].x)) <= myai[j].magic1.rangex && (myai[j].magicpoints - myai[j].magic1.cost) >= 0)
					{
						if(myai[j].magic1.damage > aimagicdamage2)
						{
							aimagicdamage2 = aimagicdamage[myai[j].magic1.randommagic];
							themagicchoose = myai[j].magic1.randommagic;
							t = j;		
						}
					}

					myai[j].magic1.equiped = aimagicitems[myai[j].magic1.nextrandommagic];
					myai[j].magic1.rangey = aimagicdistance[myai[j].magic1.nextrandommagic];
					myai[j].magic1.rangex = aimagicdistance[myai[j].magic1.nextrandommagic];
					myai[j].magic1.damage = aimagicdamage[myai[j].magic1.nextrandommagic];
					myai[j].magic1.cost = aimagiccost[myai[j].magic1.nextrandommagic];

					if((positionydiff = abs(myplayer[i].y - myai[j].y)) <= myai[j].magic1.rangey && (positionxdiff = abs(myplayer[i].x - myai[j].x)) <= myai[j].magic1.rangex && (myai[j].magicpoints - myai[j].magic1.cost) >= 0)
					{
						if(myai[j].magic1.damage > aimagicdamage2)
						{
							aimagicdamage2 = aimagicdamage[myai[j].magic1.nextrandommagic];
							themagicchoose = myai[j].magic1.nextrandommagic;
							t = j;		
						}
					}

					myai[j].magic1.equiped = aimagicitems[myai[j].magic1.nextrandommagic2];
					myai[j].magic1.rangey = aimagicdistance[myai[j].magic1.nextrandommagic2];
					myai[j].magic1.rangex = aimagicdistance[myai[j].magic1.nextrandommagic2];
					myai[j].magic1.damage = aimagicdamage[myai[j].magic1.nextrandommagic2];
					myai[j].magic1.cost = aimagiccost[myai[j].magic1.nextrandommagic2];

					if((positionydiff = abs(myplayer[i].y - myai[j].y)) <= myai[j].magic1.rangey && (positionxdiff = abs(myplayer[i].x - myai[j].x)) <= myai[j].magic1.rangex && (myai[j].magicpoints - myai[j].magic1.cost) >= 0)
					{
						if(myai[j].magic1.damage > aimagicdamage2)
						{
							aimagicdamage2 = aimagicdamage[myai[j].magic1.nextrandommagic2];
							themagicchoose = myai[j].magic1.nextrandommagic2;
							t = j;	
						}
					}

					if( (t == -1) && (positionydiff = abs(myplayer[i].y - myai[j].y)) <= myplayer[i].magic1.rangey && (positionxdiff = abs(myplayer[i].x - myai[j].x)) <= myplayer[i].magic1.rangex)
					{
						t = j;
					}

					if(themagicchoose != -1)
					{
						myai[j].magic1.equiped = aimagicitems[themagicchoose];
						myai[j].magic1.rangey = aimagicdistance[themagicchoose];
						myai[j].magic1.rangex = aimagicdistance[themagicchoose];
						myai[j].magic1.damage = aimagicdamage[themagicchoose];
						myai[j].magic1.cost = aimagiccost[themagicchoose];
					}
					else
					{
						myai[j].magic1.equiped = aimagicitems[myai[j].magic1.randommagic];
						myai[j].magic1.rangey = aimagicdistance[myai[j].magic1.randommagic];
						myai[j].magic1.rangex = aimagicdistance[myai[j].magic1.randommagic];
						myai[j].magic1.damage = aimagicdamage[myai[j].magic1.randommagic];
						myai[j].magic1.cost = aimagiccost[myai[j].magic1.randommagic];
					}

					int aimagicdamage2 = -1;
					int themagicchoose = -1;
					int aiarmorprotection = -1;
					int thearmorchoose = -1;
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

							if((myai[p].magicpoints >= myai[p].magic1.cost) && (positionydiff = abs(myplayer[j].y - myai[p].y)) <= myai[p].magic1.rangey && (positionxdiff = abs(myplayer[j].x - myai[p].x)) <= myai[p].magic1.rangex && ch == 'm' && myai[p].hitpoints > 0 && myplayer[j].hitpoints > 0)
							{
								if(j == i)
								{
									if((abs(myplayer[j].y - myai[p].y) <= myai[p].armor1.rangey) && (abs(myplayer[j].x - myai[p].x) <= myai[p].armor1.rangex))
									{
										myplayer[j].hitpoints = myplayer[j].hitpoints - myai[p].magicattack + myplayer[j].character1.magicresist + myplayer[j].armor1.protection;
									}
									else
									{
										myplayer[j].hitpoints = myplayer[j].hitpoints - myai[p].magicattack + myplayer[j].character1.magicresist;
									}
								}

								if(i == j)
								{
									myai[p].magicpoints = myai[p].magicpoints - myai[p].magic1.cost;
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
								if((myplayer[j].magicpoints >= myplayer[j].magic1.cost) && (positionydiff = abs(myplayer[j].y - myai[p].y)) <= myplayer[j].magic1.rangey  && (positionxdiff = abs(myplayer[j].x - myai[p].x)) <= myplayer[j].magic1.rangex && ch == 'm' && myai[p].hitpoints > 0 && myplayer[j].hitpoints > 0)
								{
									myai[p].hitpoints = myai[p].hitpoints - myplayer[j].magicattack + myai[p].character1.magicresist;
						
									myplayer[j].magicpoints = myplayer[j].magicpoints - myplayer[j].magic1.cost;
					
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

					myai[p].shieldstype.equiped = itemdamageenemies[myai[p].shieldstype.randomshield];
					myai[p].shieldstype.damage = shielddamageenemies[myai[p].shieldstype.randomshield];

					if(myai[p].shieldstype.damage > aishieldweapon)
					{
						thechooseshield = myai[p].shieldstype.randomshield;
						aishieldweapon = shielddamageenemies[myai[p].shieldstype.randomshield];
					}

					myai[p].shieldstype.equiped = itemdamageenemies[myai[p].shieldstype.nextrandomshield];
					myai[p].shieldstype.damage = shielddamageenemies[myai[p].shieldstype.nextrandomshield];

					if(myai[p].shieldstype.damage > aishieldweapon)
					{
						thechooseshield = myai[p].shieldstype.nextrandomshield;
						aishieldweapon = shielddamageenemies[myai[p].shieldstype.nextrandomshield];
					}

					myai[p].shieldstype.equiped = itemdamageenemies[myai[p].shieldstype.nextrandomshield2];
					myai[p].shieldstype.damage = shielddamageenemies[myai[p].shieldstype.nextrandomshield2];

					if(myai[p].shieldstype.damage > aishieldweapon)
					{
						thechooseshield = myai[p].shieldstype.nextrandomshield2;
						aishieldweapon = shielddamageenemies[myai[p].shieldstype.nextrandomshield2];
					}

					myai[p].shieldstype.equiped = itemdamageenemies[thechooseshield];
					myai[p].shieldstype.damage = shielddamageenemies[thechooseshield];

					myai[p].weapontype.equiped = itemenemies[myai[p].weapontype.randomweapon];
					myai[p].weapontype.rangey = rangeyenemies[myai[p].weapontype.randomweapon];
					myai[p].weapontype.rangex = rangexenemies[myai[p].weapontype.randomweapon];
					myai[p].weapontype.damage = damageenemies[myai[p].weapontype.randomweapon];
	
					if( (positionydiff = abs(myplayer[i].y - myai[p].y)) <= myai[p].weapontype.rangey  && (positionxdiff = abs(myplayer[i].x - myai[p].x)) <= myai[p].weapontype.rangex && myai[p].hitpoints > 0 && myplayer[i].hitpoints > 0 && (ch == 'a' || ch == 'd' || ch == 'w' || ch == 's'))
					{
						if(myai[p].weapontype.damage > aiequipedweapon)
						{
							aiequipedweapon = myai[p].weapontype.damage;
							thechoose = myai[p].weapontype.randomweapon;
						}
					}
	
					myai[p].weapontype.equiped = itemenemies[myai[p].weapontype.nextrandomweapon];
					myai[p].weapontype.rangey = rangeyenemies[myai[p].weapontype.nextrandomweapon];
					myai[p].weapontype.rangex = rangexenemies[myai[p].weapontype.nextrandomweapon];
					myai[p].weapontype.damage = damageenemies[myai[p].weapontype.nextrandomweapon];
	
					if( (positionydiff = abs(myplayer[i].y - myai[p].y)) <= myai[p].weapontype.rangey  && (positionxdiff = abs(myplayer[i].x - myai[p].x)) <= myai[p].weapontype.rangex && myai[p].hitpoints > 0 && myplayer[i].hitpoints > 0 && (ch == 'a' || ch == 'd' || ch == 'w' || ch == 's'))
					{
						if(myai[i].weapontype.damage > aiequipedweapon)
						{
							aiequipedweapon = myai[p].weapontype.damage;
							thechoose = myai[p].weapontype.nextrandomweapon;
						}
					}
	
					myai[p].weapontype.equiped = itemenemies[myai[p].weapontype.nextrandomweapon2];
					myai[p].weapontype.rangey = rangeyenemies[myai[p].weapontype.nextrandomweapon2];
					myai[p].weapontype.rangex = rangexenemies[myai[p].weapontype.nextrandomweapon2];
					myai[p].weapontype.damage = damageenemies[myai[p].weapontype.nextrandomweapon2];
	
					if( (positionydiff = abs(myplayer[i].y - myai[p].y)) <= myai[p].weapontype.rangey  && (positionxdiff = abs(myplayer[i].x - myai[p].x)) <= myai[p].weapontype.rangex && myai[p].hitpoints > 0 && myplayer[i].hitpoints > 0 && (ch == 'a' || ch == 'd' || ch == 'w' || ch == 's'))
					{
						if(myai[i].weapontype.damage > aiequipedweapon)
						{
							aiequipedweapon = myai[p].weapontype.damage;
							thechoose = myai[p].weapontype.nextrandomweapon2;
						}
					}
	
					if(thechoose != -1)
					{
						myai[p].weapontype.equiped = itemenemies[thechoose];
						myai[p].weapontype.rangey = rangeyenemies[thechoose];
						myai[p].weapontype.rangex = rangexenemies[thechoose];
						myai[p].weapontype.damage = damageenemies[thechoose];
					}
					else
					{
						myai[p].weapontype.equiped = itemenemies[myai[p].weapontype.randomweapon];
						myai[p].weapontype.rangey = rangeyenemies[myai[p].weapontype.randomweapon];
						myai[p].weapontype.rangex = rangexenemies[myai[p].weapontype.randomweapon];
						myai[p].weapontype.damage = damageenemies[myai[p].weapontype.randomweapon];
					}

					if(j == i)
					{
						if( (positionydiff = abs(myplayer[j].y - myai[p].y)) <= myplayer[j].weapontype.rangey  && (positionxdiff = abs(myplayer[j].x - myai[p].x)) <= myplayer[j].weapontype.rangex && myai[p].hitpoints > 0 && myplayer[j].hitpoints > 0 && (ch == 'a' || ch == 'd' || ch == 'w' || ch == 's'))
						{	
							myai[p].hitpoints = myai[p].hitpoints - myplayer[j].weapontype.damage - myplayer[j].character1.attack + myai[p].shieldstype.damage + myai[p].defensepoints;
					
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
						if( (positionydiff = abs(myplayer[j].y - myai[p].y)) <= myai[p].weapontype.rangey  && (positionxdiff = abs(myplayer[j].x - myai[p].x)) <= myai[p].weapontype.rangex && myai[p].hitpoints > 0 && myplayer[j].hitpoints > 0 && (ch == 'a' || ch == 'd' || ch == 'w' || ch == 's'))
						{	
							myplayer[j].hitpoints = myplayer[j].hitpoints - myai[p].weapontype.damage - myai[p].character1.attack + myplayer[j].shieldstype.damage + myplayer[j].defensepoints;

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

					positiony = (myplayer[i].y / hitpointsy) * hitpointsy;
					positionx = (myplayer[i].x / hitpointsx) * hitpointsx;
					
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

							positiony = (myplayer[i].y / hitpointsy) * hitpointsy;
							positionx = (myplayer[i].x / hitpointsx) * hitpointsx;
							
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
					videoprinterstats(hitpointspos1.y + i - positiony, 0, "Player %d is %s hp:%d mp:%d at:%d ma:%s %d def:%d w:%s sh:%s ar:%s md:%d", myplayer[i].count, myplayer[i].character1.character, myplayer[i].hitpoints, myplayer[i].magicpoints, myplayer[i].weapontype.damage + myplayer[i].character1.attack, myplayer[i].magic1.equiped, myplayer[i].magic1.damage, myplayer[i].defensepoints + myplayer[i].shieldstype.damage, myplayer[i].weapontype.equiped, myplayer[i].shieldstype.equiped, myplayer[i].armor1.equiped, myplayer[i].armor1.protection);
				}
			}

			for(int i = 0; i < maxenemies; i++)
			{
				if((hitpointspos1.ay + i) >= (positiony) && (positiony > (maxenemies)))
				{
					videoprinterstats(hitpointspos1.ay + i - positiony, 0, "AI %d is %s hp:%d mp:%d at:%d ma:%s %d def:%d w:%s sh:%s ar:%s md:%d", myai[i].count, myai[i].character1.character, myai[i].hitpoints, myai[i].magicpoints, myai[i].weapontype.damage + myai[i].character1.attack, myai[i].magic1.equiped, myai[i].magic1.damage, myai[i].defensepoints + myai[i].shieldstype.damage, myai[i].weapontype.equiped, myai[i].shieldstype.equiped, myai[i].armor1.equiped, myai[i].armor1.protection);
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
#ifdef INITNCURSESNOW
			move(myplayer[i].y - positiony, myplayer[i].x - positionx);

			refresh();
#endif
		}

	ended:
#ifdef INITNCURSESNOW
		clear();
#endif
		if (ch == 'q')
		{
#if defined(_MSC_VER)
			if(fileExists("SaveFile.txt"))
#else
			if (access("SaveFile.txt", F_OK) != -1)
#endif
			{
				remove("SaveFile.txt");
			}

			goto endmenow;
		}
	
		if(strcmp(winner, "ai") == 0)
		{
			videoprinternorm(0, 0, "You lose the ai won the game is over.");
			videoprinternorm(1, 0, "Press y to end");

#ifdef INITNCURSESNOW
			refresh();
#endif

#if defined(_MSC_VER)
			if(fileExists("SaveFile.txt"))
#else
			if(access("SaveFile.txt", F_OK ) != -1)
#endif
			{
				remove("SaveFile.txt");
			}

			ch = (RETURNTYPEVIDEO)inputgetter();

			if(ch != 'y')
			{
				roundssofar = 1;

#ifdef INITNCURSESNOW
				clear();

				refresh();
#endif

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

#ifdef INITNCURSESNOW
			refresh();
#endif

#if defined(_MSC_VER)
			if(fileExists("SaveFile.txt"))
#else
			if(access("SaveFile.txt", F_OK ) != -1)
#endif
			{
				remove("SaveFile.txt");
			}

			ch = (RETURNTYPEVIDEO)inputgetter();

			if(ch != 'y')
			{
				roundssofar = 1;

#ifdef INITNCURSESNOW
				clear();

				refresh();
#endif

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
	
#ifdef INITNCURSESNOW
		refresh();
#endif
	
		ch = (RETURNTYPEVIDEO)inputgetter();

		if(ch != 'y')
		{
			roundssofar++;

#ifdef INITNCURSESNOW
			clear();

			refresh();
#endif

			goto beginning;
		}

	endmenow:
#ifdef INITNCURSESNOW
		endwin();
#endif
	
		return 0;
	}
}
