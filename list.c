//
// Created by erickth on 04/04/23.
//

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void push_val(int val, struct list_t *list) {
  struct node_t *node = initialise_node(val, NULL, list->tail);
  list->tail = node;
}

void delete_list(struct list_t *list) {
  struct node_t *current_node = list->head;
  struct node_t *next_node;
  while ((next_node = current_node->next) != NULL) {
    next_node->previous = NULL;
    free(current_node);
    current_node = next_node;
  }

  free(current_node);
}

int pop_previous_node(struct node_t *list) {
  struct node_t *prevprev = list->previous->previous;
  struct node_t *prev = list->previous;

  free(prev);
  list->previous = prevprev;
  prevprev->next = list;

  return 0;
}

int pop_next_node(struct node_t *list) {
  free(list->next);

  return 0;
}

void print_from_head(struct node_t *list) {
  if (list == NULL) {
    printf("List is empty");
    return;
  }
  struct node_t *current_node = list;

  while (current_node->next != NULL) {
    printf("%d, ", current_node->val);
    current_node = current_node->next;
  }

  printf("%d \n", current_node->val);
}
struct node_t *initialise_node(int val, struct node_t *next,
                               struct node_t *previous) {
  struct node_t *node = malloc(sizeof(struct node_t));
  if (node == NULL) {
    fprintf(stderr,
            "Could not allocate memory to initialise a node with value: %d",
            val);
    exit(1);
  }
  node->val = val;
  node->next = next;
  node->previous = previous;
  return node;
}

struct node_t *get(struct list_t *list, unsigned long long index) {
  if (index > list->len) {
    return NULL;
  }

  struct node_t *current_node = list->head;
  if (index == 0) {
    return current_node;
  }

  for (int i = 0; i < --index; i++) {
    current_node = current_node->next;
  }

  return current_node;
}

// struct list_t *initialise_list(int *vals, unsigned long long length) {
//   struct list_t *list = malloc(sizeof(struct list_t));
//   if (length == 0) {
//     if (list == NULL) {
//       fprintf(stderr, "Could not initialise list");
//       exit(1);
//     }

//     return list;
//   }

//   struct node_t *head = initialise_node(vals[0], NULL, NULL);

//   for (int i = 1; i < length - 1; i++) {
//     struct node_t *node = initialise_node(vals[i], )
//   }
// }
