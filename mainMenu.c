#define MAX_CHOICE_CHARS 30 // max number of chars a menu option can have

typdef struct {
	int id;
	char text[MAX_CHOICE_CHARS];
} menuChoice;

menuChoice *mc;

void
