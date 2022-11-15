#include "shell.h"

/**
* test_path - checks whether path is valid
* @path: tokenized path
* @arg: user entered command
*
* Return: path appended with command on success
* NULL on failure
*/
char *test_path(char **path, char *arg)
{
	int i = 0;
	char *s;

	while (path[i])
	{
		s = append_path(path[i], arg);
		if (access(s, F_OK | X_OK) == 0)
			return (s);
		free(s);
		i++;
	}
	return (NULL);
}
