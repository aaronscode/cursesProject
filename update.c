#define TICKS_TO_COOLDOWN 5

int inputCoolCount;

int key = 0;

void update() {

	if( inputCoolCount == 0 )
	{
		key = getKey();
		if(key != ERR){
			//inputCoolCount = TICKS_TO_COOLDOWN;
			switch(getState())
			{
				case MAIN_MENU:
					updateMainMenu(key);
					break;
				case GAME:
					updateGame(key);
					break;
				case INSTRUCTIONS:
					updateInstructions(key);
					break;
				case OPTIONS:
					updateOptions(key);
					break;
				default:
					break;
			}
		}
	} else {
		inputCoolCount--;
	}

	if(key == 27)
	{
		setState(QUIT);
	} 
}

int getKey(){
	int key = getch();
	return key;
}
