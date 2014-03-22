#define MAX_CHOICE_CHARS 30 // max number of chars a menu option can have
#define TOP_BANNER_PAD 2
#define BANNER_OPTIONS_PAD 4

// define a structure to encapsulate the data used by a menu choice
typedef struct
{
	int stateID;
	char text[MAX_CHOICE_CHARS];
} menuChoice;

menuChoice *mc;

int numChoices, currentNumChoices = 0;
int titleColumns, titleRows; // number of colums and rows in the title banner
int cursorPos; // current row cursor is on (vertical cursor position)
int topOptPos, botOptPos; // position of the first menu choice, last menu choice

char *titleText; // char pointer to hold text of the tile

void initMenu(int numberOfChoices)
{
	// allocate mem for menu choices
	mc = (menuChoice*) malloc(numberOfChoices * sizeof(menuChoice));
	numChoices = numberOfChoices;
}

bool initTitle(int columns, int rows, char *text)
{
	// make sure entire menu will actually fit
	if((columns > SCREEN_WIDTH)||(rows > (SCREEN_HEIGHT - 1 - numChoices)))
	{
		return FALSE;
	}
	titleColumns = columns;
	titleRows = rows;

	// allocate memory for title banner's text
	titleText = malloc(rows * columns + 1);

	// copy text into title text
	int i;
	for(i = 0; i < rows * columns; i++)
	{
		titleText[i] = text[i];
	}

	cursorPos = TOP_BANNER_PAD + titleRows + BANNER_OPTIONS_PAD + 1;
	topOptPos = cursorPos;
	botOptPos = cursorPos + numChoices - 1;
	return TRUE;
}

int initMenuChoice(int id, char choiceText[])
{
	// make sure it's not going to initialize more options than memory 
	// was allocated for choices
	if(currentNumChoices >= numChoices)
	{
		return -1;
	}

	mc[currentNumChoices].stateID = id;
	strcpy(mc[currentNumChoices].text, choiceText);

	return ++currentNumChoices;
}

void updateMainMenu(int key)
{
	// process keyboard input
	switch(key)
	{
		case KEY_UP:
			if(cursorPos > topOptPos)
			{
				cursorPos--; // move cursor up one
			}
			break;
		case KEY_DOWN:
			if(cursorPos < botOptPos)
			{
				cursorPos++; // move cursor down one
			}
			break;
		case '\n':
			// if enter pressed, set the state of the choice that
			// was selected
			setState(mc[cursorPos - topOptPos].stateID);
		default:
			break;
	}
}

void renderMainMenu()
{
	// perform setup for printing title banner
	int leftEdgePos = (int) (80 - titleColumns)/2;
	int x = leftEdgePos;
	int y = TOP_BANNER_PAD;
	int i;

	// print out title banner
	for(i = 0; i < titleColumns * titleRows; i++)
	{
		mvaddch(y, x, titleText[i]);
		if((x - leftEdgePos) >= (titleColumns-1))
		{
			x = leftEdgePos;
			y++;
		} else x++;
	}

	// move cursor to correct row to print out choices
	y = TOP_BANNER_PAD + titleRows + BANNER_OPTIONS_PAD;

	// print out choices
	for(i = 0; i < currentNumChoices; i++)
	{
		y++;
		leftEdgePos = (int) (80 - strlen(mc[i].text))/2;
		// add cursors to indicate slected choice
		if(y == cursorPos)
		{
			mvaddstr(y, leftEdgePos - 3, "-> ");
			mvaddstr(y, leftEdgePos + strlen(mc[i].text), " <-");
		}
		mvaddstr(y, leftEdgePos, mc[i].text);
	}
	mvprintw(22,0, "Use arrow keys to select an option"); 
	mvprintw(23,0, "Select an option with (Enter)"); 
	mvprintw(24,0, "Select \"Quit\" or press (ESC) to quit"); 
}

void cleanupMenu()
{
	free(mc);
	free(titleText);
}
