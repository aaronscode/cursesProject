#ifndef __DIALOGUE_H__
#define __DIALOGUE_H__

#include <string.h>

#define MAX_NUM_DIALOGUE_LINES 30

bool dialogueUp;

void loadDialogues();
void setDialogue(int dID);
void updateDialogue(int key);
void renderDialogue();

typedef struct dialogue 
{
	int numLines;
	char dialogueText[MAX_NUM_DIALOGUE_LINES][78];
} dialogue;

#include "dialogue.c"

#endif
