#include "main.h"

/**
 *_strlen - Get the length of a string.
 *@string: The string to return the length.
 *
 *Return: The length of the string (Success), and 0 (fail).
 */
int _strlen(const char *string)
{
	int len = 0;

	while (*string != '\0')
	{
		len++;
		string++;
	}

	return (len);
}
