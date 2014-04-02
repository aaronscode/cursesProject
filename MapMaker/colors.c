/*
 * Aaron Gross
 */

#include <stdio.h>
#include <curses.h>

#ifdef _WIN32		// defs to check OS
#endif
#ifdef __unix__
#define is_unix 1
int colors[] = {0,
		1,
		2,
		3,
		4,
		5,
		6,
		7};
#else
#define is_unix 0
int colors[] = {0,
		4,
		2,
		6,
		1,
		5,
		3,
		7};
#endif

WINDOW *w;
int main(int argc, char *argv[])
{
	w = initscr();
	start_color();
	keypad(w, TRUE);
	cbreak();
	noecho();
 
	int i, j;
	int k = 0;
	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 8; j++)
		{
			if(k)
			{
				init_pair(k, colors[i], colors[j]);
			}
			color_set(k, NULL);
			mvprintw(i,j, "@");
			k++;
		}
	}
	color_set(0, NULL);
	mvprintw(16, 0, "Colors: %d", COLORS);
	mvprintw(17, 0, "ColorPairs: %d", COLOR_PAIRS);
	mvprintw(18, 0, "BLACK: %d", COLOR_BLACK);
	mvprintw(19, 0, "RED: %d", COLOR_RED);
	mvprintw(20, 0, "GREEN: %d", COLOR_GREEN);
	mvprintw(21, 0, "YELLOW: %d", COLOR_YELLOW);
	mvprintw(22, 0, "BLUE: %d", COLOR_BLUE);
	mvprintw(23, 0, "MAGENTA: %d", COLOR_MAGENTA);
	getch();
	delwin(w);
    	endwin();
   	refresh();
	return 0;
}
