#include "shell.h"

/**
 * get_location - Locates a command in the PATH.
 * @command: The command to locate.
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Otherwise - the full pathname of the command.
 */
char *fill_path_dir(char *path);
char *get_location(char *command)
{
	char **path, *i;
	list_t *dirs;
	list_t *h;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = get_path_dir(*path + 5);
	h = dirs;

	while (dirs)
	{
		i = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
		if (!i)
			return (NULL);

		_strcpy(i, dirs->dir);
		_strcat(i, "/");
		_strcat(i, command);

		if (stat(i, &st) == 0)
		{
			free_list(h);
			return (i);
		}

		dirs = dirs->next;
		free(i);
	}

	free_list(h);

	return (NULL);
}

/**
 * fill_path_dir - Copies path but also replaces leading/sandwiched/trailing
 *		   colons (:) with current working directory.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */
char *fill_path_dir(char *path)
{
	int i;
	int l = 0;
	char *copy;
	char *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				l += _strlen(pwd) + 1;
			else
				l++;
		}
		else
			l++;
	}
	copy = malloc(sizeof(char) * (l + 1));
	if (!copy)
		return (NULL);
	copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(copy, pwd);
				_strcat(copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(copy, ":");
				_strcat(copy, pwd);
			}
			else
				_strcat(copy, ":");
		}
		else
		{
			_strncat(copy, &path[i], 1);
		}
	}
	return (copy);
}

/**
 * get_path_dir - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
list_t *get_path_dir(char *path)
{
	int j;
	char **dirs;
	char *copy;
	list_t *head = NULL;

	copy = fill_path_dir(path);
	if (!copy)
		return (NULL);
	dirs = _strtok(copy, ":");
	free(copy);
	if (!dirs)
		return (NULL);

	for (j = 0; dirs[j]; j++)
	{
		if (add_node_end(&head, dirs[j]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
