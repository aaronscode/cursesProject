int state = 1;
int prevState =0;
int substate = 0;

int getState()
{
	return state;
}

int getPrevState()
{
	return prevState;
}

int setState(int newState)
{
	prevState = state;
	state = newState;
}
