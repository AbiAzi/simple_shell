#include "shell.h"

/**
* _path - finds the path from the global enviroment
* Return: The path if it is found ,NULL if not.
*/
char *_path(void)
{
	int i;
	char **env = environ, *path = NULL;

	while (*env != NULL)
	{
		if (_strncmp(*env, "PATH=", 5) == 0)
		{
			path = *env;
			while (*path && i < 5)
			{
				path++;
				i++;
			}
			return (path);
		}
		env++;
	}
	return (NULL);
}

/**
* entry - prints $ to let user know the program is
* ready to take their input
* prints the prompt if the shell is in interactive mode
* Return: no return
*/
void entry(void)
{
	if ((isatty(STDIN_FILENO) == 1) && (isatty(STDOUT_FILENO) == 1))
		flags.interactive = 1;
	if (flags.interactive)
		write(STDERR_FILENO, "# ", 2);
}
/**
* main - read, execute then print output loop
* @argc: argument count
* @argv: argument vector
* @envp: environment vector
*
* Return: 0
*/

int main(int argc, char **argv, char *envp[])
{
	char *buf = NULL;
	char *arph = NULL;
	char *dir = NULL;
	size_t n = 0;
	ssize_t l = 0;
	char **argu = NULL, **paths = NULL;
	(void)envp, (void)argv;

	if (argc < 1)
		return (-1);
	signal(SIGINT, handle_signal);
	while (1)
	{
		free_buffers(argu);
		free_buffers(paths);
		free(arph);
		entry();
		l = getline(&buf, &n, stdin);
		if (l < 0)
			break;
		info.ln_count++;
		if (buf[l - 1] == '\n')
			buf[l - 1] = '\0';
		argu = tokenizer(buf);
		if (argu == NULL || *argu == NULL || **argu == '\0')
			continue;
		if (checker(argu, buf))
			continue;
		dir = _path();
		paths = tokenizer(dir);
		arph = test_path(paths, argu[0]);
		if (!arph)
			perror(argv[0]);
		else
			exe(arph, argu);
	}
	if (l < 0 && flags.interactive)
		write(STDERR_FILENO, "\n", 1);
	free(buf);
	return (0);
}
