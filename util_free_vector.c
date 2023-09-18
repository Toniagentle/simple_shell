#include "main.h"

/**
 *_free_vector - Free a pointer to a pointer
 * i.e it free a pointer pointing to a string
 *@listOfStrings: The vector, a pointer pointing to a pointer
 *@len: The length of the vector.
 *
 *Return: void
 */
void _free_vector(char **listOfStrings, size_t len)
{
	size_t i;

	if (listOfStrings == NULL)
		return;
	for (i = 0; i < len; i++)
	{
		if (listOfStrings[i] != NULL)
			free(listOfStrings[i]);
	}
	free(listOfStrings);
}
