#include "main.h"


/**
 * _str_concat - Concatenate strings
 *@num_strings:  The number of string to join (concatenate)
 *
 * Return: The concatenated strings
 */
char *_str_concat(int num_strings, ...)
{
	char *fullString;
	va_list args;
	size_t total_length;

	va_start(args, num_strings);

	total_length = _calculate_total_length(num_strings, args);

	va_end(args);

	fullString = (char *)malloc(total_length + 1);
	if (fullString == NULL)
	{
		return (NULL);
	}

	va_start(args, num_strings);
	_copy_strings(fullString, num_strings, args);
	va_end(args);
	fullString[total_length] = '\0';
	return (fullString);
}

/**
 * _calculate_total_length - calculate total length of all strings
 * @num_strings: The number of string to join (concatenate)
 * @args: The list of the strings to concate
 * Return: The total length of the whole string
 */
size_t _calculate_total_length(int num_strings, va_list args)
{
	size_t total_length = 0;
	const char *s;
	int i;

	for (i = 0; i < num_strings; i++)
	{
		s = va_arg(args, const char *);

		if (s == NULL)
		{
			s = "";
		}
		total_length += _strlen(s);
	}
	return (total_length);
}

/**
 * _copy_strings - Copy strings into the concatenated string
 * @fullstring: Pointer to the string that are concat
 * @num_strings: The number of string to join (concatenate)
 * @args: The list of the strings to concate
 * Return: Pointer to the concatenated strings
 */
void _copy_strings(char *fullstring, int num_strings, va_list args)
{
	size_t current_index = 0, len;
	const char *s;
	int i;

	for (i = 0; i < num_strings; i++)
	{
		s = va_arg(args, const char *);
		if (s == NULL)
		{
			s = "";
		}
		len = _strlen(s);

		_strncpy(s, fullstring + current_index, len);
		current_index += len;
	}
}
