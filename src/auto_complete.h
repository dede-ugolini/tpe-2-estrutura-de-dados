#include <stdio.h>

#include <readline/history.h>
#include <readline/readline.h>

typedef struct {
  char *name;
  rl_icpfunc_t *func;
  char *doc;
} Command;

char *dupstr(char *s);

char *command_generator(const char *text, int state);

char **fileman_completion(const char *text, int start, int end);

void initialize_readline(char *progname, Command *comands);

int execute_line(char *line);
