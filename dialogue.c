int dialogueID; // ID of current dialogue to display
int curLine = 0;
bool dialogueUp = FALSE;

dialogue dialogues[3];

void loadDialogues()
{
	dialogues[0].numLines = 5;
	strcpy(dialogues[0].dialogueText[0], "YOUR AUTHORITY IS NOT RECOGNIZED IN FORT KICKASS! 0");
	strcpy(dialogues[0].dialogueText[1], "YOUR AUTHORITY IS NOT RECOGNIZED IN FORT KICKASS! 1");
	strcpy(dialogues[0].dialogueText[2], "YOUR AUTHORITY IS NOT RECOGNIZED IN FORT KICKASS! 2");
	strcpy(dialogues[0].dialogueText[3], "YOUR AUTHORITY IS NOT RECOGNIZED IN FORT KICKASS! 3");
	strcpy(dialogues[0].dialogueText[4], "YOUR AUTHORITY IS NOT RECOGNIZED IN FORT KICKASS! 4");

}

void setDialogue(int dID)
{
	dialogueID = dID;
	dialogueUp = TRUE;
	curLine = 0;
}

void updateDialogue(int key)
{
	switch(key)
	{
		case 'z':
			if(curLine < dialogues[dialogueID].numLines - 3) curLine++;
			else dialogueUp = FALSE;
			break;
		case 'x':
			if(curLine > 0) curLine--;
			break;
	}
}

void renderDialogue()
{
	mvprintw(20, 0, "O------------------------------------------------------------------------------O");
	int i;
	for(i = 0; i < 3; i++)
	{
		mvprintw(21 + i, 0, "|");
		mvprintw(21 + i, 1, "                                                                              ");
		if((i + curLine) < dialogues[dialogueID].numLines)
		{
			mvprintw(21 + i, 1, dialogues[dialogueID].dialogueText[curLine + i]);
		}
		mvprintw(21 + i, 79, "|");
	}
	mvprintw(24, 0, "O------------------------------------------------------------------------------O");
}
