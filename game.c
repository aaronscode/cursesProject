int x = (int) (SCREEN_WIDTH / 2);
int y = (int) (SCREEN_HEIGHT / 2);

void updateGame(int key)
{
	switch(key)
	{
		case KEY_UP:
			if(y > 0) y--;
			break;
		case KEY_DOWN:
			if(y <  (SCREEN_HEIGHT - 1)) y++;
			break;
		case KEY_LEFT:
			if(x > 0) x--;
			break;
		case KEY_RIGHT:
			if(x < (SCREEN_WIDTH - 1)) x++;
			break;
		default:
			break;
	}
}

void renderGame()
{
	mvprintw(0, 0, "Game State (You are having fun)");
	mvprintw(y, x, "@");
}
