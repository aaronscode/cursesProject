/*
 * Aaron Gross
 * this is a map maker for spankwagon
 */

#include <stdio.h>
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

char map[MAP_HEIGHT][MAP_WIDTH] = {'\0'};
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

char instructions[] = {"\
Yeah, there are gonna Instructions here at some point\n\
"};

WINDOW *w;

int key; // user's input

int editMode = EM_INSERTION;
// 1 means cursor moves left on character inmput, 2 moves down, 3 turn off automatic movement
int moveMode = MM_LEFT; 

int i; // generic counter

int main(int argc, char *argv[])
{
	w = initscr();
	keypad(w, TRUE);
	cbreak();
	noecho();

	map[0][0] = '0';
        map[0][1] = '1';
        map[0][2] = '2';
        map[0][3] = '3';
        map[1][0] = '1';
        map[1][1] = 'd';
        map[1][2] = 'd';
        map[1][2] = 'd';
	map[2][0] = '2';
	
	curs_set(0);
	mvaddstr(0,0, instructions);
	wgetch(w);
	curs_set(1);

	do{
		// RENDERING CODE
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
					mvaddch(screenY, screenX, map[mapYIndex][mapXIndex]);
				}
			}
		}

		// render status bar at top
		mvprintw(0, 0, "EM: %d", editMode);
		mvaddch(0, 5, '|');
		for(i = 0; i < SCREEN_WIDTH; i++)
		{
			mvaddch(1, i, '-');
		}

		move(cursorY, cursorX);
		refresh();

		// UPDATING CODE
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
				// TODO add code to save map
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
				if((key >= 33) || (key <= 126))
				{
					map[mapY][mapX] = key;
					if((mapX < MAP_WIDTH - 1) && (moveMode ==  MM_LEFT))
					{
						mapX++;
					} else if((mapY < MAP_HEIGHT - 1) && (moveMode == MM_DOWN))
					{
						mapY++;
					}
				}
				break;
		}

	}while(key != 27);

	return 0;
}
