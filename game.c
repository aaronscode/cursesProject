int gameState, prevGameState, gameStateData;

// figure out the center of the screen, 
// player is always drawn in center of screen
int xCenter = (int) (SCREEN_WIDTH / 2) - 1;
int yCenter = (int) (SCREEN_HEIGHT / 2);

// cordinate on the screen where next character will be drawn
int penX = 0;
int penY = 0; 

// holds x and y coordinates of map tile to be drawn to screen
int mapXIndex, mapYIndex;

int mapX; // player's current x position on the map
int mapY; // player's current y position on the map

int facing = DIR_UP; // facing up on 
int mapNumber = 0;

void setGameState(int gs, int gsData)
{
	prevGameState = gameState;
	gameState = gs;
	gameStateData = gsData;
}

void initGame()
{
	// load the game's maps
	printw("Loading Resources . . .\n");
	refresh();
	readMapList();
	numMaps = getNumMaps();
	maps = malloc(numMaps * sizeof(Map));
	loadMaps(maps);
	printw("%d Maps Loaded\n", numMaps);
	int i;
	for(i = 0; i < numMaps; i++)
	{
		printw("%s\n", maps[i].mapName);
	}
	refresh();
	napms(2000);

	//load the savefile
	//TODO actually load the savefile
	//TODO set game state based on savefile
	setMap(0, 78, 90, DIR_UP);
	setGameState(WALKING, 0);
}

void updateGame(int key)
{
	switch(key)
	{
		case KEY_UP:
			if((mapY > 0) && isNotSolid(DIR_UP)) mapY--;
			break;
		case KEY_DOWN:
			if((mapY <  (MAP_HEIGHT - 1)) && isNotSolid(DIR_DOWN)) mapY++;
			break;
		case KEY_LEFT:
			if((mapX > 0) && isNotSolid(DIR_LEFT)) mapX--;
			break;
		case KEY_RIGHT:
			if((mapX < (MAP_WIDTH - 1)) && isNotSolid(DIR_RIGHT)) mapX++;
			break;
		case 27:
			setState(MAIN_MENU);
			break;
		default:
			break;
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
		mapYIndex = penY + mapY - yCenter;
		for(penX = 0; penX < SCREEN_WIDTH; penX++)
		{
			mapXIndex = penX + mapX - xCenter;
			if(((mapXIndex >= 0) && (mapYIndex >= 0)) && ((mapXIndex < MAP_WIDTH) && (mapYIndex < MAP_HEIGHT)))
			{
				if(maps[mapNumber].mapTiles[mapYIndex][mapXIndex] != '\0')
				{
					color_set(maps[mapNumber].mapColors[mapYIndex][mapXIndex], NULL);
					mvaddch(penY, penX, maps[mapNumber].mapTiles[mapYIndex][mapXIndex]);
				}
			}
		}
	}
	color_set(0, NULL);
	mvprintw(24, 0, "x:%d", mapX);
	mvprintw(24, 5, "|y:%d", mapY);
	printw(" %c", maps[mapNumber].mapTiles[mapY][mapX]);
	mvprintw(yCenter, xCenter, "@");
}

void cleanupGame()
{
	free(maps);
}

void setDirection(int newDirection)
{
	facing = newDirection;	
}

void setMap(int newMapNumber, int xEntry, int yEntry, int entryDirection)
{
	setDirection(entryDirection);
	mapNumber = newMapNumber;
	mapX = xEntry;
	mapY = yEntry;
}

bool isNotSolid(int attemptDir)
{
	switch(attemptDir)
	{
		case DIR_UP:
			if((maps[mapNumber].mapProperties[mapY - 1][mapX] == SOLID_TILE) || (maps[mapNumber].mapProperties[mapY - 1][mapX] == NPC_TILE))
			{
				return FALSE;
			} else return TRUE;
			break;
		case DIR_DOWN:
			if((maps[mapNumber].mapProperties[mapY + 1][mapX] == SOLID_TILE) || (maps[mapNumber].mapProperties[mapY + 1][mapX] == NPC_TILE))
			{
				return FALSE;
			} else return TRUE;
			break;
		case DIR_LEFT:
			if((maps[mapNumber].mapProperties[mapY][mapX - 1] == SOLID_TILE) || (maps[mapNumber].mapProperties[mapY][mapX - 1] == NPC_TILE))
			{
				return FALSE;
			} else return TRUE;
			break;
		case DIR_RIGHT:
			if((maps[mapNumber].mapProperties[mapY][mapX + 1] == SOLID_TILE) || (maps[mapNumber].mapProperties[mapY][mapX + 1] == NPC_TILE))
			{
				return FALSE;
			} else return TRUE;
			break;
		default:
			break;
	}
}
