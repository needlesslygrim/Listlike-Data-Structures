#include <stdint.h>
#include <stdio.h>

#include "list.h"
#include "node.h"

int main(void) {
	int32_t vals[5] = {0, 2, 3, 4, 5};
	struct list_t list = initialise_list(vals, 5);

	push(&list, 3);
	print_node(list.head);
	insert(&list, 1, 1);
	remove_node(&list, 1);
	printf("%d\n", pop(&list));
	print_list(&list);
	// print_node(get(&list, 0));
	print_list_reversed(&list);
	delete_list(&list);
}
