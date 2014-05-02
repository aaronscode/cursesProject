int calcLevel(int experience)
{
	return pow((double) experience * 5 / 4, 1/3);
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
	return 20 + 3*level;
}

int calcSpeed(int level)
{
	return 10 + 2 * level;
}
