#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "list.h"
#include "node.h"

List::List() : m_head(nullptr), m_tail(nullptr), m_len(0){};

List::List(int32_t *vals, size_t length) : m_len(length) {
	this->m_head = new Node((length > 0) ? vals[0] : 0, nullptr, nullptr);

	if (length == 0) {
		this->m_tail = this->m_head;
		return;
	}

	auto previous_node = new Node(vals[1], nullptr, this->m_head);
	this->m_head->m_next = previous_node;

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
	auto current_node = this->m_head;
	;
	auto next_node = current_node->m_next;

	while (next_node != nullptr) {
		delete current_node;
		current_node = next_node;
		next_node = current_node->m_next;
	}

	delete current_node;
}

Node *List::get(size_t index) {
	if (index > this->m_len) {
		return nullptr;
	}

	auto current_node = this->m_head;

	if (index == 0) {
		return current_node;
	}

	for (size_t i = 0; i < index; i++) {

		current_node = current_node->getNext();
	}

	return current_node;
}

Node *List::get_head() { return this->m_head; }

Node *List::get_tail() { return this->m_tail; }

size_t List::len() const { return this->m_len; }

void List::push(int32_t val) {
	auto node = new Node(val, nullptr, this->m_tail);

	this->m_tail = node;
	this->m_tail->setNext(node);
}

int List::insert(size_t index, int32_t val) {
	if (index > this->m_len) {
		return 1;
	}

	auto new_node = new Node(val, nullptr, nullptr);

	if (index == 0) {
		auto old_head = this->m_head;
		this->m_head = new_node;
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
	auto tail = this->m_tail;
	auto val = tail->getVal();

	if (this->m_head == this->m_tail) {
		delete this->m_head;
		this->m_head = nullptr;
		this->m_tail = nullptr;
		return val;
	}

	this->m_len--;

	tail->getPrevious()->setNext(nullptr);
	this->m_tail = tail->getPrevious();

	delete tail;

	return val;
}

int List::remove(size_t index) {
	if (index == this->m_len) {
		return this->pop();
	}

	if (index == 0) {
		auto head = this->m_head;
		auto value = head->getVal();

		this->m_head = m_head->getNext();
		this->m_head->setPrevious(nullptr);
		delete head;

		return value;
	}

	auto node = this->get(index);
	auto value = node->getVal();
	auto previous_node = node->getPrevious();
	auto next_node = node->getNext();

	previous_node->setNext(next_node);
	next_node->setPrevious(previous_node);
	this->m_len--;
	delete node;

	return value;
}

int List::is_valid() {
	if (this->m_head == nullptr) {
		return 1;
	} else if (this->m_tail == nullptr) {
		return 2;
	}

	return 0;
}

int List::print() {
	printf("(%d, ", this->m_head->getVal());
	auto current_node = this->m_head->getNext();

	while (current_node->getNext() != nullptr) {
		printf("%d, ", current_node->getVal());
		current_node = current_node->getNext();
	}

	printf("%d)\n", current_node->getVal());

	return 0;
}

int List::print_reversed() {
	printf("(%d, ", this->m_tail->getVal());
	auto current_node = this->m_tail->getPrevious();

	while (current_node->getPrevious() != nullptr) {
		printf("%d, ", current_node->getVal());
		current_node = current_node->getPrevious();
	}

	printf("%d)\n", current_node->getVal());

	return 0;
}
