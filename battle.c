int batOptIndex = 1; // which of the four battle options is selected
bool inBattle;
int battleDialogue; 
enemy currEnemy;

void initBattle()
{
	inBattle = TRUE;
	battleDialogue = BAT_ENTRY; 
	// TODO init Enemy using file
	currEnemy.attack = 6;
	currEnemy.defense= 6;
	currEnemy.maxhp = currEnemy.hp = 6;
	currEnemy.speed = 6;
	currEnemy.experience = 10;
	currEnemy.money = 2;
	strcpy(currEnemy.name, "Angry Customer");
}

void updateBattle(int key)
{
	if(inBattle && !battleDialogue)
	{
		switch(key)
		{
			case KEY_UP:
				if(batOptIndex > BAT_ATTACK) batOptIndex--;
				break;
			case KEY_DOWN:
				if(batOptIndex < BAT_FLEE) batOptIndex++;
				break;
			case KEY_LEFT:
				if(batOptIndex > BAT_DEFEND) batOptIndex -=2;
				break;
			case KEY_RIGHT:
				if(batOptIndex < BAT_ITEMS) batOptIndex +=2;
				break;
			case 'z':
				chooseBatOption();
				break;
			case 'x':
				setState(GAME);
				break;
			default:
				break;
		}
	}
	else if(inBattle && battleDialogue)
	{
		switch(key)
		{
			case 'z':
			case 'x':
				if(battleDialogue == BAT_VICTORY)
				{
					chad.experience += currEnemy.experience;
					chad.money += currEnemy.money;
					if(chad.level < calcLevel(chad.experience))
					{
						chad.level = calcLevel(chad.experience);
						chad.maxhp = chad.hp = calcHP(chad.level);
						battleDialogue = BAT_LVL_UP;
					}
					else
					{
						setState(getPrevState());
						battleDialogue = 0;
					}
				} 
				else if(battleDialogue == BAT_LVL_UP)
				{
					setState(getPrevState());
					battleDialogue = 0;
				} 
				else battleDialogue = 0;
				break;
			default: 
				break;
		}
	}
	else
	{
		setState(getPrevState());
	}
}

void renderBattle()
{
	// render the battle choices box
	mvprintw(18, 59, "O-------------------O");
	int i;
	for(i = 1; i < 6; i++)
	{
		mvprintw(18 + i, 59, "|");
		mvprintw(18 + i, 79, "|");
	}
	mvprintw(24, 59, "O-------------------O");
	// if the map's not equal to 0, make it attack, not appease
	if(chad.location.mapNum) mvprintw(20, 62, "Attack");
	else mvprintw(20, 62, "Appease");
	mvprintw(22, 62, "Defend");
	mvprintw(20, 71, "Items");
	mvprintw(22, 71, "Flee");
	switch(batOptIndex)
	{
		case BAT_ATTACK: 
			mvaddch(20, 61, '>');
			break;
		case BAT_DEFEND: 
			mvaddch(22, 61, '>');
			break;
		case BAT_ITEMS: 
			mvaddch(20, 70, '>');
			break;
		case BAT_FLEE: 
			mvaddch(22, 70, '>');
			break;
	}
	
	// render chad box
	mvprintw(12, 0, "O------------------O");
	for(i = 1; i < 12; i++)
	{
		mvprintw(12 + i, 0, "|");
		mvprintw(12 + i, 19, "|");
	}
	mvprintw(18, 1, "[insert Chad here]");
	mvprintw(24, 0, "O------------------O");

	// render chad HP
	mvprintw(15, 66, "O------------O");
	for(i = 1; i < 3; i++)
	{
		mvprintw(15 + i, 66, "|");
		mvprintw(15 + i, 79, "|");
	}
	mvprintw(16, 67, "HP:%d/%d", chad.hp, chad.maxhp);
	mvaddch(17, 67, '(');
	for(i = 0; i < (chad.hp * 10 / chad.maxhp); i++)
	{
		addch('=');
	}
	mvaddch(17, 78, ')');

	// render enemy hp
	mvprintw(0, 0, "O------------O");
	for(i = 1; i < 3; i++)
	{
		mvprintw(0 + i, 0, "|");
		mvprintw(0 + i, 13, "|");
	}
	mvprintw(1, 1, "HP:%d/%d", currEnemy.hp, currEnemy.maxhp);
	mvaddch(2, 1, '(');
	for(i = 0; i < (currEnemy.hp * 10 / currEnemy.maxhp); i++)
	{
		addch('=');
	}
	mvaddch(2, 12, ')');
	mvprintw(3, 0, "O------------O");

	// render battle dialogue box
	mvprintw(21, 20, "---------------------------------------");
	switch(battleDialogue)
	{
		case BAT_ATTACK:
			if(chad.location.mapNum) mvprintw(22, 21, "Chad attacked!");
			else mvprintw(22, 21, "Chad appeased!");
			break;
		case BAT_DEFEND:

			break;
		case BAT_ITEMS:
			
			break;
		case BAT_FLEE:
			
			break;
		case BAT_ENTRY:
			mvprintw(22, 21, "A wild %s appeared", currEnemy.name);
			break;
		case BAT_VICTORY:
			mvprintw(22, 21, "You defeated %s!", currEnemy.name);
			mvprintw(23, 21, "Got $%d for winning!", currEnemy.money);
			break;
		case BAT_LVL_UP:
			mvprintw(22, 21, "Congrats, you leveled up!");
			mvprintw(23, 21, "Now lvl %d", chad.level);
			break;
	}
	mvprintw(24, 20, "---------------------------------------");
}

void chooseBatOption()
{
	switch(batOptIndex)
	{
		case BAT_ATTACK:
			//TODO make this based off of attack, defense, weapons, and shit
			if(chad.speed >= currEnemy.speed)
			{
				currEnemy.hp -=2;
				battleDialogue = BAT_ATTACK;
				if(currEnemy.hp <= 0)
				{
					currEnemy.hp = 0;
					battleDialogue = BAT_VICTORY;
				} else
				{
					chad.hp -=2;
				}
			}
			else
			{
				chad.hp -=2;
				currEnemy.hp -=2;
			}
			break;
		case BAT_DEFEND:

			break;
		case BAT_ITEMS:

			break;
		case BAT_FLEE:

			break;
	}
}
