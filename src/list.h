#ifndef LIST_H
#define LIST_H

#include "node.h"
#include <cstddef>
#include <cstdint>

class List {
  private:
	Node *m_head;
	Node *m_tail;
	size_t m_len;

  public:
	List();
	List(int32_t *vals, size_t length);
	~List();
	Node *get(size_t index);
	Node *getHead();
	Node *getTail();
	size_t len() const;

	void push(int32_t val);
	int insert(size_t index, int32_t val);

	int pop();
	int remove(size_t index);

	int is_valid();

	int print();
	int print_reversed();
};

#endif // LIST_H
