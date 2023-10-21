#include "declare.h"


/**
 * string_copy - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to the destination
 */

char *string_copy(char *destination, char *source)
{
    int i = 0;

    if (destination == source || source == NULL)
        return destination;

    while (source[i])
    {
        destination[i] = source[i];
        i++;
    }

    destination[i] = 0;

    return destination;
}

/**
 * string_duplicate - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */

char *string_duplicate(const char *str)
{
    int length = 0;
    char *ret;

    if (str == NULL)
        return NULL;

    while (*str++)
        length++;

    ret = malloc(sizeof(char) * (length + 1));

    if (!ret)
        return NULL;

    for (length++; length--;)
        ret[length] = *--str;

    return ret;
}

/**
 * print_string - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void print_string(char *str)
{
    int i = 0;

    if (!str)
        return;

    while (str[i] != '\0')
    {
        write_character(str[i]);
        i++;
    }
}

/**
 * write_character - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_character(char c)
{
    static int i;
    static char buffer[WRITE_BUFFER_SIZE];

    if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
    {
        write(1, buffer, i);
        i = 0;
    }

    if (c != BUFFER_FLUSH)
        buffer[i++] = c;

    return 1;
}