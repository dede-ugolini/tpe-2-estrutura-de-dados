#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *name;
  rl_icpfunc_t *func;
  char *doc;
} Command;

static bool done = false;

static int usage(char *arg) {
  puts("Usage");
  done = true;
  return 0;
};

static int quit(char *arg) {
  if (arg) {
    printf("%lu: len of arg\n", strlen(arg));
    printf("%lu: sizeof arg\n", sizeof(*arg));
    printf("[%s]: quit\n", arg);
  }
  return 0;
}

static int add(char *arg) {
  int i = atoi(arg);
  i += 5;
  printf("%d\n", i);
  return 0;
}

static int size(char *arg);

Command commands[] = {
    {"help", usage, "Display this text"},
    {"quit", quit, "Exit program"},
    {"add", add, "Add to 5"},
    {"size", size, "Size of command list"},
};

static int size(char *arg) {

  size_t len = sizeof(commands) / sizeof(commands[0]);
  printf("%zu: elements in command list\n", len);
  return 0;
}

char *dupstr(char *s) {
  char *r = malloc(strlen(s) + 1);
  strcpy(r, s);
  return r;
}

static char *command_generator(const char *text, int state) {
  static int index, len;
  char *name;

  if (!state) {
    index = 0;
    len = strlen(text);
  }

  while ((name = commands[index].name)) {
    index++;

    if (strncmp(name, text, len) == 0) {
      return (dupstr(name));
    }
  }
  return ((char *)NULL);
}

static char **fileman_completion(const char *text, int start, int end) {
  char **matches = NULL;

  if (start == 0) {
    matches = rl_completion_matches(text, command_generator);
  }
  return matches;
}

static void initialize_readline(char *progname) {
  rl_readline_name = progname;

  rl_attempted_completion_function = fileman_completion;
}

Command *find_command(char *name) {
  register int i;

  for (i = 0; commands[i].name; i++) {
    if (strcmp(name, commands[i].name) == 0) {
      return (&commands[i]);
    }
  }
  return ((Command *)NULL);
}

int execute_line(char *line) {
  register int i;
  Command *command;
  char *word;
  i = 0;
  while (line[i] && whitespace(line[i])) {
    i++;
  }
  word = line + i;

  while (line[i] && !whitespace(line[i])) {
    i++;
  }

  if (line[i]) {
    line[i++] = '\0';
  }

  command = find_command(word);

  if (!command) {
    fprintf(stderr, "%s: no such command\n", word);
    return -1;
  }

  while (whitespace(line[i])) {
    i++;
  }

  word = line + i;

  return ((*(command->func))(word));
}

int main(int argc, char *argv[]) {
  char *line;
  initialize_readline(argv[0]);

  while (!done) {

    line = readline(":> ");

    if (strlen(line)) {
      add_history(line);
      execute_line(line);
    }
    free(line);
  }
  return EXIT_SUCCESS;
}
