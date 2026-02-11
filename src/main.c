#include "auto_complete.h"
#include "colors.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PROG_NAME "tpe"

typedef struct Node {
  int data;
  struct Node *next;
  struct Node *prev;
} Node;

Node *createNode(int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = NULL;
  newNode->prev = NULL;
  return newNode;
}

// Função que adiciona um novo node ao final da lista
void push(Node **head, int data) {
  Node *newNode = createNode(data);

  if (*head == NULL) {
    *head = newNode;
    return;
  }

  Node *temp = *head;
  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = newNode;
  newNode->prev = temp;
}

// Função que remove o último node da lista
void pop(Node **head) {
  if (*head == NULL) {
    ERROR("Lista está vazia");
    return;
  }

  Node *temp = *head;
  if (temp->next == NULL) {
    *head = NULL;
    free(temp);
    return;
  }
  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->prev->next = NULL;
  free(temp);
}

void printListForward(Node *head) {
  Node *temp = head;
  printf("Forward List: ");
  printf("NULL->");
  while (temp != NULL) {
    printf("%d->", temp->data);
    temp = temp->next;
    if (temp == NULL) {
      printf("NULL");
    }
  }
  printf("\n");
}

void printListReverse(Node *head) {
  Node *temp = head;
  if (temp == NULL) {
    ERROR("Lista está vazia.");
    return;
  }
  // Move to the end of the list
  while (temp->next != NULL) {
    temp = temp->next;
  }
  // Traverse backwards
  printf("Reverse List: ");
  printf("NULL<-");
  while (temp != NULL) {
    printf("%d<-", temp->data);
    temp = temp->prev;
    if (temp == NULL) {
      printf("NULL");
    }
  }
  printf("\n");
}

// Função para inserir um elemento no inicio da lista
void unShift(Node **head, int data) {

  Node *newNode = createNode(data);

  if (*head == NULL) {
    *head = newNode;
    return;
  }
  newNode->next = *head;
  (*head)->prev = newNode;
  *head = newNode;
}

// Função para remover um elemento do inicio da lista
void shift(Node **head) {
  if (*head == NULL) {
    ERROR("Lista está vazia.");
    return;
  }
  Node *temp = *head;
  *head = (*head)->next;
  if (*head != NULL) {
    (*head)->prev = NULL;
  }
  free(temp);
}

void insertAtPosition(Node **head, int data, int position) {
  if (position < 1) {
    ERROR("Posição precisa ser maior que zero.");
    return;
  }

  if (position == 1) {
    unShift(head, data);
    return;
  }
  Node *newNode = createNode(data);
  Node *temp = *head;
  for (int i = 1; temp != NULL && i < position - 1; i++) {
    temp = temp->next;
  }
  if (temp == NULL) {
    ERROR("A posição é maior que o número total de elementos");
    return;
  }
  newNode->next = temp->next;
  newNode->prev = temp;
  if (temp->next != NULL) {
    temp->next->prev = newNode;
  }
  temp->next = newNode;
}

void deleteAtPosition(Node **head, int position) {
  if (*head == NULL) {
    ERROR("Lista está vazia.");
    return;
  }
  Node *temp = *head;
  if (position == 1) {
    shift(head);
    return;
  }
  for (int i = 1; temp != NULL && i < position; i++) {
    temp = temp->next;
  }
  if (temp == NULL) {
    ERROR("Posição é maior que o número de elementos da lista.");
    return;
  }
  if (temp->next != NULL) {
    temp->next->prev = temp->prev;
  }
  if (temp->prev != NULL) {
    temp->prev->next = temp->next;
  }
  free(temp);
}

Node *bubbleSortCrescente(Node *head) {
  if (head == NULL) {
    return head;
  }

  bool swaped;
  Node *last = NULL;
  Node *current;

  do {
    swaped = false;
    current = head;
    while (current->next != last) {
      if (current->data > current->next->data) {

        int tmp = current->data;
        current->data = current->next->data;
        current->next->data = tmp;
        swaped = true;
      }
      current = current->next;
    }
  } while (swaped);

  return head;
}

Node *bubbleSortDecrescente(Node *head) {
  if (head == NULL) {
    return head;
  }

  bool swaped;
  Node *last = NULL;
  Node *current;

  do {
    swaped = false;
    current = head;
    while (current->next != last) {
      if (current->data < current->next->data) {

        int tmp = current->data;
        current->data = current->next->data;
        current->next->data = tmp;
        swaped = true;
      }
      current = current->next;
    }
  } while (swaped);

  return head;
}

void freeAll(Node *head) {
  while (head != NULL) {
    Node *tmp = head->next;
    free(head);
    head = tmp;
  }
}

void fill(Node *head) {
  srand(time(NULL));
  Node *newNode = createNode(rand() % 100);
  if (head == NULL) {
    head = newNode;
  }
  for (int i = 0; i < 30; i++) {
    push(&head, rand() % 100);
  }
}

Node *head = NULL;

static int help(char *arg);
static int quit(char *arg);
static int cm_print(char *arg);
static int cm_push(char *arg);

Command command_list[] = {
    {"help", help, "See this message"},
    {"quit", quit, "Fechar o programa"},
    {"exit", quit, "Fechar o programa"},
    {"pop"},
    {"push", cm_push, "Adicionar node ao final da lista"},
    {"shift"},
    {"unshift"},
    {"fill"},
    {"delete"},
    {"print", cm_print, "Printar lista"},
    {"sort"},
};

static int cm_push(char *arg) {
  if (!strlen(arg)) {
    puts("Falta argumento");
    return -1;
  } else {
    int data = atoi(arg);
    push(&head, data);
  }
  return 0;
}

static int cm_print(char *arg) {
  printListForward(head);
  return 0;
}

static int help(char *arg) {
  printf("Usage of program\n");
  int size = sizeof(command_list) / sizeof(command_list[0]);
  for (int i = 0; i < size; i++) {
    printf("%s\t%s\t\n", command_list[i].name, command_list[i].doc);
  }
  return 0;
}

static int quit(char *arg) {
  puts("Bye");
  // TODO: Adicionar suporte a função freall() para desalocar memória do node
  exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {

  initialize_readline(argv[0], command_list);

  char *line;

  puts("Digite help");

  while (true) {
    line = readline(":> ");

    if (strlen(line)) {
      add_history(line);
    }

    execute_line(line);
    free(line);
  }

  return EXIT_SUCCESS;
}
