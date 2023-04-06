#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "node.h"

/*
 * Initialise a node, will exit the program if memory cannot be allocated.
 * Takes a value for the next and previous node, and a value to set. Nodes
 * initialised *must* be freed.
 *
 * Example use:
 * struct node_t *node = initialise_node(3, NULL, NULL);
 * struct node_t *next_node = initialise_node(4, NULL, node);
 */
struct node_t *initialise_node(int32_t val, struct node_t *next,
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

/*
 * Prints out a node with the format (the next and previous nodes will just be
 * printed as pointers:
 *
 * Node {
 * 	val: node->val,
 * 	next: node->next,
 * 	previous: node->previous,
 * }
 */
void print_node(struct node_t *node) {
	printf("Node {\n  val: %d,\n  next: %ld,\n  previous: %ld }\n", node->val,
		   (size_t) node->next, (size_t) node->previous);
}
