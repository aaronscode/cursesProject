int gameState, prevGameState, gameStateData;

// TODO remove these lines
int x = (int) (SCREEN_WIDTH / 2);
int y = (int) (SCREEN_HEIGHT / 2);

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
	setGameState(WALKING, 0);
}

void updateGame(int key)
{
	switch(key)
	{
		case KEY_UP:
			if(y > 0) y--;
			break;
		case KEY_DOWN:
			if(y <  (SCREEN_HEIGHT - 1)) y++;
			break;
		case KEY_LEFT:
			if(x > 0) x--;
			break;
		case KEY_RIGHT:
			if(x < (SCREEN_WIDTH - 1)) x++;
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
	mvprintw(0, 0, "Game State (You are having fun)");
	mvprintw(0,0, "%d", numMaps);
	mvprintw(y, x, "@");
}

void cleanupGame()
{
	free(maps);
}
