#ifndef NODE_H
#define NODE_H

#include <cstdint>

class Node {
  private:
	int32_t _val;
	Node *_next;
	Node *_previous;

  public:
	Node(int32_t val, Node *next, Node *previous);
	void print() const;

	int32_t getVal() const;
	void setVal(int32_t val);
	Node *getNext() const;
	void setNext(Node *next);
	Node *getPrevious() const;
	void setPrevious(Node *previous);
};

#endif // NODE_H
