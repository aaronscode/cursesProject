#define MAX_CHOICE_CHARS 30 // max number of chars a menu option can have

typedef struct
{
	int id;
	char text[MAX_CHOICE_CHARS];
} menuChoice;

menuChoice *mc;

int numChoices;
int screenHeight, screenWidth;
int titleColumns, titleRows;

void initMenu(int numberOfChoices, int width, int height)
{
	mc = (menuChoice*) malloc(numberOfChoices * sizeof(menuChoice));
	numChoices = numberOfChoices;
	screenWidth = width;
	screenHeight = height;
}

bool initTitle(int columns, int rows, char text)
{
	if((columns > 80) || (rows > (25 - 1 - numChoices)))
	{
		return FALSE;
	}
	titleColumns = columns;
	titleRows = rows;

}

void updateMainMenu()
{
}

void cleanupMenu()
{
	free(mc);
}
