#include "main.h"

/**
 * _handle_file_status - Check if a pathname exit or not.
 * @pathname: The pathname to check if exit or not
 * @statbuffer: A pointer to the buffer containing the pathname
 *
 * Return: True if found and false if not found.
 */
bool _handle_file_status(struct stat *statbuffer, char *pathname)
{
	int status_value;

	status_value = stat(pathname, statbuffer);
	/*If file is found based on the provided pathname*/
	if (status_value == 0)
		return (true);
	return (false);
}
