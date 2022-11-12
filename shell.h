#ifndef SHELL
#define SHELL

#include <stddef.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "typedefs.h"
#include "constants.h"

extern char **environ;
char *name;
alias_t *aliases;
void signal_handler(int);
char *get_user_input();
void readline_error(void);

void (*handle_error[])(void) = {
    readline_error
};


#endif
