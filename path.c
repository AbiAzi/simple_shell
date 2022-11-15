#include "shell.h"

/**
* append_path - adds path to command
* @path: path of command
* @arg: user entered command
*
* Return: buffer of command with path
* NULL on failure
*/
char *append_path(char *path, char *arg)
{
	char *buf;
	size_t i = 0;
	size_t j = 0;

	if (arg == 0)
		arg = "";

	if (path == 0)
		path = "";

	buf = malloc(sizeof(char) * (_strlen(path) + _strlen(arg) + 2));
	if (!buf)
		return (NULL);

	while (path[i])
	{
		buf[i] = path[i];
		i++;
	}

	if (path[i - 1] != '/')
	{
		buf[i] = '/';
		i++;
	}
	while (arg[j])
	{
		buf[i + j] = arg[j];
		j++;
	}
	buf[i + j] = '\0';
	return (buf);
}
