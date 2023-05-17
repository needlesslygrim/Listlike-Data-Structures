#ifndef LIST_H
#define LIST_H

#include "node.h"
#include <cstddef>
#include <cstdint>

namespace dl_list {
class List {
  public:
	List();
	explicit List(int32_t val);
	List(int32_t *vals, size_t length);
	~List();
	int32_t &operator[](size_t index) const;
	Node *get(size_t index) const;
	Node *getHead() const;
	Node *getTail() const;
	size_t len() const;

	void push(int32_t val);
	void insert(size_t index, int32_t val);
	int32_t pop();
	int32_t remove(size_t index);

	int isValid() const;

	int print() const;
	int print_reversed() const;

  private:
	Node *m_head;
	Node *m_tail;
	size_t m_len;
};

} // namespace dl_list

#endif // LIST_H
