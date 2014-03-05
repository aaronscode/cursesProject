CFLAGS=-Wall -g

all:
	del cursesProject.exe
	gcc -o cursesProject.exe main.c -lpdcurses

unix:
	rm cursesProject
	gcc -o cursesProject main.c -lncurses

test:
	cursesProject
