#define MAX_CHOICE_CHARS 30 // max number of chars a menu option can have

typedef struct
{
	int id;
	char text[MAX_CHOICE_CHARS];
} menuChoice;

menuChoice *mc;

int numChoices, currentNumChoices = 0;
int screenHeight, screenWidth;
int titleColumns, titleRows;

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
	if((columns > 80) || (rows > (25 - 1 - numChoices)))
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
	return TRUE;
}

//int initMenuChoice(int id, char choiceText[]

void updateMainMenu()
{

}

void renderMainMenu()
{
	int leftEdgePos = (int) (80 - titleColumns)/2;
	int x = leftEdgePos;
	int y = 2;
	int i;
	for(i = 0; i < 81; i++)
	{
		mvprintw(0, i, "%d", i%10);
	}
	for(i = 0; i < titleColumns * titleRows; i++)
	{
		mvaddch(y, x, titleText[i]);
		if((x - leftEdgePos) >= (titleColumns-1))
		{
			x = leftEdgePos;
			y++;
		} else x++;
	}

}
void cleanupMenu()
{
	free(mc);
	free(titleText);
}
