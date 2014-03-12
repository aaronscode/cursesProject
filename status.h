#ifndef __STATE_H__ //TODO change this to actual game name
#define __STATE_H__

#define QUIT 0
#define MAIN_MENU 1

int getState();
int getPrevState();
int setState(int newState);
#include "globals.c"
#endif
