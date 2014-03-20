#define MAX_CHOICE_CHARS 30 // max number of chars a menu option can have
#define TOP_BANNER_PAD 2
#define BANNER_OPTIONS_PAD 4

typedef struct
{
	int stateID;
	char text[MAX_CHOICE_CHARS];
} menuChoice;

menuChoice *mc;

int numChoices, currentNumChoices = 0;
int screenHeight, screenWidth;
int titleColumns, titleRows;
int cursorPos;
int topOptPos, botOptPos;

char *titleText;

void initMenu(int numberOfChoices, int width, int height)
{
	mc = (menuChoice*) malloc(numberOfChoices * sizeof(menuChoice));
	numChoices = numberOfChoices;
	screenWidth = width;
	screenHeight = height;
}

bool initTitle(int columns, int rows, char *text)
{
	if((columns > SCREEN_WIDTH)||(rows > (SCREEN_HEIGHT - 1 - numChoices)))
	{
		return FALSE;
	}
	titleColumns = columns;
	titleRows = rows;
	titleText = malloc(rows * columns + 1);

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
	switch(key)
	{
		case KEY_UP:
			if(cursorPos > topOptPos)
			{
				cursorPos--;
			}
			break;
		case KEY_DOWN:
			if(cursorPos < botOptPos)
			{
				cursorPos++;
			}
			break;
		case '\n':
			setState(mc[topOptPos-cursorPos].stateID);
		default:
			break;
	}
}

void renderMainMenu()
{
	int leftEdgePos = (int) (80 - titleColumns)/2;
	int x = leftEdgePos;
	int y = TOP_BANNER_PAD;
	int i;

	/*
	for(i = 0; i < 81; i++)
	{
		mvprintw(0, i, "%d", i%10);
	}
	*/

	for(i = 0; i < titleColumns * titleRows; i++)
	{
		mvaddch(y, x, titleText[i]);
		if((x - leftEdgePos) >= (titleColumns-1))
		{
			x = leftEdgePos;
			y++;
		} else x++;
	}

	y = TOP_BANNER_PAD + titleRows + BANNER_OPTIONS_PAD;

	for(i = 0; i < currentNumChoices; i++)
	{
		y++;
		leftEdgePos = (int) (80 - strlen(mc[i].text))/2;
		if(y == cursorPos)
		{
			mvaddstr(y, leftEdgePos - 3, "-> ");
			mvaddstr(y, leftEdgePos + strlen(mc[i].text), " <-");
		}
		mvaddstr(y, leftEdgePos, mc[i].text);
	}
}

void cleanupMenu()
{
	free(mc);
	free(titleText);
}
