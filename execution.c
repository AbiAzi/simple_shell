#include "shell.h"

/**
 * exe - executes commands entered by users
 *@command: command
 *@buf:vector array of pointers to commands
 * Return: 0
 */

void exe(char *command, char **buf)
{
	pid_t pid;
	char **env = environ;
	int s;

	pid = fork();
	if (pid < 0)
		perror(command);
	if (pid == 0)
	{
		execve(command, buf, env);
		perror(command);
		free(command);
		free_buffers(buf);
		exit(98);
	}
	else
		wait(&s);
}
