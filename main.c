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

void update();
void render();
void pause();

int main(int argc, char *argv[])
{
	bool running = TRUE;

	while(running)
	{
		update();
		render();
		pause();
	}

	return 0;
}

void update()
{

}

void render() 
{

}

void pause() 
{
	napms(500);
 	printf("Hello, World!\n");
}
