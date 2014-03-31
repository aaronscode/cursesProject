CFLAGS=-Wall -g

all:
	del SWMapMaker
	gcc -o SWMapMaker SWMapMaker.c -lpdcurses

unix:
	gcc -o SWMapMaker SWMapMaker.c -lncurses

test:
	./SWMapMaker
