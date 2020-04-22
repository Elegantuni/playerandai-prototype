#include <iostream>
#include <cstdio>
#include <cstring>
#include <regex>
using namespace std;

#include "player.h"
#include "aicharacter.h"

void readfiletest(FILE *fp1);
void processeditorconfigint(FILE *fp1, const char* datatype, int* thedata, std::string searchfor);

struct worldsize
{
	int width;
	int height;
};

int main(int argc, char *argv[])
{
	FILE *fp1;
	struct worldsize theworldsize;
	const char *thetype = "int";
		
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

	processeditorconfigint(fp1, thetype, &theworldsize.width, "world_size_width");

	printf("%d\n", theworldsize.width);
	
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

void processeditorconfigint(FILE *fp1, const char* datatype, int *thedata, std::string searchfor)
{
	const int arbsize = 100;
		
	char *buffer1 = (char*)malloc(sizeof(char) * arbsize);

	size_t arbsizetemp = arbsize;
	std::string result;
	std::string result2 = searchfor + "=(.*)";
	std::string result3 = searchfor + "=";

	size_t numsize;
	
	while((numsize = getline(&buffer1, &arbsizetemp, fp1)) != -1)
	{	
		try {
			std::regex re(result2);
			std::cmatch match;

			if(std::regex_search(buffer1, match, re) && match.size() > 1)
			{
				result = match.str();
				
				char temp[match.length()];
				
				int i = 0;
				int j = 0;
				
				while(i < match.length())
				{
					if(buffer1[i] == result3[i])
					{
						i++;
					}
					else
					{
						temp[j] = buffer1[i];

						i++;
						j++;
					}
				}

				*thedata = (int)strtol(temp, NULL, 10);

				return;
			}
			else
			{
				result = std::string("");
			}
				
		} catch (std::regex_error& e) {
		}
	}
}
