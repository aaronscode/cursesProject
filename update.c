#define TICKS_TO_COOLDOWN 0

int inputCoolCount = 0;

int key = 0;

void update() {

	key = getKey();
	if(key != ERR){
		if(inputCoolCount == 0)
		{
			inputCoolCount = TICKS_TO_COOLDOWN;
		} else {
			key = ERR;
		}

		switch(getState())
		{
			case MAIN_MENU:
				updateMainMenu(key);
				break;
			case GAME:
				updateGame(key);
				break;
			case BATTLE:
				updateBattle(key);
				break;
			case INSTRUCTIONS:
				updateInstructions(key);
				break;
			case OPTIONS:
				updateOptions(key);
				break;
			case STATUS:
				updateStatus(key);
				break;
			default:
				break;
		}
	} 

	if(inputCoolCount > 0)
	{
			inputCoolCount--;
	}
}

int getKey(){
	int key = getch();
	return key;
}
