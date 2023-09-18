void _buitin_command(char *command)
{
	int i;

	if (_strcmp(command, "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
		{
			printf("%s\n", environ[i]);
		}
	}
	else
		printf("Error: Unknown command '%s'\n", command);
}