void updateStatus(int key)
{
	switch(key)
	{
		case 'x':
			setState(getPrevState());
			break;
		default:
			break;
	}
}

void renderStatus()
{
	mvprintw(0,0, "EXP: %d\n", chad.experience);
	printw("Level: %d\n", chad.level);
	printw("hp/maxhp: %d/%d\n", chad.hp, chad.maxhp);
	printw("money: %d\n", chad.money);
}
