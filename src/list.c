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
 * struct dl_list_t *list = dl_initialise_list(vals, 6);
 * ...
 * dl_delete_list(list);
 */
struct dl_list_t dl_initialise_list(int32_t *vals, size_t length) {
	struct dl_list_t list = {NULL, NULL, length };

	list.len = length;
	struct dl_node_t *head = initialise_dl_node((length > 0) ? vals[0] : 0, NULL, NULL);
	list.head = head;

	if (length == 0) {
		return list;
	}

	struct dl_node_t *previous_node = initialise_dl_node(vals[1], NULL, head);
	head->next = previous_node;

	for (size_t i = 2; i < length - 1; i++) {
		struct dl_node_t *node = initialise_dl_node(vals[i], NULL, previous_node);

		previous_node->next = node;
		previous_node = node;
	}

	struct dl_node_t *tail =
			initialise_dl_node(vals[length - 1], NULL, previous_node);
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
 * struct dl_list_t *list = dl_initialise_list(vals, 6);
 * ...
 * dl_delete_list(list);
 */
void dl_delete_list(struct dl_list_t *list) {
	struct dl_node_t *current_node = list->head;
	struct dl_node_t *next_node;
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
 * struct dl_node_t *node = list.dl_get(3);
 * node->val++;
 */
struct dl_node_t *dl_get(struct dl_list_t *list, size_t index) {
	if (index > list->len) {
		return NULL;
	}

	struct dl_node_t *current_node = list->head;

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
 * dl_insert(list, 3, 12);
 * dl_print_list(list);
 *
 * Returns:
 * - 0 if successful
 * - 1 if index given > len
 */
int dl_insert(struct dl_list_t *list, size_t index, int32_t val) {
	if (index > list->len) {
		return 1;
	}

	struct dl_node_t *new_node = initialise_dl_node(val, NULL, NULL);

	if (index == 0) {
		struct dl_node_t *old_head = list->head;
		list->head = new_node;
		new_node->next = old_head;
		old_head->previous = new_node;
		return 0;
	}

	struct dl_node_t *node = dl_get(list, index);
	struct dl_node_t *previous_node = node->previous;
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
 * dl_push(list, 12);
 * dl_print_list();
 */
void dl_push(struct dl_list_t *list, int32_t val) {
	struct dl_node_t *node = initialise_dl_node(val, NULL, list->tail);

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
 * printf("%d", dl_pop(list));
 * dl_print_list(list);
 */
int32_t dl_pop(struct dl_list_t *list) {
	struct dl_node_t *tail = list->tail;

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
 * printf("%d", dl_remove_node(list, 3);
 * dl_print_list(list);
 */
int32_t dl_remove_node(struct dl_list_t *list, size_t index) {
	if (index == list->len) {
		return dl_pop(list);
	}

	if (index == 0) {
		struct dl_node_t *head = dl_get(list, 0);
		list->head = head->next;
		list->head->previous = NULL;
		free(head);
	}

	struct dl_node_t *node = dl_get(list, index);
	int value = node->val;
	struct dl_node_t *previous_node = node->previous;
	struct dl_node_t *next_node = node->next;

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
int32_t dl_check_list_validity(struct dl_list_t *list) {
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
int32_t dl_print_list(struct dl_list_t *list) {
	int validity = dl_check_list_validity(list);
	if (validity) {
		return validity;
	}

	printf("(%d, ", list->head->val);
	struct dl_node_t *current_node = list->head->next;

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
int32_t dl_print_list_reversed(struct dl_list_t *list) {
	struct dl_node_t *current_node = list->tail;

	int32_t validity = dl_check_list_validity(list);
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
