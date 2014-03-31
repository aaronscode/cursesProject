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
#include "definitions.h"
#include "state.h"
#include "update.h"
#include "mainMenu.h"

#ifdef _WIN32		// defs to check OS
#endif
#ifdef __unix__
#define is_unix 1
#else
#define is_unix 0
#endif

void initialize();
void loadResources();
void render();
void pause();
void cleanup();

bool notReadyToQuit();

int getKey();

int tick = 0;

char titleBanner[] = {"\
SSSSS PPPPP   A   N   N K  K W     W   A    GGG   OOO  N   N\
S     P   P  A A  NN  N K K  W  W  W  A A  G     O   O NN  N\
SSSSS PPPPP A   A N N N KK   W W W W A   A G  G  O   O N N N\
    S P     AAAAA N N N K K  W W W W AAAAA G   G O   O N N N\
SSSSS P     A   A N  NN K  K WW   WW A   A GGGG   OOO  N  NN"};

WINDOW *w;

int main(int argc, char *argv[])
{
	initialize();

	// main game loop
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


	// set the correct size for linux terminals
	if(is_unix)
	{
		resizeterm(25, 80);
	}

	curs_set(0); // set it so that there's no cursor

	loadResources();
	initMenu(4);
	initTitle(60, 5, titleBanner);
	initMenuChoice(GAME, "Play Game");
	initMenuChoice(INSTRUCTIONS, "Instructions");
	initMenuChoice(OPTIONS, "Options");
	initMenuChoice(QUIT, "Quit");
	setState(MAIN_MENU);
}

void loadResources()
{
	printw("Loading Resources . . .\n");
	refresh();
	// TODO load resources when they actually exist.
	napms(500);
}

void render() 
{
	clear();
	switch(getState())
	{
		case MAIN_MENU:
			renderMainMenu();
			break;
		case GAME:
			renderGame();
			break;
		case INSTRUCTIONS:
			renderInstructions();
			break;
		case OPTIONS:
			renderOptions();
			break;
		default:
			break;
	}
	refresh(); // call curses's refresh funct to update screen
}

void pause() 
{
	napms(DELAY); // from curses.h, sleeps for n milliseconds
}

void cleanup()
{
	curs_set(1); // set cursor back to being visible
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
