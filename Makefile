CFLAGS=-Wall -g

all:
	del cursesProject.exe
	gcc -o cursesProject.exe cursesProject.c 

test:
	final
