void updateOptions(int key)
{
	switch(key)
	{
		case 'x':
			setState(getPrevState());
			break;
		case 27:
			setState(QUIT);
			break;
		default:
			break;
	}
}

void renderOptions()
{
	mvprintw(0, 0, "Options State");
	mvprintw(1, 0, "(You are experienceing the illsion of free will)");
}
