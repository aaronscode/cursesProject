#ifndef __SPANKGAME_H__
#define __SPANKGAME_H__

#include "definitions.h"
#include "state.h"
#include "mapParser.h"

#define WALKING 0
#define DIALOGUE 1
//#define BATTLE 2
#define EVENT 3
#define PAUSE_MENU 4
//#define SHOP 5

void setGameState(int gs, int gsData);

void initGame();
void updateGame(int key);
void renderGame();
void cleanupGame();

#include "game.c"

#endif
