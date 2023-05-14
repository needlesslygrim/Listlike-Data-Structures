#ifndef NODE_H
#define NODE_H

#include <cstdint>
namespace dl_list {
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
} // namespace dl_list

#endif // NODE_H
