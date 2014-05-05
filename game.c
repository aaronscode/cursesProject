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

int randNum;
//bool encounterTile;

FILE *savePtr;

bool menuUp = FALSE; // if the pause menu is currently displayed or not
bool gameJustSaved = FALSE;
int menuPosition = 0; // the position of the currently selected menu option
int numMenuChoices = 6;
char pauseMenuChoices[][5] = {"Inv", "Stat", "Save", "Opt", "Inst", "Exit"};

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
	loadDialogues();
	// seed the RNG
	srand(time(NULL));

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
	warpFile = NULL;
	
}

/******************************* initChad() *****************************
 *
 *
 */
void initChad()
{
	if(access( SAVE_FILE_NAME, F_OK ) != -1) // if savefile exits
	{
		int temp;
		savePtr = fopen(SAVE_FILE_NAME, "r");
		fscanf(savePtr, "%d", &temp); // read experience
		chad.experience = temp;
		chad.level = calcLevel(chad.experience);
		chad.attack = calcAttack(chad.level);
		chad.defense = calcDefense(chad.level);
		chad.maxhp = calcHP(chad.level);
		chad.speed = calcSpeed(chad.level);
		fscanf(savePtr, "%d", &temp); // read hp
		chad.hp = temp;
		fscanf(savePtr, "%d", &temp); // read map number
		chad.location.mapNum = temp;
		fscanf(savePtr, "%d", &temp); // read x position
		chad.location.x = temp;
		fscanf(savePtr, "%d", &temp); // read y position
		chad.location.y = temp;
		fscanf(savePtr, "%d", &temp); // read direction
		setDirection(temp);
		// will load inventory and shit later
		fclose(savePtr);
		savePtr = NULL;
	}
	else
	{ // file does not exist, start with defaults
		chad.experience = 0;
		chad.level = calcLevel(chad.experience);
		chad.attack = calcAttack(chad.level);
		chad.defense = calcDefense(chad.level);
		chad.maxhp = chad.hp = calcHP(chad.level); 
		chad.speed = calcSpeed(chad.level);
		setMap(warpTable[0][1], warpTable[0][2], warpTable[0][3], warpTable[0][4]);
	}
	// move this shit into else later, when you actually load inventory
	// TODO set initial inventory to be later moved under else statement	
}

/***************************** updateGame() ************************
 *
 *
 */
void updateGame(int key)
{
	if((key != ERR) && (gameJustSaved == TRUE))
	{
		gameJustSaved = FALSE;
	}
	if(!menuUp && !dialogueUp)
	{
		switch(key)
		{
			case KEY_UP:
				setDirection(DIR_UP);
				if((chad.location.y > 0) && isNotSolid(DIR_UP)) chad.location.y--;
				if((warpID = isWarp())) warp(warpID);
				if(isRandEncounterTile()) rollTheDice();
				break;
			case KEY_DOWN:
				setDirection(DIR_DOWN);
				if((chad.location.y <  (MAP_HEIGHT - 1)) && isNotSolid(DIR_DOWN)) chad.location.y++;
				if((warpID = isWarp())) warp(warpID);
				if(isRandEncounterTile()) rollTheDice();
				break;
			case KEY_LEFT:
				setDirection(DIR_LEFT);
				if((chad.location.x > 0) && isNotSolid(DIR_LEFT)) chad.location.x--;
				if((warpID = isWarp())) warp(warpID);
				if(isRandEncounterTile()) rollTheDice();
				break;
			case KEY_RIGHT:
				setDirection(DIR_RIGHT);
				if((chad.location.x < (MAP_WIDTH - 1)) && isNotSolid(DIR_RIGHT)) chad.location.x++;
				if((warpID = isWarp())) warp(warpID);
				if(isRandEncounterTile()) rollTheDice();
				break;
			case 'z':
				switch(chad.facing)
				{
					int tileToCheck;
					case DIR_UP: tileToCheck = maps[chad.location.mapNum].mapProperties[chad.location.y - 1][chad.location.x];
						if(startsWith(NPC_TILE, tileToCheck))
						{
							setDialogue(tileToCheck - 200);
						}
						break;
					case DIR_DOWN: tileToCheck = maps[chad.location.mapNum].mapProperties[chad.location.y + 1][chad.location.x];
						if(startsWith(NPC_TILE, tileToCheck))
						{
							setDialogue(tileToCheck - 200);
						}
						break;
					case DIR_LEFT: tileToCheck = maps[chad.location.mapNum].mapProperties[chad.location.y][chad.location.x - 1];
						if(startsWith(NPC_TILE, tileToCheck))
						{
							setDialogue(tileToCheck - 200);
						}
						break;
					case DIR_RIGHT: tileToCheck = maps[chad.location.mapNum].mapProperties[chad.location.y][chad.location.x + 1];
						if(startsWith(NPC_TILE, tileToCheck))
						{
							setDialogue(tileToCheck - 200);
						}
						break;
				}
				break;
			/*
			case KEY_F(1):
				saveGame();
				break;
			*/
			case 0x9: // TAB
				menuUp = TRUE;
				break;
			case 27:
				setState(MAIN_MENU);
				break;
			default:
				break;
		}
	} else if(menuUp){
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
					case 1: // status
						setState(STATUS);
						break;
					case 2: // Save
						saveGame();
						gameJustSaved = TRUE;
						menuUp = FALSE;
						break;
					case 3: // Options
						setState(OPTIONS);
						break;
					case 4: // Instructions
						setState(INSTRUCTIONS);
						break;
					case 5: // Exit
						menuUp = FALSE;
						break;
				}
				break;
			case 27: // Escape
			case 'x':
			case 0x9: // TAB
				menuUp = FALSE;
				break;
			default:
				break;
		}
	} else if(dialogueUp)
	{
		updateDialogue(key);
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
	// debug for random encounter system
	//mvprintw(24, 0, "%d, %d, %d", randNum, encounterTile, isRandEncounterTile());
	mvprintw(24,0, "%d", calcLevel(chad.experience));

	mvaddch(yCenter, xCenter, chad.characterIcon);

	// render menu if necessary
	if(menuUp)
	{
		int topRowOfMenu = ((SCREEN_HEIGHT/2) - (numMenuChoices + 1));
		mvprintw(topRowOfMenu, 73, "O-----O");
		int i;
		for(i = 0; i < numMenuChoices; i++)
		{
			mvprintw(topRowOfMenu + i + 1, 73, "|");
			mvprintw(topRowOfMenu + i + 1, 74, "      ");
			mvprintw(topRowOfMenu + i + 1, 75, "%s", pauseMenuChoices[i]);
			mvprintw(topRowOfMenu + i + 1, 79, "|");
		}
		mvprintw(topRowOfMenu + i + 1, 73, "O-----O");
		mvprintw(topRowOfMenu + menuPosition + 1, 74, ">");
	}else if(dialogueUp)
	{
		renderDialogue();
	}
	else if(gameJustSaved)
	{
		mvprintw(11, 33, "O----------O");
		mvprintw(12, 33, "|Game Saved|");
		mvprintw(13, 33, "O----------O");
	}
}

