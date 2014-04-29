#define NUMPAGES 2
int page = 1;
char instructionsText1[] = {"\
Page 1: Introduction\n\
----------------\n\
(Use the up and down arrow keys to scroll between pages of instructions)\n\n\
This is you: U\n\
More specifically, this is your when facing up. When facing down, you look more\n\
like this: D And, as you can probably imagine, left and right look like L & R,\n\
respectively.\n\n\
Your name is Chad, by the way. Huh? What's that you say?\n\n\
\"Chad? Really now? What kind of name for a hero is Chad?\"\n\n\
Well, I can't really argue with you. It is a terrible name. But, that's just\n\
the way it is, so try to deal with it.\n\n\
Anyway, Chad, erm, I mean YOU (remember, you ARE the Chad), work in the local\n\
Amazon warehouse, stacking boxes, taking inventory, etc. That is, you did until\n\
one day, when you hear a noise in the back of the warehouse. You head back to\n\
investigate..."
};
char instructionsText2[] = {"\
Page 2: Controls\n\
----------------\n\n\
Use the arrow keys for navigation, both in the game world and in the menus.\n\
The 'z' key is used to to select menu options and talk to npcs, think of it\n\
like the 'A' button on a Gameboy. Conversely, the 'x' key is used to back out\n\
of menus and selections, like the 'B' button on a gameboy. When in the main\n\
game use the TAB key to open and close the pause menu."
};

void updateInstructions(int key)
{
	switch(key)
	{
		case KEY_UP:
			if(page > 1) page--;
			break;
		case KEY_DOWN:
			if(page < NUMPAGES) page++;
			break;
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

void renderInstructions()
{
	switch(page)
	{
		case 1:
			mvaddstr(0,0, instructionsText1);
			break;
		case 2:
			mvaddstr(0,0, instructionsText2);
			break;

	}
}
