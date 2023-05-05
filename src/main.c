#include <stdint.h>
#include <stdio.h>

#include "list.h"
#include "node.h"

int main() {
	int32_t vals[6] = {0, 1, 2, 3, 4, 5};
	struct dl_list_t list = dl_initialise_list(vals, 6);

	dl_print_list(&list);
	print_dl_node(dl_get(&list, 0));
	print_dl_node(dl_get(&list, 1));
	print_dl_node(dl_get(&list, list.len - 1));
	print_dl_node(dl_get(&list, 2));

	dl_push(&list, 5);
	dl_print_list(&list);
	print_dl_node(dl_get(&list, list.len - 1));
	dl_insert(&list, 0, -1);
	dl_print_list(&list);
	print_dl_node(list.head);
	print_dl_node(list.head->next);
	print_dl_node(dl_get(&list, 0));
	print_dl_node(dl_get(&list, 1));


	dl_delete_list(&list);
}
