#include "shell.h"

/**
* tokenizer - creates tokens
* @line: to be tokenized
*
* Return: array of strings
*/
char **tokenizer(char *line)
{
	char *buf = NULL, *cpbuf = NULL, *t = NULL;
	char *delim = " :\t\r\n";
	char **token = NULL;
	int size = 1;
	size_t i = 0;
	size_t flag = 0;

	buf = _strdup(line);
	if (!buf)
		return (NULL);
	cpbuf = buf;

	while (*cpbuf)
	{
		if (_strchr(delim, *cpbuf) != NULL && flag == 0)
		{
			size++;
			flag = 1;
		}
		else if (_strchr(delim, *cpbuf) == NULL && flag == 1)
			flag = 0;
		cpbuf++;
	}
	token = malloc(sizeof(char *) * (size + 1));
	t = strtok(buf, delim);
	while (t)
	{
		token[i] = _strdup(t);
		if (token[i] == NULL)
		{
			free(token);
			return (NULL);
		}
		t = strtok(NULL, delim);
		i++;
	}
	token[i] = '\0';
	free(buf);
	return (token);
}
