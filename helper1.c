#include "shell.h"

/**
 * free_args - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the beginning of args.
 */
void variable_replacement(char **line, int *exe_ret);
void free_args(char **args, char **front)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(front);
}

/**
 * get_pid - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */
char *get_pid(void)
{
	size_t i = 0;
	char *buf;
	ssize_t f;

	f = open("/proc/self/stat", O_RDONLY);
	if (f == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buf = malloc(120);
	if (!buf)
	{
		close(f);
		return (NULL);
	}
	read(f, buf, 120);
	while (buf[i] != ' ')
		i++;
	buf[i] = '\0';

	close(f);
	return (buf);
}

/**
 * get_env_value - Gets the value corresponding to an environmental variable.
 * @beginning: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *get_env_value(char *beginning, int len)
{
	char **addr;
	char *nw = NULL, *i, *v;

	v = malloc(len + 1);
	if (!v)
		return (NULL);
	v[0] = '\0';
	_strncat(v, beginning, len);

	addr = _getenv(v);
	free(v);
	if (addr)
	{
		i = *addr;
		while (*i != '=')
			i++;
		i++;
		nw = malloc(_strlen(i) + 1);
		if (nw)
			_strcpy(nw, i);
	}

	return (nw);
}

/**
 * variable_replacement - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void variable_replacement(char **line, int *exe_ret)
{
	int j, k = 0, l;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
				old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replacement = get_pid();
				k = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				k = j + 2;
			}
			else if (old_line[j + 1])
			{
				/* extract the variable name to search for */
				for (k = j + 1; old_line[k] &&
						old_line[k] != '$' &&
						old_line[k] != ' '; k++)
					;
				l = k - (j + 1);
				replacement = get_env_value(&old_line[j + 1], l);
			}
			new_line = malloc(j + _strlen(replacement)
					  + _strlen(&old_line[k]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, j);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}
