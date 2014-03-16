CFLAGS=-Wall -g

all:
	del cursesProject.exe
	gcc -o cursesProject.exe main.c -lpdcurses

unix:
	gcc -o cursesProject main.c -lncurses

test:
	./cursesProject

clean:
	rm cursesProject
