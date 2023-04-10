#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "list.h"
#include "node.h"

List::List(int32_t *vals, size_t length) {
	this->tail = nullptr;
	this->len = length;

	this->head = new Node((length > 0) ? vals[0] : 0, nullptr, nullptr);

	if (length == 0) {
		return;
	}

	auto previous_node = new Node(vals[1], nullptr, head);
	this->head->setNext(previous_node);

	for (size_t i = 2; i < length - 1; i++) {
		auto node = new Node(vals[i], nullptr, previous_node);

		previous_node->setNext(node);
		previous_node = node;
	}

	auto tail = new Node(vals[length -1 ], nullptr, previous_node);
	previous_node->setNext(tail);
	this->tail = tail;
}

List::~List() {
	auto current_node = this->head;
	Node *next_node;
	while ((next_node = current_node->getNext()) != nullptr) {
		next_node->setPrevious(nullptr);
		delete current_node;
		current_node = next_node;
	}

	delete current_node;
	this->head = nullptr;
	this->tail = nullptr;
	this->len = 0;
}

int List::print() {
	printf("(%d, ", this->head->getVal());
	auto current_node = this->head->getNext() ;

	while (current_node->getNext() != nullptr) {
		printf("%d, ", current_node->getVal());
		current_node = current_node->getNext();
	}

	printf("%d)\n", current_node->getVal());

	return 0;
}
