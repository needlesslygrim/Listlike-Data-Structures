#include <cstdint>

#include "list.h"


int main() {
	int32_t vals[5] = {0, 1, 2, 3, 4};
	auto list = new List(vals, 5);
	list->get(0)->print();
	list->get(1)->print();
	list->get(4)->print();
	list->get(list->len() - 1)->print();

	list->insert(0, 1);
	//	printf("%d", 3.2);
	list->print();
	delete list;
}
