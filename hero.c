int calcLevel(int experience)
{
	return (int)(experience / 30);
}

int calcAttack(int level)
{
	return 6 + 2 * level;
}

int calcDefense(int level)
{
	return 6 + 2 * level;
}

int calcHP(int level)
{
	return 20 + 3 * level;
}

int calcSpeed(int level)
{
	return 10 + 2 * level;
}
