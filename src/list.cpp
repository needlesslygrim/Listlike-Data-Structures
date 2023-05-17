#include <cstdint>
#include <cstdio>
#include <cstring>
#include <exception>
#include <stdexcept>

#include "exceptions.h"
#include "list.h"
#include "node.h"

namespace dl_list {
List::List() : m_head(nullptr), m_tail(nullptr), m_len(0){};
List::List(int32_t val) : m_len(1) {
	auto node = new Node(val);
	this->m_head = node;
	this->m_tail = node;
}

List::List(int32_t *vals, size_t length) : m_len(length) {
	if (length == 0) {
		throw std::invalid_argument("Invalid length");
	}

	auto head = new Node(vals[0]);
	this->m_head = head;

	if (length == 1) {
		this->m_tail = head;
		return;
	}

	auto previous_node = new Node(vals[1], nullptr, head);
	head->m_next = previous_node;

	for (size_t i = 2; i < length - 1; i++) {
		auto node = new Node(vals[i], nullptr, previous_node);

		previous_node->m_next = node;
		previous_node = node;
	}

	auto tail = new Node(vals[length - 1], nullptr, previous_node);
	previous_node->m_next = tail;
	this->m_tail = tail;
}

List::~List() {
	if (this->m_len == 0) {
		return;
	}
	if (this->m_len == 1) {
		delete this->m_head;
		return;
	}
	auto current_node = this->m_head;

	auto next_node = current_node->m_next;

	while (next_node != nullptr) {
		delete current_node;
		current_node = next_node;
		next_node = current_node->m_next;
	}

	delete current_node;
}

int32_t &List::operator[](size_t index) const {
	if (index >= this->m_len) {
		throw std::out_of_range("Index out of range");
	}
	if (index == 0) {
		return this->m_head->m_val;
	}

	auto current_node = this->m_head;

	for (size_t i = 0; i < index; i++) {
		current_node = current_node->getNext();
	}

	return current_node->m_val;
}

Node *List::get(size_t index) const {
	if (index >= this->m_len) {
		throw std::out_of_range("Index out of range");
	}
	if (index == 0) {
		return this->m_head;
	}

	auto current_node = this->m_head;

	for (size_t i = 0; i < index; i++) {
		current_node = current_node->getNext();
	}

	return current_node;
}

Node *List::getHead() const { return this->m_head; }

Node *List::getTail() const { return this->m_tail; }

size_t List::len() const { return this->m_len; }

void List::push(int32_t val) {
	auto new_node = new Node(val, nullptr, this->m_tail);

	this->m_tail->m_next = new_node;
	this->m_tail = new_node;
	this->m_len++;
}

void List::insert(size_t index, int32_t val) {
	if (index > this->m_len) {
		throw std::out_of_range(
			"Index out of range: greater than length of list");
	}

	auto new_node = new Node(val);

	if (index == 0) {
		auto old_head = this->m_head;
		old_head->m_previous = new_node;
		new_node->m_next = old_head;
		this->m_head = new_node;
		this->m_len++;
		return;
	} else if (index == this->m_len) {
		this->push(val);
		return;
	}

	auto old_node_at_index = this->get(index);
	auto previous_node = old_node_at_index->m_previous;

	previous_node->m_next = new_node;
	new_node->m_previous = previous_node;
	old_node_at_index->m_previous = new_node;
	new_node->m_next = old_node_at_index;
	this->m_len++;
}

int32_t List::pop() {
	if (this->m_len == 0) {
		throw empty_list_exception("Cannot pop value from empty list");
	}

	auto val = this->m_tail->m_val;

	if (this->m_len == 1) {
		delete this->m_head;
		this->m_head = nullptr;
		this->m_tail = nullptr;
		this->m_len--;
		return val;
	}

	auto old_tail = this->m_tail;
	old_tail->m_previous->m_next = nullptr;
	this->m_tail = old_tail->m_previous;
	this->m_len--;

	delete old_tail;

	return val;
}

int List::remove(size_t index) {
	if (index > this->m_len) {
		throw std::out_of_range(
			"Cannot remove node at index greater than length of list");
	}
	if (this->m_len == 0) {
		throw empty_list_exception("Cannot remove value from empty list");
	}
	if (index == this->m_len) {
		return this->pop();
	}

	if (index == 0) {
		auto head = this->m_head;
		auto value = head->m_val;

		this->m_head = head->m_next;
		this->m_len--;
		delete head;

		return value;
	}

	auto node = this->get(index);
	auto value = node->m_val;
	auto previous_node = node->getPrevious();
	auto next_node = node->getNext();

	previous_node->m_next = next_node;
	next_node->m_previous = previous_node;
	this->m_len--;
	delete node;

	return value;
}

/*
// Come back to later, not important at the moment
//void List::toString(char* buffer, size_t size) {
//	if (buffer == nullptr || size < 1) {
//		throw std::invalid_argument("Buffer invalid or size < 1");
//	}
//	if (this->m_len == 0) {
//		buffer = "()";
//		return;
//	}
//	if (this->m_len == 1) {
//		snprintf(buffer, size, "(%d)", this->m_head->m_val);
//		return;
//	}
//	char *temp[size];
//	snprintf("(%d, ", this->m_head->m_val);
//	auto current_node = this->m_head->getNext();
//
//	while (current_node->getNext() != nullptr) {
//		printf("%d, ", current_node->m_val);
//		current_node = current_node->getNext();
//	}
//
//	printf("%d)\n", current_node->m_val);
//
//	return 0;
//}
*/

int List::print() const {
	if (this->m_len == 0) {
		printf("()");
		return 0;
	}
	if (this->m_len == 1) {
		printf("(%d)", this->m_head->m_val);
		return 0;
	}
	printf("(%d, ", this->m_head->m_val);
	auto current_node = this->m_head->getNext();

	while (current_node->getNext() != nullptr) {
		printf("%d, ", current_node->m_val);
		current_node = current_node->getNext();
	}

	printf("%d)\n", current_node->m_val);

	return 0;
}

int List::print_reversed() const {
	if (this->m_len == 0) {
		printf("()");
		return 0;
	} else if (this->m_len == 1) {
		printf("(%d)", this->m_head->m_val);
		return 0;
	}
	printf("(%d, ", this->m_tail->m_val);
	auto current_node = this->m_tail->getPrevious();

	while (current_node->getPrevious() != nullptr) {
		printf("%d, ", current_node->m_val);
		current_node = current_node->getPrevious();
	}

	printf("%d)\n", current_node->m_val);

	return 0;
}
}