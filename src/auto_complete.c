#include <stdbool.h>
#include <stdio.h>

#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>

#include "auto_complete.h"

static int usage(char *);
static int quit(char *);
static int add(char *);
static int size(char *);

Command commands[] = {
    {"help", usage, "Display this text"},
    {"quit", quit, "Exit program"},
    {"add", add, "Add to 5"},
    {"size", size, "Size of command list"},
};

static bool done = false;
static int elements_list =
    (sizeof(commands) /
     sizeof(commands[0])); // Quantidade de elementos na lista de comandos

static int usage(char *arg) {
  puts("Usage\n");
  for (int i = 0; i < elements_list; i++) {
    printf("%s\t%s\n", commands[i].name, commands[i].doc);
  }
  return 0;
};

static int quit(char *arg) {
  puts("Bye");
  done = true;
  return 0;
}

static int add(char *arg) {
  int i = atoi(arg);
  i += 5;
  printf("%d\n", i);
  return 0;
}

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

char *command_generator(const char *text, int state) {
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

char **fileman_completion(const char *text, int start, int end) {
  char **matches = NULL;

  if (start == 0) {
    matches = rl_completion_matches(text, command_generator);
  }
  return matches;
}

void initialize_readline(char *progname) {
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
