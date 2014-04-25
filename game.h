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

#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_LEFT 2
#define DIR_RIGHT 3

void setGameState(int gs, int gsData);

void initGame();
void updateGame(int key);
void renderGame();
void cleanupGame();

void setDirection(int newDirection);
void setMap(int newNapNumber, int xEntry, int yEntry, int entryDirection);

// checks if tile in direction player is trying to move is solid
bool isNotSolid(int attemptDir);

#include "game.c"

#endif
