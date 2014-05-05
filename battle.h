#ifndef __BATTLE_H__
#define __BATTLE_H__

#include <curses.h>
#include <string.h>
#include "definitions.h"
#include "state.h"
#include "enemy.h"

#define BAT_ATTACK 1
#define BAT_DEFEND 2
#define BAT_ITEMS 3
#define BAT_FLEE 4
#define BAT_ENTRY 5
#define BAT_VICTORY 6
#define BAT_LVL_UP 7

void initBattle();
void updateBattle(int key);
void renderBattle();
void chooseBatOption();

#include "battle.c"

#endif
