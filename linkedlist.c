/* Singly linked list
 *
 */

#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list *list_new() {
  struct list *new_list = (struct list *)malloc(sizeof(struct list));
  new_list->head = NULL;
  new_list->tail = NULL;
  return new_list;
}

struct node *node_new(const char *value) {
  struct node *new_node = (struct node *)malloc(sizeof(struct node));
  // First we need to malloc space for the string;
  new_node->value = (char *)malloc(sizeof(char) * strlen(value));
  new_node->next = NULL;
  strcpy(new_node->value, value);
  return new_node;
}

void node_free(struct node *node) {
  free(node->value);
  free(node);
}

void list_free(struct list *list) {
  struct node *n = list->head;
  struct node *next;
  while (n != NULL) {
    next = n->next;
    node_free(n);
    n = next;
  }
  free(list);
}

void list_append(struct list *list, const char *value) {
  struct node *prev_tail = list->tail;
  struct node *new_node = node_new(value);
  if (prev_tail == NULL) {
    list->tail = new_node;
    list->head = list->tail;
  } else {
    prev_tail->next = new_node;
    list->tail = new_node;
  }
  return;
}

/* Can return null
 */
struct node *list_find(struct list *list, const char *value) {
  struct node *n = list->head;
  while (n != NULL) {
    if (strcmp(n->value, value) == 0) {
      return n;
    }
    n = n->next;
  }
  return n; // NULL
}

void list_print(struct list *list) {
  printf("----\n");
  if (list->head != NULL) {
    printf("HEAD: %p", list->head);
  } else {
    printf("HEAD: NULL");
  }
  if (list->tail != NULL) {
    printf("HEAD: %p", list->tail);
  } else {
    printf("HEAD: NULL");
  }
  struct node *node = list->head;
  while (node != NULL) {
    node_print(node);
    node = node->next;
  }
  printf("----\n");
}

void node_print(struct node *node) {
  printf("----\n");
  if (node->value != NULL) {
    printf("value: %s\n", node->value);
  } else {
    printf("value: NULL\n");
  }
  if (node->next != NULL) {
    printf("next: %p\n", node->next);
  } else {
    printf("next: NULL\n");
  }
  printf("----\n");
}
