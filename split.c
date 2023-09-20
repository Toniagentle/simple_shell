#include "main.h"

/**
 * strsplit - splits a string into substrings based on a separator
 * @str: string to split
 * @separator: the separator character to split the string
 * @num_strings: The number of strings in the whole string
 *
 * Return: pointer to an array of strings (Success) or NULL (Error)
 */
char **strsplit(char *str, char separator, size_t *num_strings)
{
	size_t num_words;
	char **matrix;

	if (str == NULL || separator == '\0')
	{
		if (num_strings != NULL)
			*num_strings = 0;
		return (NULL);
	}
	num_words = count_words(str, separator);
	if (num_strings != NULL)
		*num_strings = num_words;
	if (num_words == 0)
		return (NULL);

	matrix = _allocate_memory_for_matrix(num_words);

	if (matrix == NULL)
		return (NULL);

	_extract_substrings(str, separator, matrix);

	return (matrix);
}
/**
 * count_words - Count the number of words in a string
 * @str: The string from which words are to be counted.
 * @separator: The separator to split the words
 *
 * Return: The number of words in a string
 */
size_t count_words(char *str, char separator)
{
	size_t num_words = 0;
	bool in_word = false;
	char *ptr;

	for (ptr = str; *ptr != '\0'; ptr++)
	{
		if (*ptr == separator)
		{
			if (in_word)
			{
				num_words++;
				in_word = false;
			}
		}
		else
		{
			if (!in_word)
				in_word = true;
		}
	}
	if (in_word)
		num_words++;
	return (num_words);
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
 * _extract_substring - Extract a single string from a whole string
 * @str: The string to extract from
 * @start: The start of the whole string
 * @end: The end of the whole string
 *
 * Return: The extracted substring.
 */
char *_extract_substring(char *str, int start, int end)
{
	int length = end - start, i;
	char *temp = (char *)malloc(sizeof(char) * (length + 1));

	if (temp == NULL)
		return (NULL);

	for (i = 0; i < length; i++)
		temp[i] = str[start + i];
	temp[length] = '\0';
	return (temp);
}
/**
 * _cleanup_matrix - Free memory allocated for the matrix and its strings.
 * @matrix: The matrix to be cleaned up
 * @num_words: The number of words in the matrix
 */
void _cleanup_matrix(char **matrix, int num_words)
{
	int i;

	for (i = 0; i < num_words; i++)
		free(matrix[i]);
	free(matrix);
}
