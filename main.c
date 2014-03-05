/*
 * Aaron Gross
 * cursesProject.c
 * 3/4/14
 * V 0.1
 */

#include <stdio.h>
#include <curses.h>

#ifdef _WIN32		// defs to check OS
#define Herp "Derp"     // may put in .h file later to reduce clutter
#endif
#ifdef __linux__
#define Herp "Herp"
#endif

int main(int argc, char *argv[])
{
	bool running = TRUE;
 	printf("Hello, World!\n");

	return 0;
}
