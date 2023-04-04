//
// Created by erickth on 04/04/23.
//

#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "node.h"

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

struct node_t *get(struct list_t *list, unsigned long long index) {
	if (index > list->len) {
		// printf("Index > Len");
		return NULL;
	}

	struct node_t *current_node = list->head;
	// print_node(current_node);

	if (index == 0) {
		return current_node;
		// printf("Index is 0, returning head");
	}
	// index--;

	for (int i = 0; i < index; i++) {
		current_node = current_node->next;
		// printf("Current loop iteration: %d, \t", i);
		// print_node(current_node);
	}

	return current_node;
}

void push(int val, struct list_t *list) {
  struct node_t *node = initialise_node(val, NULL, list->tail);

  list->tail->next = node;
  list->tail = node;
  list->len++;
}
int pop(struct list_t *list) {
  struct node_t *tail = list->tail;

  int val = tail->val;
  list->len--;
  tail->previous->next = NULL;
  free(tail);

  return val;
}

void print_list(struct list_t *list) {
  if (list == NULL) {
    printf("List is empty");
    return;
  }

  struct node_t *current_node = list->head;

  while (current_node->next != NULL) {
    printf("%d, ", current_node->val);
    current_node = current_node->next;
  }

  printf("%d \n", current_node->val);
}
void print_list_reverse(struct list_t *list) {
  struct node_t *current_node = list->tail;

  while (current_node->previous != NULL) {
   printf("%d, ", current_node->val);
    current_node = current_node->previous; 
  }

  printf("%d\n", current_node->val);
}