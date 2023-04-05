#ifndef NODE_H
#define NODE_H

#include <stdint.h>

struct node_t {
	int32_t val;
	struct node_t *next;
	struct node_t *previous;
};

struct node_t *initialise_node(int32_t val, struct node_t *next,
							   struct node_t *previous);

void print_node(struct node_t *node);

#endif // NODE_H
