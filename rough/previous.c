#include "main.h"


/**
 * strsplit - splits a string into substrings based on a seperator
 * @str: string to split
 * @separator: the seperator character to split the string
 * @num_strings: The number of strings in the whole strings
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
 *count_words - Count the number of words in a string
 *@str: The sting from which word is to be counted.
 *@separator: The seperated to split the words
 *
 *Return: The number of word in a string
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
								(int)(start - str + length)), word_index))
				{
					_cleanup_matrix(matrix, word_index);
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



/*Taking and checking*/

#include "main.h"
/**
 * _extract_substrings - Extract substrings from a whole string passed
 * @str: The whole string passed
 * @separator: The separator to use for splitting the string
 * @matrix: The place to store the substrings
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
                
                matrix[word_index] = _extract_substring(str, start - str, (int)(start - str + length));
                if (matrix[word_index] == NULL)
                {
                    _cleanup_matrix(matrix, word_index);
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

        matrix[word_index] = _extract_substring(str, start - str, (int)(start - str + length));
        if (matrix[word_index] == NULL)
        {
            _cleanup_matrix(matrix, word_index);
            return;
        }
    }
}