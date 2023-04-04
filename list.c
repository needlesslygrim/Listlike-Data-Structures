//
// Created by erickth on 04/04/23.
//

#include "list.h"

#include <stdio.h>
#include <stdlib.h>

#include "node.h"

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

/* Checks whether a given list is valid or not.
 *
 * Returns:
 * 0 if valid
 * 1 if the pointer == NULL
 * 2 if the head == NULL;
 * 3 if the head == NULL;
 */

int check_list_validity(struct list_t *list) {
	if (list == NULL) {
		return 1;
	} else if (list->head == NULL) {
		return 2;
	} else if (list->tail == NULL) {
		return 3;
	}

	return 0;
}

int print_list(struct list_t *list) {
	int validity = check_list_validity(list);
	if (!validity) {
		return validity;
	}

	struct node_t *current_node = list->head;

	while (current_node->next != NULL) {
		printf("%d, ", current_node->val);
		current_node = current_node->next;
	}

	printf("%d \n", current_node->val);

	return 0;
}

int print_list_reverse(struct list_t *list) {
	struct node_t *current_node = list->tail;

	int validity = check_list_validity(list);
	if (!validity) {
		return validity;
	}

	while (current_node->previous != NULL) {
		printf("%d, ", current_node->val);
		current_node = current_node->previous;
	}

	printf("%d\n", current_node->val);
	return 0;
}