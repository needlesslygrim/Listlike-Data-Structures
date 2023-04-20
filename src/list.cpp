#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "list.h"
#include "node.h"

List::List(int32_t *vals, size_t length) {
	this->_tail = nullptr;
	this->_len = length;

	this->_head = new Node((length > 0) ? vals[0] : 0, nullptr, nullptr);

	if (length == 0) {
		return;
	}

	auto previous_node = new Node(vals[1], nullptr, this->_head);
	this->_head->setNext(previous_node);

	for (size_t i = 2; i < length - 1; i++) {
		auto node = new Node(vals[i], nullptr, previous_node);

		previous_node->setNext(node);
		previous_node = node;
	}

	auto tail = new Node(vals[length - 1], nullptr, previous_node);
	previous_node->setNext(tail);
	this->_tail = tail;
}
List::~List() {
	auto current_node = this->_head;
	Node *next_node;
	while ((next_node = current_node->getNext()) != nullptr) {
		next_node->setPrevious(nullptr);
		delete current_node;
		current_node = next_node;
	}

	delete current_node;
	this->_head = nullptr;
	this->_tail = nullptr;
	this->_len = 0;
}

Node *List::get(size_t index) {
	if (index > this->_len) {
		return nullptr;
	}

	auto current_node = this->_head;

	if (index == 0) {
		return current_node;
	}

	for (size_t i = 0; i < index; i++) {

		current_node = current_node->getNext();
	}

	return current_node;
}

Node *List::get_head() { return this->_head; }
Node *List::get_tail() { return this->_tail; }

size_t List::len() const { return this->_len; }
void List::push(int32_t val) {
	auto node = new Node(val, nullptr, this->_tail);

	this->_tail = node;
	this->_tail->setNext(node);
}

int List::insert(size_t index, int32_t val) {
	if (index > this->_len) {
		return 1;
	}

	auto new_node = new Node(val, nullptr, nullptr);

	if (index == 0) {
		auto old_head = this->_head;
		this->_head = new_node;
		new_node->setPrevious(old_head);
		old_head->setNext(new_node);
		return 0;
	}

	auto node = this->get(index);
	auto previous_node = node->getPrevious();
	previous_node->setNext(new_node);
	new_node->setPrevious(previous_node);
	new_node->setNext(node);
	node->setPrevious(new_node);

	return 0;
}

int List::pop() {
	auto tail = this->_tail;
	auto val = tail->getVal();

	if (this->_head == this->_tail) {
		delete this->_head;
		this->_head = nullptr;
		this->_tail = nullptr;
		return val;
	}

	this->_len--;

	tail->getPrevious()->setNext(nullptr);
	this->_tail = tail->getPrevious();

	delete tail;

	return val;
}

int List::remove(size_t index) {
	if (index == this->_len) {
		return this->pop();
	}

	if (index == 0) {
		auto head = this->_head;
		auto value = head->getVal();

		this->_head = _head->getNext();
		this->_head->setPrevious(nullptr);
		delete head;

		return value;
	}

	auto node = this->get(index);
	auto value = node->getVal();
	auto previous_node = node->getPrevious();
	auto next_node = node->getNext();

	previous_node->setNext(next_node);
	next_node->setPrevious(previous_node);
	this->_len--;
	delete node;

	return value;
}

int List::is_valid() {
	if (this->_head == nullptr) {
		return 1;
	} else if (this->_tail == nullptr) {
		return 2;
	}

	return 0;
}

int List::print() {
	printf("(%d, ", this->_head->getVal());
	auto current_node = this->_head->getNext();

	while (current_node->getNext() != nullptr) {
		printf("%d, ", current_node->getVal());
		current_node = current_node->getNext();
	}

	printf("%d)\n", current_node->getVal());

	return 0;
}

int List::print_reversed() {
	printf("(%d, ", this->_tail->getVal());
	auto current_node = this->_tail->getPrevious();

	while (current_node->getPrevious() != nullptr) {
		printf("%d, ", current_node->getVal());
		current_node = current_node->getPrevious();
	}

	printf("%d)\n", current_node->getVal());

	return 0;
}
