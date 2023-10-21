#include "declare.h"

/**
 * string_split - splits a string into words, ignoring repeat delimiters
 * @str: the input string
 * @delimiters: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **string_split(char *str, char *delimiters)
{
    int i, j, k, m, num_words = 0;
    char **strings;

    if (str == NULL || str[0] == 0)
        return NULL;

    if (!delimiters)
        delimiters = " ";

    for (i = 0; str[i] != '\0'; i++)
    {
        if (!is_character_delimiter(str[i], delimiters) && (is_character_delimiter(str[i + 1], delimiters) || !str[i + 1]))
            num_words++;
    }

    if (num_words == 0)
        return NULL;

    strings = malloc((1 + num_words) * sizeof(char *));
    if (!strings)
        return NULL;

    for (i = 0, j = 0; j < num_words; j++)
    {
        while (is_character_delimiter(str[i], delimiters))
            i++;

        k = 0;

        while (!is_character_delimiter(str[i + k], delimiters) && str[i + k])
            k++;

        strings[j] = malloc((k + 1) * sizeof(char));

        if (!strings[j])
        {
            for (k = 0; k < j; k++)
                free(strings[k]);
            free(strings);
            return NULL;
        }

        for (m = 0; m < k; m++)
            strings[j][m] = str[i++];

        strings[j][m] = 0;
    }

    strings[j] = NULL;

    return strings;
}


/**
 * string_split2 - splits a string into words using a single delimiter
 * @str: the input string
 * @delimiter: the delimiter character
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **string_split2(char *str, char delimiter)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delimiter && str[i + 1] == delimiter) ||
		    (str[i] != delimiter && !str[i + 1]) || str[i + 1] == delimiter)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == delimiter && str[i] != delimiter)
			i++;
		k = 0;
		while (str[i + k] != delimiter && str[i + k] && str[i + k] != delimiter)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

