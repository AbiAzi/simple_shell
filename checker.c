#include "shell.h"

/**
 *checker- checks if it is built in function
 *@com: tokenized user input
 *@buf: line drived fromgetline function
 *Return: 1 if com excuted 0 if not
 */

int checker(char **com, char *buf)
{
	if (handle_builtin(com, buf))
		return (1);
	else if (**com == '/')
	{
		exe(com[0], com);
		return (1);
	}
	return (0);
}
