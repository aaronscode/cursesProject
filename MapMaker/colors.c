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
	mvprintw(20,20,"%d", COLOR_RED);
	getch();
	delwin(w);
    	endwin();
   	refresh();
	return 0;
}
