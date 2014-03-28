#define NUMPAGES 2
int page = 1;
char instructionsText1[] = {"\
Page 1: Controls\n\
----------------\n\n\
The escape key will instantly exit out of the program, without saving any\n\
progress.\n\n\
Use the arrow keys for navigation. For example, pressing the down arrow would\n\
currently scroll to the next page of instructions. The arrow keys can also be\n\
used to select menu options and move your character.\n\n\
The z key is used to interact with objects and make selections. Think of it\n\
as the A button on a Gameboy. The (ENTER) key does the same thing as z.\n\n\
The x key is used to back out, or cancel a section. For example, pressing\n\
x would allow you to return to the main menu from this screen. Think of it as\n\
the B button.\n\n\
And finally, in the actual game, (TAB) will open up the menu."
};
char instructionsText2[] = {"\
Page 2:\n\
This is the second page. Lorem ipsum sum or something."
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
