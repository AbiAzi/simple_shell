#include "shell.h"

/**
* free_buffers - frees buffers
* @buf: buffer to be freed
*
* Return: no return
*/
void free_buffers(char **buf)
{
	int i = 0;

	if (!buf || buf == NULL)
		return;
	while (buf[i])
	{
		free(buf[i]);
		i++;
	}
	free(buf);
}

/**
* exit_cmd - handles the exit command
* @ctok: the tokenized strings
* @l: input read from stdin
*
* Return: no return
*/

void exit_cmd(char **ctok, char *l)
{
	free(l);
	free_buffers(ctok);
	exit(0);
}
