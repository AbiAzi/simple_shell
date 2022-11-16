#ifndef SHELL
#define SHELL

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>

/* environment variables */
extern char **environ;
extern __sighandler_t signal(int __sig, __sighandler_t __handler);

/* handle built ins */
int checker(char **cmd, char *buf);
void entry(void);
void handle_signal(int m);
char **tokenizer(char *line);
char *test_path(char **path, char *command);
char *append_path(char *path, char *arg);
int handle_builtin(char **command, char *line);
void exit_cmd(char **ctok, char *l);

void print_env(void);

/* a new environment variable, or modify & Remove an environment variable */
//char **get_environ(info_t *ino);
//int _unsetenv(info_t *ino, char *var);
//int _setenv(info_t *ino, char *var, char *value);

/* string handlers */
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
int _strncmp(char *s1, char *s2, int n);
char *_strdup(char *s);
char *_strchr(char *s, char c);

void exe(char *command, char **buf);
char *_path(void);

/* helper function for efficient free */
void free_buffers(char **buf);

/**
 *struct builtin - a char structure
 *@env: an environment char
 *@exit: the exit char
 *Description: accept two char from builtin
 */
struct builtin
{
	char *env;
	char *exit;
} builtin;

/**
 *struct info - and int structure
 *@final_exit: an int for the final exit
 *@in_count: an int that count
 *Description: an int that increment
 */
struct info
{
	int final_exit;
	int ln_count;
} info;

/**
 *struct flag - a bool struct
 *@interactive: 0 or 1
 *Description: it holds a bool
 */
struct flags
{
	bool interactive;
} flags;

#endif
