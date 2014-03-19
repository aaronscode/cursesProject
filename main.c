/* =============================================================================
 * Aaron Gross
 * cursesProject
 * renamed SpankWagon, my friend's idea.
 *
 * Credits: 
 * Programming - Aaron Gross
 * Story/Comic relief - Jason Pepper, Jack Hafer
 * 3/4/14
 * V 0.2
 * =============================================================================
 */

#include <stdio.h>
#include <curses.h>
#include "state.h"
#include "update.h"
#include "mainMenu.h"

#ifdef _WIN32		// defs to check OS
#endif
#ifdef __linux__
#endif

#define MAX_FPS 50
#define MSEC_IN_SEC 1000
#define DELAY (MSEC_IN_SEC / MAX_FPS)
#define TICS_PER_SEC MAX_FPS
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

void initialize();
void loadResources();
void render();
void pause();
void cleanup();

bool notReadyToQuit();

int getKey();

int tick = 0;

char titleBanner[] = {"\
SSSSS PPPPP   A   W     W   A   N   N K  K W     W   A    GGG   OOO  N   N\
S     P   P  A A  W  W  W  A A  NN  N K K  W  W  W  A A  G     O   O NN  N\
SSSSS PPPPP A   A W W W W A   A N N N KK   W W W W A   A G  G  O   O N N N\
    S P     AAAAA W W W W AAAAA N N N K K  W W W W AAAAA G   G O   O N N N\
SSSSS P     A   A WW   WW A   A N  NN K  K WW   WW A   A GGGG   OOO  N  NN"};

WINDOW *w;

int main(int argc, char *argv[])
{
	w = initscr(); // init a curses window

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

	initialize();

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

	cleanup();

	return 0;
}

void initialize()
{
	curs_set(0);
	loadResources();
	initTitle(74, 5, titleBanner);
	initMenu(4, SCREEN_WIDTH, SCREEN_HEIGHT);
	setState(MAIN_MENU);
}

void loadResources()
{
	printw("Loading Resources . . .\n");
	refresh();
	// TODO load resources when the actually exist.
	napms(500);
}

void render() 
{
	clear();
	/*
	if(tick == 0)
	{
 		printw("Hello, World!\n");
	}

	*/
	renderMainMenu();
	refresh(); // call curses's refresh funct to update screen
}

void pause() 
{
	napms(DELAY); // from curses.h, sleeps for n milliseconds
}

void cleanup()
{
	cleanupMenu();
	delwin(w);
    	endwin();
   	refresh();
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

int getKey(){
	int key = getch();
	return key;
}
