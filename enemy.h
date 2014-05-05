#ifndef __ENEMY_H__
#define __ENEMY_H__

typedef struct enemy
{
	int attack, defense, maxhp, speed;
	int hp;
	int experience;
	int money;
	char name[15];
} enemy;

#endif
