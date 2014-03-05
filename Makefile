CFLAGS=-Wall -g

all:
	del cursesProject.exe
	gcc -o cursesProject.exe cursesProject.c -libpdcurses

unix:
	rm cursesProject
	gcc -o cursesProject cursesProject.c -libncurses

test:
	cursesProject
