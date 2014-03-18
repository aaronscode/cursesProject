#ifndef __MAIN_MENU__
#define __MAIN_MENU__

<<<<<<< HEAD
#include <string.h>
#include <stdlib.h>

typedef struct menuChoice;

void initMenu(int numberOfChoices, int width, int height);
bool initTitle(int columns, int rows, char text);
void cleanupMenu();
void updateMainMenu();
=======
typedef struct menuChoice;

void initMenu(int numChoices);
>>>>>>> 594583d7fab2cc5436533d28f08eb1f8e17c087e

#include "mainMenu.c"
#endif
