#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "node.h"

/*
 * Initialise a new list with values as given in the array `vals`, with length
 * as given by the value `length`. Any list created using this function *must*
 * be deinitialised using the `delete_list` function.
 *
 * Example use:
 * int32_t vals[6] = {1, 2, 3, 4, 5, 6};
 * struct list_t *list = initialise_list(vals, 6);
 * ...
 * delete_list(list);
 */
struct list_t initialise_list(int32_t *vals, size_t length) {
	struct list_t list = { NULL, NULL, length };

	list.len = length;
	struct node_t *head = initialise_node((length > 0) ? vals[0] : 0, NULL, NULL);
	list.head = head;

	if (length == 0) {
		return list;
	}

	struct node_t *previous_node = initialise_node(vals[1], NULL, head);
	head->next = previous_node;

	for (size_t i = 2; i < length - 1; i++) {
		struct node_t *node = initialise_node(vals[i], NULL, previous_node);

		previous_node->next = node;
		previous_node = node;
	}

	struct node_t *tail =
		initialise_node(vals[length - 1], NULL, previous_node);
	previous_node->next = tail;
	list.tail = tail;

	return list;
}

/*
 * Deinitialise a list, first `free`ing each node, and then the list structure
 * itself. List should not be used after.
 *
 * Example use:
 * int32_t vals[6] = {1, 2, 3, 4, 5, 6};
 * struct list_t *list = initialise_list(vals, 6);
 * ...
 * delete_list(list);
 */
void delete_list(struct list_t *list) {
	struct node_t *current_node = list->head;
	struct node_t *next_node;
	while ((next_node = current_node->next) != NULL) {
		next_node->previous = NULL;
		free(current_node);
		current_node = next_node;
	}

	free(current_node);
	list->head = NULL;
	list->tail = NULL;
	list->len = 0;
//	free(list);
}

/*
 * Get a node at a certain index, a pointer to the node will be returned. If
 * the index given is longer than the length of the list, NULL will be returned.
 *
 * Example use:
 * struct node_t *node = list.get(3);
 * node->val++;
 */
struct node_t *get(struct list_t *list, size_t index) {
	if (index > list->len) {
		return NULL;
	}

	struct node_t *current_node = list->head;

	if (index == 0) {
		return current_node;
	}

	for (size_t i = 0; i < index; i++) {
		current_node = current_node->next;
	}

	return current_node;
}

/*
 * Insert a value at a given index, a new node will be created to store the
 * value, which means allocation is required.
 *
 * Example use:
 * print_list(list);
 * insert(list, 3, 12);
 * print_list(list);
 *
 * Returns:
 * - 0 if successful
 * - 1 if index given > len
 */
int insert(struct list_t *list, size_t index, int32_t val) {
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
	struct node_t *previous_node = node->previous;
	previous_node->next = new_node;
	new_node->previous = previous_node;
	new_node->next = node;
	node->previous = new_node;

	return 0;
}

/*
 * Push a new val to the end of the list, a new node will be created to store
 * the value, which means allocation is required.
 *
 * Example use:
 * print_list(list);
 * push(list, 12);
 * print_list();
 */
void push(struct list_t *list, int32_t val) {
	struct node_t *node = initialise_node(val, NULL, list->tail);

	list->tail->next = node;
	list->tail = node;
	list->len++;
}

/*
 * Pop the last node off the list, its value will be returned. Memory required
 * for tail of list shall be `free`d.
 *
 * Example use:
 * print_list(list)
 * printf("%d", pop(list));
 * print_list(list);
 */
int32_t pop(struct list_t *list) {
	struct node_t *tail = list->tail;

	int32_t val = tail->val;

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

/*
 * Pop the node at the given index from the list, its value will be returned.
 * Memory required for tail of list shall be `free`d.
 *
 * Example use:
 * print_list(list)
 * printf("%d", remove_node(list, 3);
 * print_list(list);
 */
int32_t remove_node(struct list_t *list, size_t index) {
	if (index == list->len) {
		return pop(list);
	}

	if (index == 0) {
		struct node_t *head = get(list, 0);
		list->head = head->next;
		list->head->previous = NULL;
		free(head);
	}

	struct node_t *node = get(list, index);
	int value = node->val;
	struct node_t *previous_node = node->previous;
	struct node_t *next_node = node->next;

	previous_node->next = next_node;
	next_node->previous = previous_node;
	list->len--;
	free(node);

	return value;
}

/*
 * Checks whether a given list is valid, based on whether the head and tail are
 * not NULL, or whether the pointer itself is NULL. It will not check the
 * validity of the chain.
 *
 * Returns:
 * 0 if valid
 * 1 if the pointer == NULL
 * 2 if the head == NULL;
 * 3 if the head == NULL;
 */
int32_t check_list_validity(struct list_t *list) {
	if (list == NULL) {
		return 1;
	} else if (list->head == NULL) {
		return 2;
	} else if (list->tail == NULL) {
		return 3;
	}

	return 0;
}

/*
 * Print out a list from head->tail, returns the value that is returned by
 * check_validity when called with the list passed.
 */
int32_t print_list(struct list_t *list) {
	int validity = check_list_validity(list);
	if (validity) {
		return validity;
	}

	printf("(%d, ", list->head->val);
	struct node_t *current_node = list->head->next;

	while (current_node->next != NULL) {
		printf("%d, ", current_node->val);
		current_node = current_node->next;
	}

	printf("%d)\n", current_node->val);

	return 0;
}

/*
 * Prints out a list from tail->head, returns the value that is returned by
 * check_validity when called with the list passed.
 */
int32_t print_list_reversed(struct list_t *list) {
	struct node_t *current_node = list->tail;

	int32_t validity = check_list_validity(list);
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
