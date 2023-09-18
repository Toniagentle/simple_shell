#include "main.h"

/**
 *_count_words - Count the number of words in a string
 *@string: The sting from which word is to be counted.
 *@seperator: The seperated to split the words
 *
 *Return: The number of word in a string
 */
int _count_words(char *string, char seperator)
{
	int flag, character, word;

	flag = 0;
	word = 0;

	for (character = 0; string[character] != '\0'; character++)
	{
		if (string[character] == seperator)
			flag = 0;
		else if (flag == 0)
		{
			flag = 1;
			word++;
		}
	}
	return (word);
}
