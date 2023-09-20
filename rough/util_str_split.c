#include "main.h"

/**
 * _strsplit - splits a string into substrings based on a seperator
 * @str: string to split
 * @seperator: the seperator character to split the string
 * @num_strings: The number of strings in the whole strings
 *
 * Return: pointer to an array of strings (Success) or NULL (Error)
 */
char **_strsplit(char *str, char seperator, size_t *num_strings)
{
	size_t words;
	char **matrix;

	if (str == NULL || seperator == '\0')
	{
		if (num_strings != NULL)
			*num_strings = 0;
		return (NULL);
	}

	words = _count_words(str, seperator);

	if (num_strings != NULL)
		*num_strings = words;
	if (words == 0)
		return (NULL);

	matrix = _allocate_memory_for_matrix(words);

	if (matrix == NULL)
		return (NULL);
	_extract_substrings(str, seperator, matrix);
	return (matrix);
}

/**
 * _allocate_memory_for_matrix - Allocate space for the strings to split
 * @size: The size of the space to allocate
 *
 * Return: A pointer to the first space of the memory allocated.
*/

char **_allocate_memory_for_matrix(size_t size)
{
	return ((char **)malloc(sizeof(char *) * (size + 1)));
}

/**
 * _extract_substrings - Extract substring from a whole string passed
 * @str: The whole string passed
 * @seperator: The seperator to use for splitting the string
 * @matrix: The place to store the substrings
 *
 * Return: The extracted substrings.
*/
void _extract_substrings(char *str, char seperator, char **matrix)
{
	int i, k = 0, len = _strlen(str), c = 0, start, end;
	char *temp;

	for (i = 0; i <= len; i++)
	{
		if (str[i] == seperator || str[i] == '\0')
		{
			if (c > 0)
			{
				end = i;
				temp = _extract_substring(str, start, end);
				matrix[k++] = temp;
				c = 0;
				start = i + 1;
			}
		}
		else if (c == 0)
		{
			start = i;
		}
		c++;
	}
	matrix[k] = NULL;
}

/**
 * _extract_substring - Extract a single string from a whole string
 * @str: The string to extract from
 * @start: The start of the whole string
 * @end: The end of the whole string
 *
 * Return: Each of the strings extracted.
*/
char *_extract_substring(char *str, int start, int end)
{
	int j, index;
	char *temp;
	int len = end - start;

	temp = (char *)malloc(sizeof(char) * (len + 1));

	if (temp == NULL)
		return (NULL);
	index = 0;
	for (j = start; j < end; j++)
		temp[index++] = str[j];
	temp[index] = '\0';
	return (temp);
}





void _extract_substrings(char *str, char separator, char **matrix)
{
	int word_index = 0;
	bool in_word = false;
	char *start = str;
	char *ptr;
	int i;

	for (ptr = str; *ptr != '\0'; ptr++)
	{
		if (*ptr == separator)
		{
			if (in_word)
			{
				int length = ptr - start;

				matrix[word_index] = _extract_substring(str, start - str,
						(int)(start - str + length));
				if (matrix[word_index] == NULL)
				{
					for (i = 0; i < word_index; i++)
						free(matrix[i]);
					free(matrix);
					return;
				}
				word_index++;
				in_word = false;
			}
		}
		else
		{
			if (!in_word)
				start = ptr;
			in_word = true;
		}
	}
	if (in_word)
	{
		int length = ptr - start;

		matrix[word_index] = _extract_substring(str, start - str,
				(int)(start - str + length));
		if (matrix[word_index] == NULL)
		{
			for (i = 0; i <= word_index; i++)
				free(matrix[i]);
			free(matrix);
			return;
		}
	}
}
