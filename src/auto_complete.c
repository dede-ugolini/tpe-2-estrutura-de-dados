#include "auto_complete.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

Command *commands;

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

void initialize_readline(char *progname, Command *list) {
  rl_readline_name = progname;

  rl_attempted_completion_function = fileman_completion;

  commands = list;
}

static Command *find_command(char *name) {
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
