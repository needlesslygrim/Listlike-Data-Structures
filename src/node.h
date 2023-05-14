#ifndef NODE_H
#define NODE_H

#include <cstdint>

class Node {
  public:
	int32_t m_val;

	friend class List;

  public:
	Node();
	explicit Node(int32_t val);
	Node(int32_t val, Node *next, Node *previous);
	Node *getNext() const;
	Node *getPrevious() const;
	void print() const;

  private:
	Node *m_next;
	Node *m_previous;
};

#endif // NODE_H
