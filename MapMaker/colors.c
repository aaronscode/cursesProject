/*
 * Aaron Gross
 */

#include <stdio.h>
#include <curses.h>

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
	for(i = 0; i < 16; i++)
	{
		for(j = 0; j < 16; j++)
		{
			if(k)
			{
				init_pair(k, i, j);
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
