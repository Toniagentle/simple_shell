#include "main.h"

/**
 * _strncpy - copy a string
 * @destination: input value
 * @string: input value
 * @n: input value
 * Return: dest
 */
char *_strncpy(const char *string, char *destination, int n)
{
	int j;

	j = 0;
	while (j < n && string[j] != '\0')
	{
		destination[j] = string[j];
		j++;
	}
	while (j < n)
	{
		destination[j] = '\0';
		j++;
	}
	return (destination);
}
