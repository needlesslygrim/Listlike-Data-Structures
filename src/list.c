//
// Created by erickth on 04/04/23.
//

#include "list.h"

#include <stdio.h>
#include <stdlib.h>

#include "node.h"

struct list_t *initialise_list(int *vals, unsigned long long length) {
	struct list_t *list = malloc(sizeof(struct list_t));
	if (list == NULL) {
		fprintf(stderr, "Could not initialise list\n");
		exit(1);
	}

	list->len = length;
	struct node_t *head = initialise_node(vals[0], NULL, NULL);
	list->head = head;

	if (length == 0) {
		return list;
	}


	struct node_t *previous = initialise_node(vals[1], NULL, head);
	head->next = previous;

	for (unsigned long long i = 2; i < length - 1; i++) {
		struct node_t *node = initialise_node(vals[i], NULL, previous);

		previous->next = node;
		previous = node;
	}

	struct node_t *tail = initialise_node(vals[length - 1], NULL, previous);
	previous->next = tail;
	list->tail = tail;

	return list;
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
	free(list);
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

	for (unsigned long long i = 0; i < index; i++) {
		current_node = current_node->next;
		// printf("Current loop iteration: %d, \t", i);
		// print_node(current_node);
	}

	return current_node;
}

int insert(struct list_t *list, unsigned long long index, int val) {
	if (index > list->len) {
		return 1;
	}

	struct node_t *new_node = initialise_node(val, NULL, NULL);

	if (index == 0) {
		struct node_t *old_head = list->head;
		list->head = new_node;
		new_node->next = old_head;
		old_head->previous = new_node;
		return 0;
	}

	struct node_t *node = get(list, index);
	struct node_t *prev = node->previous;
	prev->next = new_node;
	new_node->previous = prev;
	new_node->next = node;
	node->previous = new_node;

	return 0;
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

	if (list->head == list->tail) {
		free(list->head);
		list->head = NULL;
		list->tail = NULL;
		return val;
	}

	list->len--;

	tail->previous->next = NULL;
	list->tail = tail->previous;

	free(tail);

	return val;
}

int remove_node(struct list_t *list, unsigned long long index) {
	if (index == list->len) { return pop(list); }


	if (index == 0) {
		struct node_t *head = get(list, 0);
		list->head = head->next;
		list->head->previous = NULL;
		free(head);
	}

	struct node_t *node = get(list, index);
	int value = node->val;
	struct node_t *prev = node->previous;
	struct node_t *next = node->next;

	prev->next = next;
	next->previous = prev;
	list->len--;
	free(node);

	return value;
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
	if (validity) {
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
	if (validity) {
		return validity;
	}

	while (current_node->previous != NULL) {
		printf("%d, ", current_node->val);
		current_node = current_node->previous;
	}

	printf("%d\n", current_node->val);
	return 0;
}
