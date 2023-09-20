#include "main.h"

/**
 * _panic - Display error message, encountered.
 *@string: The error message to display.
 *
 *Return: Nothing (void)
 */
void _panic(char *string)
{
	perror(string);
}
