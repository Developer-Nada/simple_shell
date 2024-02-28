#include "inf.h"

/**
 * inf_strcpy - copies a string
 * @inf_dest: the destination
 * @inf_src: the source
 *
 * Return: pointer to destination
 */
char *inf_strcpy(char *inf_dest, char *inf_src)
{
        int inf_i = 0;

        if (inf_dest == inf_src || inf_src == 0)
                return (inf_dest);
        while (inf_src[inf_i])
        {
                inf_dest[inf_i] = inf_src[inf_i];
                inf_i++;
        }
        inf_dest[inf_i] = 0;
        return (inf_dest);
}

/**
 * inf_strdup - duplicates a string
 * @inf_str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *inf_strdup(const char *inf_str)
{
        int inf_length = 0;
        char *inf_ret;

        if (inf_str == NULL)
                return (NULL);
        while (*inf_str++)
                inf_length++;
        inf_ret = malloc(sizeof(char) * (inf_length + 1));
        if (!inf_ret)
                return (NULL);
        for (inf_length++; inf_length--;)
                inf_ret[inf_length] = *--inf_str;
        return (inf_ret);
}

/**
 * inf_puts - prints an input string
 * @inf_str: the string to be printed
 *
 * Return: Nothing
 */
void inf_puts(char *inf_str)
{
        int inf_i = 0;

        if (!inf_str)
                return;
        while (inf_str[inf_i] != '\0')
        {
                inf_putchar(inf_str[inf_i]);
                inf_i++;
        }
}

/**
 * inf_putchar - writes the character c to stdout
 * @inf_c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int inf_putchar(char inf_c)
{
        static int inf_i;
        static char inf_buf[WRITE_BUF_SIZE];

        if (inf_c == BUF_FLUSH || inf_i >= WRITE_BUF_SIZE)
        {
                write(1, inf_buf, inf_i);
                inf_i = 0;
        }
        if (inf_c != BUF_FLUSH)
                inf_buf[inf_i++] = inf_c;
        return (1);
}

