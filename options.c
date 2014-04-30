bool screenTest = FALSE;

void updateOptions(int key)
{
	switch(key)
	{
		case 'z':
			if(screenTest == FALSE)
			{
				screenTest = TRUE;
			}
			break;
		case 'x':
			if(screenTest)
			{
				screenTest = FALSE;
			} else {
			setState(getPrevState());
			}
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
	if(screenTest == FALSE)
	{
		mvprintw(0, 0, "Options State");
		mvprintw(1, 0, "(You are experienceing the illsion of free will)");
		mvprintw(2, 0, "> Screen Test");
	} else {
		int i;
		mvprintw(0,0, "O------------------------------------------------------------------------------O");
		mvprintw(1, 1, "Those who are not using Windows, please resize the termial until the entire");
		mvprintw(2, 1, "Box is visible on your screen.");
		for(i = 1; i < SCREEN_HEIGHT-1; i++)
		{
			mvprintw(i, 0, "|");
			mvprintw(i, SCREEN_WIDTH - 1, "|");
		}
		mvprintw(24, 0, "O------------------------------------------------------------------------------O");
	}

}
