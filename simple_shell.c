#include "main.h"

/**
 * main - Entry point
 * @argc: Argument count
 * @env: Environment variable
 *  Return: Always 0 if success and 1 if otherwise
*/
int main(int argc, char **env)
{
	char *buffer = NULL;
	char *prompt = "$ ";
	ssize_t bytes_read;
	size_t buffer_size = 0;
	bool user_piped = false;

	(void)argc;

	while (1 && !user_piped)
	{
		if (isatty(STDIN_FILENO) == 0)
		{
			user_piped = true;
		}
		else
			write(STDOUT_FILENO, prompt, 2);

		bytes_read = getline(&buffer, &buffer_size, stdin);

		if (bytes_read == -1)
		{
			free(buffer);
			exit(EXIT_FAILURE);
		}

		if (*buffer != '\n')
		{
			if (buffer[bytes_read - 1] == '\n')
				buffer[bytes_read - 1] = '\0';

			_handle_command(buffer, env);
		}
	}
	free(buffer);
	return (0);
}

/**
 * _execute_command - Execute the command passed by the user
 * @args: The argument vector
 * @no_of_args: The number of strings argument passed
 * @env: The enironment variable
 *  Return: Void
*/
void _execute_command(char **args, size_t no_of_args, char **env)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		_free_vector(args, no_of_args);
		_panic("Error (fork)");
	}

	if (pid == 0)
	{
		_handle_execute(args, no_of_args, env);
	}

	if (waitpid(pid, NULL, 0) == -1)
	{
		_free_vector(args, no_of_args);
		_panic("Error (wait)");
	}
	_free_vector(args, no_of_args);
}

/**
 * _handle_command - Handle the command passed and parse it
 * @command: The command passed
 * @env: The enviroment variable
 * Return: void
*/
void _handle_command(char *command, char **env)
{
	struct stat statbuffer;
	char **args;
	size_t no_of_args;
	int status;

	status = EXIT_SUCCESS;
	/* Split the arguments into separate strings */
	args = strsplit(command, ' ', &no_of_args);
	if (args == NULL)
	{
		printf("Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	if (_strcmp("exit", args[0]) == 0)
	{
		status = _atoi(args[1]);
		_free_vector(args, no_of_args);
		exit(status);
	} else if (_strcmp("env", args[0]) == 0)
	{
		_handle_builtin_command(args[0]);
	}
	if (!_handle_file_status(&statbuffer, args[0]))
	{
		char *fullpath;

		fullpath = _handle_file_in_path(args[0], &statbuffer);
		if (fullpath)
		{
			args[0] = fullpath;
		}
		else
		{
			printf("Executable not found\n");
			_free_vector(args, no_of_args);
			return;
		}
	}
	_execute_command(args, no_of_args, env);
}
