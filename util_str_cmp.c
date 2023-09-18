#include "main.h"

/**
 *_strcmp - compare string values
 *@string1: input value
 *@string2: input value
 *
 *Return: s1[i] - s2[i]
 */
int _strcmp(char *string1, char *string2)
{
	int i;

	i = 0;
	while (string1[i] != '\0' && string2[i] != '\0')
	{
		if (string1[i] != string2[i])
		{
			return (string1[i] - string2[i]);
		}
		i++;
	}
	return (0);
}
