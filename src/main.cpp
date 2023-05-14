#include "list.h"
#include <cstdint>

using namespace dl_list;

auto CreateList() {
	int32_t vals[5] = {1, 2, 3, 4, 5};
	auto list = List(vals, 5);
	list.push(6);
	list.insert(0, 0);
	list.insert(3, 3);
	list.insert(list.len() - 1, 7);
	list.insert(list.len(), 8);
	for (size_t i = 0; i < list.len(); i++) {
		list.operator[](i)->print();
	}
	list.print();

	return list;
}

int main() {

	CreateList();
	//	delete list;
	//	for (auto &list : lists) {
	//		list = CreateList();
	//	}
	//	for (auto &list : lists) {
	//		delete list;
	//	}

	//	list->get(0)->print();
	//	list->get(1)->print();
	//	list->get(4)->print();
	//	list->get(list->len() - 1)->print();
	//
	//	list->insert(0, 1);
	//	//	printf("%d", 3.2);
	//	list->print();
}
