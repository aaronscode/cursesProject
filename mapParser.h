#ifndef __MAP_PARSER_H__
#define __MAP_PARSER_H__

#include "definitions.h"
void readMapList();
int getNumMaps();
void loadMaps(Map* mp);
void stripNewline(char *string);

#include "mapParser.c"
#endif
