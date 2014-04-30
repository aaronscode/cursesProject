// figure out the center of the screen, 
// player is always drawn in center of screen
int xCenter = (int) (SCREEN_WIDTH / 2) - 1;
int yCenter = (int) (SCREEN_HEIGHT / 2);

// cordinate on the screen where next character will be drawn
int penX = 0;
int penY = 0; 

// holds x and y coordinates of map tile to be drawn to screen
int mapXIndex, mapYIndex;

int warpTable[MAX_NUM_WARPS][5];
int warpID;

hero chad;

bool menuUp = FALSE; // if the pause menu is currently displayed or not
int menuPosition = 0; // the position of the currently selected menu option
int numMenuChoices = 5;
char pauseMenuChoices[][5] = {"Inv", "Save", "Opt", "Inst", "Exit"};

/************************ initGame() ***********************
 *
 *
 *
 */
void initGame()
{
	// load the game's maps
	printw("Loading Resources . . .\n");
	refresh();
	readMapList();
	numMaps = getNumMaps();
	maps = malloc(numMaps * sizeof(Map));
	loadMaps(maps);
	/*
	printw("%d Maps Loaded\n", numMaps);
	int i;
	for(i = 0; i < numMaps; i++)
	{
		printw("%s\n", maps[i].mapName);
	}
	refresh();
	napms(2000);
	*/
	loadWarpTable();

	initChad();
}

/****************************** loadWarpTable() *************************
 *
 *
 *
 */
void loadWarpTable()
{
	FILE *warpFile;
	int numWarps;
	char ch_in;
	char digitsList[5];
	warpFile = fopen("warpTable.txt", "r");
	int i = 0;
	while((ch_in = getc(warpFile)) != '\n')
	{
		digitsList[i] = ch_in;
		i++;
	}
	sscanf(digitsList, "%d", &numWarps);

	for(i = 0; i < numWarps; i++)
	{
		int j;
		for(j = 0; j < 5; j++)
		{
			mvprintw(4,0, "I got here");
			refresh();
			int k = 0;
			int temp = 0;
			digitsList[0] = '\0';
			digitsList[1] = '\0';
			digitsList[2] = '\0';
			digitsList[3] = '\0';
			bool timeForNext = FALSE;
			do
			{
				ch_in = getc(warpFile);
				if((ch_in == ' ') || (ch_in == '\n'))
				{
					timeForNext = TRUE;
					sscanf(digitsList, "%d", &temp);
					warpTable[i][j] = temp;
				} else {
					digitsList[k] = ch_in;
					k++;
				}
			}while(!timeForNext);
		}
	}
	fclose(warpFile);
	free(warpFile);
	warpFile = NULL;
	
}

/******************************* initChad() *****************************
 *
 *
 */
void initChad()
{
	//TODO loadsavefile, if it exists, to set all these values
	chad.experience = 0;
	chad.level = pow((double) chad.experience * 5 / 4, 1/3);
	chad.attack = 0;
	chad.defence = 0;
	chad.hp = 0; 
	chad.speed = 0;
	setMap(warpTable[0][1], warpTable[0][2], warpTable[0][3], warpTable[0][4]);
}

/***************************** updateGame() ************************
 *
 *
 */
void updateGame(int key)
{
	if(!menuUp)
	{
		switch(key)
		{
			case KEY_UP:
				setDirection(DIR_UP);
				if((chad.location.y > 0) && isNotSolid(DIR_UP)) chad.location.y--;
				if((warpID = isWarp())) warp(warpID);
				break;
			case KEY_DOWN:
				setDirection(DIR_DOWN);
				if((chad.location.y <  (MAP_HEIGHT - 1)) && isNotSolid(DIR_DOWN)) chad.location.y++;
				if((warpID = isWarp())) warp(warpID);
				break;
			case KEY_LEFT:
				setDirection(DIR_LEFT);
				if((chad.location.x > 0) && isNotSolid(DIR_LEFT)) chad.location.x--;
				if((warpID = isWarp())) warp(warpID);
				break;
			case KEY_RIGHT:
				setDirection(DIR_RIGHT);
				if((chad.location.x < (MAP_WIDTH - 1)) && isNotSolid(DIR_RIGHT)) chad.location.x++;
				if((warpID = isWarp())) warp(warpID);
				break;
			case 0x9: // TAB
				menuUp = TRUE;
				break;
			case 27:
				setState(MAIN_MENU);
				break;
			default:
				break;
		}
	} else {
		switch(key)
		{
			case KEY_UP:
				if(menuPosition > 0) menuPosition--;
				break;
			case KEY_DOWN:
				if(menuPosition < (numMenuChoices - 1)) menuPosition++;
				break;
			case 'z':
				switch(menuPosition)
				{
					case 0: // Inventory
						break;
					case 1: // Save
						break;
					case 2: // Options
						setState(OPTIONS);
						break;
					case 3: // Instructions
						setState(INSTRUCTIONS);
						break;
					case 4: // Exit
						menuUp = FALSE;
						break;
				}
				break;
			case 'x':
				menuUp = FALSE;
				break;
			case 0x9: // TAB
				menuUp = FALSE;
				break;
			default:
				break;
		}
	}
}

