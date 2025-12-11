#include <stdio.h>
#include <stdlib.h>

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
    printf("The list is already empty.\n");
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
