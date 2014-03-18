#define MAX_CHOICE_CHARS 30 // max number of chars a menu option can have

<<<<<<< HEAD
typedef struct
{
=======
typdef struct {
>>>>>>> 594583d7fab2cc5436533d28f08eb1f8e17c087e
	int id;
	char text[MAX_CHOICE_CHARS];
} menuChoice;

menuChoice *mc;

<<<<<<< HEAD
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
=======
void
>>>>>>> 594583d7fab2cc5436533d28f08eb1f8e17c087e
