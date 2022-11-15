#include "shell.h"

/**
 *handle_signal- it keeps track is interactive mode
 *@i: the signal number
 *Return: nothing
 */

void handle_signal(__attribute__((unused))int i)
{
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, "$ ", 2);
}
