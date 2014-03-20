#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include "definitions.h"
#include "state.h"

//typedef struct menuChoice;

void initMenu(int numberOfChoices, int width, int height);

// returns true if successful, false if rows or colums is too big
bool initTitle(int columns, int rows, char *text);
int initMenuChoice(int id, char choiceText[]);
void updateMainMenu(int key);
void renderMainMenu();
void cleanupMenu();

#include "mainMenu.c"
#endif
