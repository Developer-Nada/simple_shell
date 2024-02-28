#include <stdio.h>
#include <stdlib.h>
/**
 * main - le main
 * Return: int
 */
int main(void)
{
	char *buf = NULL;
	size_t m = 10;


	buf = malloc(sizeof(char) * m);
	printf("$");
	getline(&buf, &m, stdin);
	printf("%s", buf);
		return (0);

}
