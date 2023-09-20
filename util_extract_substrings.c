#include "main.h"

/**
 * _extract_substrings - Extract substring from a whole string passed
 * @str: The whole string passed
 * @separator: The seperator to use for splitting the string
 * @matrix: The place to store the substrings
 *
 * Return: The extracted substrings.
*/
void _extract_substrings(char *str, char separator, char **matrix)
{
	int word_index = 0;
	bool in_word = false;
	char *start = str;
	char *ptr;

	for (ptr = str; *ptr != '\0'; ptr++)
	{
		if (*ptr == separator)
		{
			if (in_word)
			{
				int length = ptr - start;

				if (!_add_word_to_matrix(matrix, _extract_word(str, start - str,
								(int)(start - str + length)), word_index++))
				{
					_cleanup_matrix(matrix, word_index);
					return;
				}
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

		if (!_add_word_to_matrix(matrix, _extract_word(str, start - str,
						(int)(start - str + length)), word_index))
		{
			_cleanup_matrix(matrix, word_index);
			return;
		}
	}
}
/**
 * _extract_word - Extract a single word from a whole string
 * @str: The whole string
 * @start: The start of the word
 * @end: The end of the word
 *
 * Return: The extracted word as a new string.
 */
char *_extract_word(char *str, int start, int end)
{
	int i;
	int length = end - start;
	char *temp = (char *)malloc(sizeof(char) * (length + 1));

	if (temp == NULL)
		return (NULL);
	for (i = 0; i < length; i++)
		temp[i] = str[start + i];
	temp[length] = '\0';
	return (temp);
}
/**
 * _add_word_to_matrix - Add a word to the matrix, handling memory allocation.
 * @matrix: The matrix to store the word
 * @word: The word to add
 * @word_index: The index in the matrix to add the word
 *
 * Return: true on success, false on memory allocation failure.
 */
bool _add_word_to_matrix(char **matrix, char *word, int word_index)
{
	matrix[word_index] = word;

	if (matrix[word_index] == NULL)
	{
		return (false);
	}
	return (true);
}
