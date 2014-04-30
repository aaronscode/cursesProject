#include <stdio.h>
#include <string.h>
#define LIST_FILE_NAME "./maps/maplist.txt"
#define FOLDER_PREFIX "./maps/"
#define MAX_NAME_LENGTH 80

FILE *fp = NULL; // pointer to maplist file

char **mapNames; // string array to hold map names
//  holds digits from mapList to be converted to numMaps later
char mapNumDigitList[3];
char ch_in; // character read from file

void readMapList()
{
	fp = fopen(LIST_FILE_NAME, "r");

	int i = 0; // generic counter
	while((ch_in = getc(fp)) != '\n')
	{
		mapNumDigitList[i] = ch_in;
		i++;
	}
	// convert string to int
	sscanf(mapNumDigitList, "%d", &numMaps);
	mapNames = (char **) malloc(numMaps * sizeof(char*));
	for(i = 0; i < numMaps; i++)
	{
		mapNames[i] = malloc(MAX_NAME_LENGTH * sizeof(char));
	}
	
	for(i = 0; i < numMaps; i++)
	{
		fgets(mapNames[i], 79, fp);
		stripNewline(mapNames[i]);
	}
	free(fp);
	fp = NULL;
}

int getNumMaps()
{
	return numMaps;
}

void loadMaps(Map* mp)
{
	int i, j, k, l;
	for(l = 0; l < numMaps; l++)
	{
		char mapFilePath[80]; 
		memset(mapFilePath, 0, sizeof(char) * 80);
		strcpy(mapFilePath, FOLDER_PREFIX);

		strcpy(mp[l].mapName, mapNames[l]);
		strcat(mapFilePath, mp[l].mapName);

		bool timeForNext = FALSE;
		int temp;
		char chFromFile;
		char digitList[6];
		fp = fopen(mapFilePath, "r");
		getc(fp);
		getc(fp);
		fgets(mp[l].mapDesc, 79, fp);
		stripNewline(mp[l].mapDesc);
		getc(fp);
		getc(fp);

		// parse character data
		for(i = 0; i < MAP_HEIGHT; i++)
		{
			for(j = 0; j < MAP_WIDTH; j++)
			{
				k = 0;
				digitList[0] = '\0';
				digitList[1] = '\0';
				digitList[2] = '\0';
				digitList[3] = '\0';
				digitList[4] = '\0';
				digitList[5] = '\0';
				temp = 0;
				timeForNext = FALSE;
				do
				{
					chFromFile = getc(fp);
					if((chFromFile == ','))
					{
					} else if((chFromFile == ' ') || (chFromFile == '\n'))
					{
				
						timeForNext = TRUE;
						sscanf(digitList, "%d", &temp);
						mp[l].mapTiles[i][j] = (char)temp;
					} else {
						digitList[k] = chFromFile;
						k++;
						}
				}while(!timeForNext);
			}
		}

	getc(fp);
	getc(fp);
	for(i = 0; i < MAP_HEIGHT; i++)
	{
		for(j = 0; j < MAP_WIDTH; j++)
		{
			k = 0;
			digitList[0] = '\0';
			digitList[1] = '\0';
			digitList[2] = '\0';
			digitList[3] = '\0';
			digitList[4] = '\0';
			digitList[5] = '\0';
			temp = 0;
			timeForNext = FALSE;
			do
			{
				chFromFile = getc(fp);
				if((chFromFile == ','))
				{
				} else if((chFromFile == ' ') || (chFromFile == '\n'))
				{
				
					timeForNext = TRUE;
					sscanf(digitList, "%d", &temp);
					mp[l].mapColors[i][j] = temp;
				} else {
					digitList[k] = chFromFile;
					k++;
					}
			}while(!timeForNext);
		}
	}

	// parse property data
	getc(fp);
	getc(fp);
	for(i = 0; i < MAP_HEIGHT; i++)
	{
		for(j = 0; j < MAP_WIDTH; j++)
		{
			k = 0;
			digitList[0] = '\0';
			digitList[1] = '\0';
			digitList[2] = '\0';
			digitList[3] = '\0';
			digitList[4] = '\0';
			digitList[5] = '\0';
			temp = 0;
			timeForNext = FALSE;
			do
			{
				chFromFile = getc(fp);
				if((chFromFile == ','))
				{
				} else if((chFromFile == ' ') || (chFromFile == '\n'))
				{
				
					timeForNext = TRUE;
					sscanf(digitList, "%d", &temp);
					mp[l].mapProperties[i][j] = temp;
				} else {
					digitList[k] = chFromFile;
					k++;
					}
			}while(!timeForNext);
		}
	}

		fclose(fp);
		fp = NULL;
	}

	for(i = 0; i < numMaps; i++)
	{
		free(mapNames[i]);
	}

	free(mapNames);
}

void stripNewline(char *string)
{
	int i = 0;
	while(string[i] != '\0')
	{
		if(string[i] == '\n') string[i] = '\0';
		i++;
	}
}
