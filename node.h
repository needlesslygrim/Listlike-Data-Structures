//
// Created by erickth on 04/04/23.
//

#ifndef LIST_NODE_H
#define LIST_NODE_H

struct node_t {
	int val;
	struct node_t *next;
	struct node_t *previous;
};

struct node_t *initialise_node(int val, struct node_t *next,
							   struct node_t *previous);

void print_node(struct node_t *node);

#endif //LIST_NODE_H