void saveGame()
{
	savePtr = fopen(SAVE_FILE_NAME, "w+");
	fprintf(savePtr, "%d\n", chad.experience);
	fprintf(savePtr, "%d\n", chad.hp);
	fprintf(savePtr, "%d\n", chad.location.mapNum);
	fprintf(savePtr, "%d\n", chad.location.x);
	fprintf(savePtr, "%d\n", chad.location.y);
	fprintf(savePtr, "%d\n", chad.facing);
	// TODO save inventory
	fclose(savePtr);
	savePtr = NULL;
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

void rollTheDice()
{
	// generate a random number between 1 and 10
	randNum = (int) rand() % 10 + 1;
	if(randNum == 4)// http://xkcd.com/221/
	{
		initBattle();
		setState(BATTLE);
		napms(400); // give the user a sec to realize battle is happening
	}
}

bool isNotSolid(int attemptDir)
{
	switch(attemptDir)
	{
		int tileToCheck;
		case DIR_UP:
			tileToCheck = maps[chad.location.mapNum].mapProperties[chad.location.y - 1][chad.location.x];
			if((tileToCheck == SOLID_TILE) || (startsWith(NPC_TILE, tileToCheck)))
			{
				return FALSE;
			} else return TRUE;
			break;
		case DIR_DOWN:
			tileToCheck = maps[chad.location.mapNum].mapProperties[chad.location.y + 1][chad.location.x];
			if((tileToCheck == SOLID_TILE) || (startsWith(NPC_TILE, tileToCheck)))
			{
				return FALSE;
			} else return TRUE;
			break;
		case DIR_LEFT:
			tileToCheck = maps[chad.location.mapNum].mapProperties[chad.location.y][chad.location.x - 1];
			if((tileToCheck == SOLID_TILE) || (startsWith(NPC_TILE, tileToCheck)))
			{
				return FALSE;
			} else return TRUE;
			break;
		case DIR_RIGHT:
			tileToCheck = maps[chad.location.mapNum].mapProperties[chad.location.y][chad.location.x + 1];
			if((tileToCheck == SOLID_TILE) || (startsWith(NPC_TILE, tileToCheck)))
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

bool isRandEncounterTile()
{
	int propToCheck = maps[chad.location.mapNum].mapProperties[chad.location.y][chad.location.x];
	if(startsWith(3, propToCheck)) return TRUE;
	else return FALSE;
}
