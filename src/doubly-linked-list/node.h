#ifndef DOUBLY_LINKED_NODE_H
#define DOUBLY_LINKED_NODE_H

#include <stdint.h>

struct dl_node_t {
	int32_t val;
	struct dl_node_t *next;
	struct dl_node_t *previous;
};

struct dl_node_t *initialise_dl_node(int32_t val, struct dl_node_t *next,
									 struct dl_node_t *previous);

void print_dl_node(struct dl_node_t *node);

#endif // DOUBLY_LINKED_NODE_H
