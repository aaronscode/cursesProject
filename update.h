#ifndef __UPDATE__
#define __UPDATE__

#include <curses.h>
#include "state.h"
#include "mainMenu.h"
#include "game.h"
#include "instructions.h"
#include "options.h"

int inputCoolCount;

void update();

int getKey();

#include "update.c"
#endif
