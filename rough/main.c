


#include "shell.h"

char *read_user_input() {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t bytes_read = getline(&buffer, &buffer_size, stdin);

    if (bytes_read == -1) {
        free(buffer);
        exit(EXIT_FAILURE);
    }

    if (*buffer != '\n') {
        if (buffer[bytes_read - 1] == '\n') {
            buffer[bytes_read - 1] = '\0';
        }
    }

    return buffer;
}

void process_command(char *command, char **env) {
    if (*command != '\0') {
        size_t no_of_args;
        char **args = _strsplit(command, ' ', &no_of_args);

        if (args == NULL) {
            printf("Memory allocation error\n");
            return;
        }

        if (_strcmp("exit", args[0]) == 0) {
            _free_vector(args, no_of_args);
            free(command);
            exit(EXIT_SUCCESS);
        } else if (_strcmp("env", args[0]) == 0) {
            _buitin_command(args[0]);
        }

        // ... Handle checking file status, finding full path, etc.

        // Execute command
        _execute(args, no_of_args, env);
        _free_vector(args, no_of_args);
    }
    free(command);
}

int main(int argc, char **env) {
    const char *prompt = "$ ";
    char *buffer;
    ssize_t bytes_read;
    bool user_piped = false;

    // ... Other declarations and initializations

    while (1 && !user_piped) {
        // ... Check if in interactive mode or from pipe
        

        prompt_user(prompt);
        buffer = read_user_input();

        process_command(buffer, env);
    }

    return 0;
}



#include "shell.h"

/*
*main - Entry Point
*@argc: the argument counts.
*@env: Hold the enviroment variable
*
*Return: 0 if success and 1 if otherwise
*/
int main(int argc, char **env)
{
    char *buffer = NULL;
    char *prompt = "$ ";
    ssize_t bytes_read;
    size_t no_of_args, buffer_size = 0;
    pid_t pid;
    int wstatus;
    char **args;
    char *fullpath;
    bool user_piped = false;
    struct stat statbuffer;
    
    (void)argc;

    /*Enter an infinite loop*/
    while (1 && !user_piped)
    {
        /*Check if in interactive mode or from pipe*/
        if (isatty(STDIN_FILENO) == 0)
            user_piped = true;
            
        /*Prompt the user to write a command*/
        write(STDOUT_FILENO, prompt, 2);

        /* Read the command from the standard input from the user*/
        bytes_read = getline(&buffer, &buffer_size, stdin);

        /*Check for error*/
        if (bytes_read == -1)
        {
            free(buffer);
            exit(EXIT_FAILURE);
        }

        if (*buffer != '\n')
        {
            /*If successfull replace the newline character with a Null terminator*/
            if (buffer[bytes_read - 1] == '\n')
                buffer[bytes_read - 1] = '\0';

            /*Split the arguments into seperate strings*/
            args = _strsplit(buffer, ' ', &no_of_args);
            if (args == NULL) {
                printf("Memory allocation error\n");
                free(buffer);
                exit(EXIT_FAILURE);
            }
            /*Handle exit */
            if (_strcmp("exit", args[0]) == 0)
            {
                _free_vector(args, no_of_args);
                break;
            }
            else if (_strcmp("env", args[0]) == 0)
            {
                _buitin_command(args[0]);
            }
            
            if (!_check_file_status(args[0], &statbuffer))
            {
                fullpath = _check_file_in_path(args[0], &statbuffer);
                if (fullpath) 
                {
                    /*Update the executable argument to the correct full path*/
                    args[0] = fullpath;
                    printf("The fullpath is %s\n", fullpath);
                } 
                else
                {
                    /*Handle the case where the executable was not found*/
                    printf("Executable not found\n");
                    _free_vector(args, no_of_args);
                    continue;
                }
            }

            /*Create a child process*/
            pid = fork();

            /*check for error*/
            if (pid == -1)
            {
                _free_vector(args, no_of_args);
                _panic("Error (fork)");
            }

            /*If the child process is successful*/
            if (pid == 0)
            {
                /*Execute the command*/
                _execute(args, no_of_args, env);
            }

            /*Let the parent wait*/
            if (waitpid(pid, &wstatus, 0) == -1)
            {
                _free_vector(args, no_of_args);
                _panic("Error (wait)");
            }
            _free_vector(args, no_of_args);
        }
    }
    free(buffer);
    return (0);
}