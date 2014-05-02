#ifndef __SPANKGAME_H__
#define __SPANKGAME_H__

#include <math.h>
#include <unistd.h> // access() - check for savefile
#include "definitions.h"
#include "state.h"
#include "mapParser.h"
#include "hero.h"

#define MAX_NUM_WARPS 10

#define SAVE_FILE_NAME "save.txt"

#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_LEFT 2
#define DIR_RIGHT 3

void initGame();
void loadWarpTable();
void initChad();
void updateGame(int key);
void renderGame();
void saveGame();
void cleanupGame();

void setDirection(int newDirection);
void setMap(int newNapNumber, int xEntry, int yEntry, int entryDirection);
void warp(int warpID);

// checks if tile in direction player is trying to move is solid
bool isNotSolid(int attemptDir);
int isWarp();
// checks if a number begins with a specific digit
bool startsWith(int digit, int numToCheck);

#include "game.c"

#endif
