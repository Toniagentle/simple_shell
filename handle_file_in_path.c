#include "main.h"

/**
 *_handle_file_in_path - Check an executable in path
 *@executable: The executable (command) to check in path.
 *@statbuffer: The status of the executable
 *
 *Return: The full path of the executable (command)
 */
char *_handle_file_in_path(char *executable, struct stat *statbuffer)
{
	size_t i, path_count;
	char *fullPath;
	char *pathValues = getenv("PATH");
	/*char **paths = _strsplit(pathValues, ':', &path_count);*/
	char **paths = strsplit(pathValues, ':', &path_count);

	/*Loop through the path*/
	for (i = 0; i < path_count; i++)
	{
		/*Concatenate each path with the executable command name*/
		fullPath = _str_concat(3, paths[i], "/", executable);
		/*check the execuatable filename status*/
		if (_handle_file_status(statbuffer, fullPath))
		{
			_free_vector(paths, path_count);
			return (fullPath);
		}
		free(fullPath);
		fullPath = NULL;
	}
	/*if executable doesn't exit in any of the paths*/
	_free_vector(paths, path_count);
	return (NULL);
}
