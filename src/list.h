#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdint.h>

struct list_t {
	struct node_t *head;
	struct node_t *tail;
	size_t len;
};

struct list_t *initialise_list(int32_t *vals, size_t length);
void delete_list(struct list_t *list);

struct node_t *get(struct list_t *list, size_t index);

void push(struct list_t *list, int32_t val);
int insert(struct list_t *list, size_t index, int32_t val);

int pop(struct list_t *list);
int remove_node(struct list_t *list, size_t index);

int check_list_validity(struct list_t *list);

int print_list(struct list_t *list);
int print_list_reversed(struct list_t *list);

#endif // LIST_H