void renderGame()
{
	/*
	mvprintw(0, 0, "Game State (You are having fun)");
	mvprintw(0,0, "%d", numMaps);
	mvprintw(y, x, "@");
	*/
	for(penY = 0; penY < SCREEN_HEIGHT; penY++)
	{
		mapYIndex = penY + chad.location.y - yCenter;
		for(penX = 0; penX < SCREEN_WIDTH; penX++)
		{
			mapXIndex = penX + chad.location.x - xCenter;
			if(((mapXIndex >= 0) && (mapYIndex >= 0)) && ((mapXIndex < MAP_WIDTH) && (mapYIndex < MAP_HEIGHT)))
			{
				if(maps[chad.location.mapNum].mapTiles[mapYIndex][mapXIndex] != '\0')
				{
					color_set(maps[chad.location.mapNum].mapColors[mapYIndex][mapXIndex], NULL);
					mvaddch(penY, penX, maps[chad.location.mapNum].mapTiles[mapYIndex][mapXIndex]);
				}
			}
		}
	}
	color_set(0, NULL);
	/*
	mvprintw(24, 0, "x:%d", chad.location.x);
	mvprintw(24, 5, "|y:%d", chad.location.y);
	printw(" %c", maps[chad.location.mapNum].mapTiles[chad.location.y][chad.location.x]);
	*/

	mvaddch(yCenter, xCenter, chad.characterIcon);

	if(menuUp)
	{
		int topRowOfMenu = ((SCREEN_HEIGHT/2) - (numMenuChoices + 1));
		mvprintw(topRowOfMenu, 73, "O-----O");
		int i;
		for(i = 0; i < numMenuChoices; i++)
		{
			mvprintw(topRowOfMenu + i + 1, 73, "|");
			mvprintw(topRowOfMenu + i + 1, 75, "%s", pauseMenuChoices[i]);
			mvprintw(topRowOfMenu + i + 1, 79, "|");
		}
		mvprintw(topRowOfMenu + i + 1, 73, "O-----O");
		mvprintw(topRowOfMenu + menuPosition + 1, 74, ">");
	}
}

void cleanupGame()
{
	free(maps);
	maps = NULL;
}

void setDirection(int newDirection)
{
	chad.facing = newDirection;	
	switch(chad.facing)
	{
		case DIR_UP:
			chad.characterIcon = 'U';
			break;
		case DIR_DOWN:
			chad.characterIcon = 'D';
			break;
		case DIR_LEFT:
			chad.characterIcon = 'L';
			break;
		case DIR_RIGHT:
			chad.characterIcon = 'R';
			break;
	}
}

void setMap(int newMapNumber, int xEntry, int yEntry, int entryDirection)
{
	setDirection(entryDirection);
	chad.location.mapNum = newMapNumber;
	chad.location.x = xEntry;
	chad.location.y = yEntry;
}

void warp(warpID)
{
	setMap(warpTable[warpID - 900][1], warpTable[warpID - 900][2], warpTable[warpID - 900][3], warpTable[warpID - 900][4]);
}

bool isNotSolid(int attemptDir)
{
	switch(attemptDir)
	{
		int tileToCheck;
		case DIR_UP:
			tileToCheck = maps[chad.location.mapNum].mapProperties[chad.location.y - 1][chad.location.x];
			if((tileToCheck == SOLID_TILE) || (tileToCheck == NPC_TILE))
			{
				return FALSE;
			} else return TRUE;
			break;
		case DIR_DOWN:
			tileToCheck = maps[chad.location.mapNum].mapProperties[chad.location.y + 1][chad.location.x];
			if((tileToCheck == SOLID_TILE) || (tileToCheck == NPC_TILE))
			{
				return FALSE;
			} else return TRUE;
			break;
		case DIR_LEFT:
			tileToCheck = maps[chad.location.mapNum].mapProperties[chad.location.y][chad.location.x - 1];
			if((tileToCheck == SOLID_TILE) || (tileToCheck == NPC_TILE))
			{
				return FALSE;
			} else return TRUE;
			break;
		case DIR_RIGHT:
			tileToCheck = maps[chad.location.mapNum].mapProperties[chad.location.y][chad.location.x + 1];
			if((tileToCheck == SOLID_TILE) || (tileToCheck == NPC_TILE))
			{
				return FALSE;
			} else return TRUE;
			break;
		default:
			break;
	}
}

int isWarp()
{
	int propToCheck = maps[chad.location.mapNum].mapProperties[chad.location.y][chad.location.x];
	if(startsWith(9, propToCheck))
	{
		return propToCheck;
	} else return 0;
}

bool startsWith(int digit, int numToCheck)
{
	numToCheck = abs(numToCheck);
	while(numToCheck >= 10)
	{
		numToCheck /= 10;
	}
	if(numToCheck == digit) return TRUE;
	else return FALSE;
}
