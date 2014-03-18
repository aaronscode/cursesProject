#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include <string.h>
#include <stdlib.h>

typedef struct menuChoice;

void initMenu(int numberOfChoices, int width, int height);
bool initTitle(int columns, int rows, char text);
void cleanupMenu();
void updateMainMenu();

#include "mainMenu.c"
#endif
