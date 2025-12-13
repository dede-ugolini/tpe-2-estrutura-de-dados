#include "colors.h"

#include <stdbool.h>
#include <stddef.h>
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

void menu(Node *head) {

  int option = 0;
  do {
    printf("============ Hello World ===============\n");
    printf("1 - pop (remover o último node da lista.)\n");
    printf("2 - push (adicionar um node ao final da lista.)\n");
    printf("3 - shift (remover primeiro node da lista.)\n");
    printf("4 - unShift (adicionar um node ao início da lista.)\n");
    printf("5 - inserir valor em determinada posição\n");
    printf("6 - excluir valor em determinada posição\n");
    printf("7 - printar lista de frente para trás\n");
    printf("8 - printar lista de trás para frente\n");
    printf("9 - ordenar a lista em ordem crescente\n");
    printf("10 - ordenar a lista em ordem decrescente\n");
    printf("0 - Sair");

    int data = 0;
    int position = 0;

    printf("\nEscolha uma opção.\n");
    scanf("%d", &option);

    switch (option) {
    case 1:
      pop(&head);
      break;
    case 2:
      printf("Digite o valor que o node vai armazenar: ");
      scanf("%d", &data);
      push(&head, data);
      break;
    case 3:
      shift(&head);
      break;
    case 4:
      printf("Digite o valor que o node vai armazenar: ");
      scanf("%d", &data);
      unShift(&head, data);
      break;
    case 5:
      printf("Digite o valor que o node vai armazenar: ");
      scanf("%d", &data);
      printf("Digite a posição do node.");
      scanf("%d", &position);
      insertAtPosition(&head, data, position);
      break;
    case 6:
      printf("Digite a posição do node: ");
      scanf("%d", &position);
      deleteAtPosition(&head, position);
      break;
    case 7:
      printListForward(head);
      break;
    case 8:
      printListReverse(head);
      break;
    case 9:
      bubbleSortCrescente(head);
      break;
    case 10:
      bubbleSortDecrescente(head);
      break;
    case 0:
      SUCESS("Encerrando...");
      break;
    default:
      fputs("Opção não reconhecida", stderr);
      break;
    }
  } while (option != 0);
}

int main(int argc, char *argv[]) {
  Node *head = NULL;
  menu(head);
  return EXIT_SUCCESS;
}
