#include <stdio.h>
/**
 * main - le main
 * @av: NULL terminated array of strings
 * @ac: is the number of items in av
 * Return: int
 */
int main(int ac, char **av)
{
	int n = 0;

	while (av[n] != NULL)
	{
		printf("%s", av[n]);
		n++;
	}
}
