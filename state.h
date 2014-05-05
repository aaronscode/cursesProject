#ifndef __STATE_H__ //TODO change this to actual game name
#define __STATE_H__

#define QUIT 0
#define MAIN_MENU 1
#define GAME 2
#define INSTRUCTIONS 3
#define OPTIONS 4
#define BATTLE 5
#define SHOP 6
#define INVENTORY 7
#define STATUS 8

int getState();
int getPrevState();
int setState(int newState);
#include "state.c"
#endif
