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
	char *buf = NULL;
	size_t m = 10;

	while (av[n] != NULL)
	{
		printf("%s", av[n]);
		n++;
	}:
	//the getline part
buf = malloc(sizeof(char) * m);
printf("$");
getline(&buf, &m, stdin);

}
