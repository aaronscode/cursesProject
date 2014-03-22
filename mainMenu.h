#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include "definitions.h"
#include "state.h"

// call first to allocate mem for memory choices
void initMenu(int numberOfChoices);

// initiate the banner, coulums is width of banner, rows is number 
// of rows, *text is a character array holding the banner
// returns true if successful, false if rows or colums is too big
// assert that colums is no greater than width of screen
// rows no greater than height of screen
bool initTitle(int columns, int rows, char *text);

// id is the state id associated with the choice, choicetext is the actual
// text of the choice
// returns -1 if you try to initiate more than numberOfChoices
int initMenuChoice(int id, char choiceText[]);

// called by update(), passes key pressed from keyboard (if any)
void updateMainMenu(int key);

// called by render()
void renderMainMenu();

// call before quitting, frees up allocated memory
void cleanupMenu();

#include "mainMenu.c"
#endif
