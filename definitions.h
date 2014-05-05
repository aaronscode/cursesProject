#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#include "hero.h"

#define MAX_FPS 50
#define MSEC_IN_SEC 1000
#define DELAY (MSEC_IN_SEC / MAX_FPS)
#define TICS_PER_SEC MAX_FPS
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

#define MAP_WIDTH 160
#define MAP_HEIGHT 160

#define SOLID_TILE 1
#define NPC_TILE 2

#ifdef _WIN32		// defs to check OS
#endif
#ifdef __unix__
#define is_unix 1
int colors[] = {0,1,2,3,4,5,6,7};
#else
#define is_unix 0
int colors[] = {0,4,2,6,1,5,3,7};
#endif

typedef struct Map{
	char mapName[80];
	char mapDesc[80];
	char mapTiles[MAP_WIDTH][MAP_HEIGHT];
	int mapColors[MAP_WIDTH][MAP_HEIGHT];
	int mapProperties[MAP_WIDTH][MAP_HEIGHT];
} Map;

Map *maps;

int numMaps;

hero chad;
#endif
