#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <stddef.h>
#include <stdint.h>

#include "../defs.h"

struct dl_list_t {
	struct dl_node_t *head;
	struct dl_node_t *tail;
	usize len;
};

struct dl_list_t dl_initialise_list(i32 *vals, usize length);
void dl_delete_list(struct dl_list_t *list);

struct dl_node_t *dl_get(struct dl_list_t *list, usize index);

void dl_push(struct dl_list_t *list, i32 val);
int dl_insert(struct dl_list_t *list, usize index, i32 val);

int dl_pop(struct dl_list_t *list);
int dl_remove_node(struct dl_list_t *list, usize index);

int dl_check_list_validity(struct dl_list_t *list);

int dl_print_list(struct dl_list_t *list);
int dl_print_list_reversed(struct dl_list_t *list);

#endif // DOUBLE_LINKED_LIST_H
