#include <cstdint>
#include <vector>

#include "list.h"

using namespace dl_list;

void bubblesort(List &list) {
	for (size_t i = 0; i < list.len() - 1; i++) {
		for (size_t j = 0; j < list.len() - 1; j++) {
			if (list[j] > list[j + 1]) {
				auto temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}

auto CreateList() {
	int32_t vals[10] = {1,	  2,	3,	  4,	543, 215321, 4321, 4321, 43, 91};
	auto list = List(vals, 10);
	bubblesort(list);
	list.print();
		list.push(6);
		list.insert(0, 0);
		list.insert(3, 3);
		list.insert(list.len() - 1, 7);
		list.insert(list.len(), 8);
		for (int32_t i = 0; i < list.len(); i++) {
			list.remove(i);
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
