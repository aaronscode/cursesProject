/*
 * Aaron Gross
 * this is a map maker for spankwagon
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

#define MAP_WIDTH 160
#define MAP_HEIGHT 160

#define EM_INSERTION 1
#define EM_COLOR 2
#define EM_PROPERTIES 3
#define MM_LEFT 1
#define MM_DOWN 2
#define MM_NONE 3

#ifdef __unix__
#define is_unix 1
int colors[] = {0,1,2,3,4,5,6,7};
#else
#define is_unix 0
int colors[] = {0,4,2,6,1,5,3,7};
#endif

void startup(int argc, char *argv[]);
void loadMap(char *mapName);
void instructions();
void render();
void update();
void saveMap();

bool mapExists(char *fname);

char mapName[40];
char mapDesc[80] = {'\0'};
char map[MAP_HEIGHT][MAP_WIDTH] = {'\0'};
int colorMap[MAP_HEIGHT][MAP_WIDTH] = {0};
int propertyMap[MAP_HEIGHT][MAP_WIDTH] = {0};
//cursor's position relative to the screen's x-orign, should be centered
int cursorX = (int) SCREEN_WIDTH / 2 - 1;
//cursor's position relative to the screen's y-orign, should be centered
int cursorY = (int) SCREEN_HEIGHT / 2;

int mapX = 0; // cursor's position relative to map's x-origin
int mapY = 0; // cursor's position relative to map's y-origin

// hold cords relative to screen of character currently being printed
int screenX = 0;
int screenY = 0;

// hold the x and y indicies of the character that needs to be printed from map[][]
int mapXIndex, mapYIndex;

FILE *fp = NULL;

WINDOW *w;

int key; // user's input

int editMode = EM_INSERTION;
// 1 means cursor moves left on character inmput, 2 moves down, 3 turn off automatic movement
int moveMode = MM_LEFT; 
int currColorPair = 0;

int i, j, k; // generic counters

int main(int argc, char *argv[])
{

	startup(argc, argv);
	instructions();	

	do{
		// RENDERING CODE
		render();
		// UPDATING CODE
		update();
	}while(key != 27);
	
	delwin(w);
    	endwin();
   	refresh();
	return 0;
}

void startup(int argc, char *argv[])
{
	w = initscr();
	start_color();
	keypad(w, TRUE);
	cbreak();
	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 8; j++)
		{
			if(k)
			{
				init_pair(k, colors[i], colors[j]);
			}
			k++;
		}
	}
	if(argc < 2)
	{
		printw("Map file name not imput, defauling to \"MapUnamed.txt\"\n");
		printw("Please enter a short (less than one line) description of the map:\n");
		getstr(mapDesc);
		printw("Press any key to continue");
		strcpy(mapName, "MapUnamed.txt");
	} else {
		strcpy(mapName, argv[1]);
		printw("Attempting to open file: \"%s\"\n", mapName);	
		if(mapExists(mapName))
		{
			printw("Map file found. Loading...\n");
			loadMap(mapName);
			printw("Map loaded, press any key to continue");
		} else {
			printw("Map file not found. A file named \"%s\" will be created when you save.\n", mapName);
			printw("Please enter a short (less than one line) description of the map:\n");
			getstr(mapDesc);
			printw("Press any key to continue");
		}
	}
	noecho();
	wgetch(w);

}

void loadMap(char *mapName)
{
	bool timeForNext = FALSE;
	int temp;
	char chFromFile;
	char digitList[6];
	fp = fopen(mapName, "r");
	addch(getc(fp));
	addch(getc(fp));
	fgets(mapDesc, 79, fp);
	// strip \n from mapDescription
	for(i = 0; i < (sizeof(mapDesc)/sizeof(char)); i++)
	{
		if(mapDesc[i] == '\n')
		{
			mapDesc[i] = '\0';
		}
	}
	addch(getc(fp));
	addch(getc(fp));

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
					map[i][j] = (char)temp;
				} else {
					digitList[k] = chFromFile;
					k++;
					}
			}while(!timeForNext);
		}
	}

	// parse color data
	addch(getc(fp));
	addch(getc(fp));
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
					colorMap[i][j] = temp;
				} else {
					digitList[k] = chFromFile;
					k++;
					}
			}while(!timeForNext);
		}
	}

	// parse property date
	addch(getc(fp));
	addch(getc(fp));
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
					propertyMap[i][j] = temp;
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

void instructions()
{

char instructions[] = {"\
Yeah, there are gonna be better instructions here at some point\n\n\
Anyway, for now: There's a 160 by 160 character array for you to play with.\n\
Pressing most most of the keys on the keyboard will enter that character\n\
in the currently selected cell. You can use the arrow keys to move around.\n\
In the future, there will be different editing modes. One for inserting\n\
characters, one for adding properties (such as colllidability) to tiles,\n\
even changing colors of cells. Right now that's not implemented, but you can\n\
still change the number associated with that by pressing F2. That's what EM: \n\
at the top means. The mode that's actually implemented, movement mode, is also\n\
displayed at the top, next to the MM: . This mode controls how your cursor\n\
moves after you enter a character. In MM 1, your cursor moves to the left\n\
on character input. MM 2 moves your cursor down automatically on input,\n\
and MM 3, the cursor does not move automatically. You can change this using\n\
the F3 key. Also, you can't save or anything right now.\n\n\
Press any key to continue.\
"};

	curs_set(0);
	mvaddstr(0,0, instructions);
	wgetch(w);
	curs_set(1);
}

void render()
{
	clear();

	// nested for loops to render map
	for(screenY = 0; screenY < SCREEN_HEIGHT; screenY++)
	{
		mapYIndex = screenY + mapY - cursorY;
		for(screenX = 0; screenX < SCREEN_WIDTH; screenX++)
		{
			mapXIndex = screenX + mapX - cursorX;
			if(((mapXIndex >= 0) && (mapYIndex >= 0)) && ((mapXIndex < MAP_WIDTH) && (mapYIndex < MAP_HEIGHT)))
			{
				if(map[mapYIndex][mapXIndex] != '\0')
				{
					color_set(colorMap[mapYIndex][mapXIndex], NULL);
					if((EM_INSERTION == editMode) || (EM_COLOR == editMode))
					{
						mvaddch(screenY, screenX, map[mapYIndex][mapXIndex]);
					} else if(EM_PROPERTIES == editMode)
					{
						mvprintw(screenY, screenX,"%d", propertyMap[mapYIndex][mapXIndex]);
					}
				}
			}
		}
	}
	color_set(0, NULL);

	// render status bar at top
	for(i = 0; i < SCREEN_WIDTH; i++)
	{
		mvaddch(0, i, ' ');
	}

	mvprintw(0, 0, "EM: %d", editMode);
	addch('|');
	printw("MM: %d", moveMode);
	addch('|');
	printw("CP: %d", currColorPair);
	color_set(currColorPair, NULL);
	mvaddch(0, 19, '@');
	color_set(0, NULL);
	addch('|');
	for(i = 0; i < 60; i++)
	{
		if(mapDesc[i] != '\0')
		{
			addch(mapDesc[i]);
		}
	}
	
	for(i = 0; i < SCREEN_WIDTH; i++)
	{
		mvaddch(1, i, '-');
	}
	
	// render coords at bottom
	mvprintw(23, 0, "------------");
	mvprintw(24, 0, "            ");
	mvprintw(24, 0, "x:%d", mapX);
	mvprintw(24, 5, "|y:%d", mapY);
	mvprintw(24, 11, "|");

	move(cursorY, cursorX);
	refresh();
}

void update()
{

	key = wgetch(w);
	switch(key)
	{
		case KEY_UP:
			if(mapY > 0) mapY--;
			break;
		case KEY_DOWN:
			if(mapY < MAP_HEIGHT - 1) mapY++;
			break;
		case KEY_LEFT:
			if(mapX > 0) mapX--;
			break;
		case KEY_RIGHT:
			if(mapX < MAP_WIDTH - 1) mapX++;
			break;
		case KEY_F(1):
			saveMap();
			break;
		case KEY_F(2):
			if(editMode < EM_PROPERTIES) editMode++;
			else editMode = EM_INSERTION;
			break;
		case KEY_F(3):
			if(moveMode < MM_NONE) moveMode++;
			else moveMode = MM_LEFT;
			break;
		default:
			switch(editMode)
			{
				case EM_INSERTION:
					// take care of backspace
					if(key == 8)
					{
						if((moveMode == MM_LEFT) && (mapX > 0)) mapX--; // move back
						else if((moveMode == MM_DOWN) && (mapY > 0)) mapY--; // move up
						map[mapY][mapX] = 0;
					}
					// if key within printable ascii range, set cell to that value
					if((key >= 32) && (key <= 126)) 
					{
						map[mapY][mapX] = key;
						colorMap[mapY][mapX] = currColorPair;
						if((mapX < MAP_WIDTH - 1) && (moveMode ==  MM_LEFT))
						{
							mapX++;
						} else if((mapY < MAP_HEIGHT - 1) && (moveMode == MM_DOWN))
						{
							mapY++;
						}
			
					}
					break;
				case EM_COLOR:
					switch(key)
					{
						case 'z':
							if(currColorPair > 0) currColorPair--;
							break;
						case 'c':
							if(currColorPair < 63) currColorPair++;
							break;
						case 'a':
							if((currColorPair-8) > 0) currColorPair -= 8;
							else currColorPair = 0;
							break;
						case 'd':
							if((currColorPair+8) < 63) currColorPair += 8;
							else currColorPair = 63;
							break;
						case 'x':
							colorMap[mapY][mapX] = currColorPair;
							if((mapX < MAP_WIDTH - 1) && (moveMode ==  MM_LEFT))
							{
								mapX++;
							} else if((mapY < MAP_HEIGHT - 1) && (moveMode == MM_DOWN))
							{
								mapY++;
							}
							break;
						default:
							break;
							
					}
					break;
				case EM_PROPERTIES:
					if(('0' <= key) && (key <= '9'))
					{
						propertyMap[mapY][mapX] = key - '0';
					}
					if((mapX < MAP_WIDTH - 1) && (moveMode ==  MM_LEFT))
						{
							mapX++;
						} else if((mapY < MAP_HEIGHT - 1) && (moveMode == MM_DOWN))
						{
							mapY++;
						}
					break;
			}
			break;
	}
}

void saveMap()
{
	fp = fopen(mapName, "w+");
	fprintf(fp, "d\n");
	fprintf(fp, "%s\n", mapDesc);
	
	// save which character is used for tiles
	fprintf(fp, "t\n");
	for(i =0; i < MAP_HEIGHT; i++)
	{
		for(j = 0; j < MAP_WIDTH; j++)
		{
			fprintf(fp, "%d", map[i][j]);
			if(j < MAP_WIDTH - 1)
			{
				fprintf(fp, ", ");
			} else {
				fprintf(fp, "\n");
			}
		}
	}

	// save color data
	fprintf(fp, "c\n");
	for(i =0; i < MAP_HEIGHT; i++)
	{
		for(j = 0; j < MAP_WIDTH; j++)
		{
			fprintf(fp, "%d", colorMap[i][j]);
			if(j < MAP_WIDTH - 1)
			{
				fprintf(fp, ", ");
			} else {
				fprintf(fp, "\n");
			}
		}
	}

	// save tile properties
	fprintf(fp, "p\n");
	for(i =0; i < MAP_HEIGHT; i++)
	{
		for(j = 0; j < MAP_WIDTH; j++)
		{
			fprintf(fp, "%d", propertyMap[i][j]);
			if(j < MAP_WIDTH - 1)
			{
				fprintf(fp, ", ");
			} else {
				fprintf(fp, "\n");
			}
		}
	}
	fclose(fp);
	fp = NULL;
}

bool mapExists(char *fname)
{
	if( access( fname, F_OK ) != -1 ) {
		return 1;
	} else {
		return 0;
	}
}
