//
// Created by erickth on 04/04/23.
//

#include "node.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

void print_node(struct node_t *node) {
	printf("Node {\n  val: %d,\n  next: %ld,\n  previous: %ld }\n", node->val,
		   (long)node->next, (long)node->previous);
}
