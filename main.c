/* =============================================================================
 * Aaron Gross
 * cursesProject.c
 * 3/4/14
 * V 0.2
 * =============================================================================
 */

#include <stdio.h>
#include <curses.h>
#include "globals.h"
#include "update.h"

#ifdef _WIN32		// defs to check OS
#endif
#ifdef __linux__
#endif

#define MAX_FPS 50
#define MSEC_IN_SEC 1000
#define DELAY (MSEC_IN_SEC / MAX_FPS)
#define TICS_PER_SEC MAX_FPS
void loadResources();
void render();
void pause();

bool notReadyToQuit();
int getKey();

int tick = 0;

int main(int argc, char *argv[])
{
	WINDOW *w = initscr(); // init a curses window

	/*
	 * These two line make it so that getch() doesn't need to wait 
	 * for a character to be entered for getch() to return.
	 * This allows the game to update and render even when there is no input
	 * Also put as: call getch() without blocking
	 */
	cbreak(); // put terminal in c break mode
	nodelay(w, TRUE); // don't wait for enter to read char

	noecho(); // turn off key echoing
	keypad(w, TRUE); // allow getch() to detect non-character key presses

	loadResources();

	while(notReadyToQuit())
	{
		update();
		render();
		pause();

		tick++;
		if(tick == TICS_PER_SEC)
		{
			tick = 0;
		}
	}

	//perform cleanup
	delwin(w);
    	endwin();
   	refresh();

	return 0;
}

void loadResources(){
	printw("Loading Resources . . .");
}

void render() 
{
	if(tick == 0)
	{
 		printw("Hello, World!\n");
	}

	refresh(); // call curses's refresh funct to update screen
}

void pause() 
{
	napms(DELAY); // from curses.h, sleeps for n milliseconds
}

int getKey(){
	int key = getch();
	return key;
}

bool notReadyToQuit()
{
	if(state)
	{
		return TRUE;
	} else 
	{
		return FALSE;
	}
}
