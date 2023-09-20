#include "main.h"

/**
 *_handle_execute - Execute the program base on what the user enter
 *@arguments: The command passed in by the user.
 *@no_of_args: The number of argument the user passed in.
 *@envp: A pointer pointing to the environment variable.
 *
 *Return: Nothing if successfull, and -1 if fails.
 */
void _handle_execute(char **arguments, int no_of_args, char **envp)
{
	execve(arguments[0], arguments, envp);
	/*If execve fails*/
	_free_vector(arguments, no_of_args);
	_panic("Error (execv)");
	exit(EXIT_FAILURE);
}
