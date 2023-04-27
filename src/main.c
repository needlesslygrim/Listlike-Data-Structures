#include <stdint.h>
#include <stdio.h>

#include "list.h"
#include "node.h"

int main() {
	int32_t vals[5] = {0, 1, 2, 3, 4};
	struct list_t list = initialise_list(vals, 5);
;
	print_list(&list);
	print_node(get(&list, 0));
	print_node(get(&list, 1));
	print_node(get(&list, list.len - 1));
	print_node(get(&list, 2));

	push(&list, 5);
	print_list(&list);
	print_node(get(&list, list.len - 1));
	insert(&list, 0, -1);
	print_list(&list);
	print_node(list.head);
	print_node(list.head->next);
	print_node(get(&list, 0));
	print_node(get(&list, 1));

	delete_list(&list);
}
