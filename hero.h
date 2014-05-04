#ifndef __HERO_H__
#define __HERO_H__

#include "item.h"

#define MAX_INV_SIZE 40

// define a struct to store the x and y position of the hero
// as well as what map he/she is on
typedef struct position
{
	int mapNum;
	int x, y;
} position;

typedef struct hero
{
	int experience;
	int level;
	int attack, defence, hp, speed;
	int money;
	
	int facing;
	int characterIcon;

	position location;

	item inventory[MAX_INV_SIZE];
	item weapon, armour; // equiped weapon and armour
} hero;

int calcLevel(int experience);
int calcAttack(int level);
int calcDefense(int level);
int calcHP(int level);
int calcSpeed(int level);

#include "hero.c"

#endif
