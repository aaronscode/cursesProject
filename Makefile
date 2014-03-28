CFLAGS=-Wall -g

all:
	del SpankWagon.exe
	gcc -o SpankWagon.exe main.c -lpdcurses

unix:
	gcc -o SpankWagon main.c -lncurses

test:
	SpankWagon

clean:
	rm SpankWagon
