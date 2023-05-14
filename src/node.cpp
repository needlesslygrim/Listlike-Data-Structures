#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "node.h"

Node::Node() : m_val(0), m_next(nullptr), m_previous(nullptr) {}

Node::Node(int32_t val) : m_val(val), m_next(nullptr), m_previous(nullptr) {}

Node::Node(int32_t val, Node *next, Node *previous)
	: m_val(val), m_next(next), m_previous(previous) {}

/*
 * Prints out a node with the format (the next and previous nodes will just be
 * printed as pointers:
 *S
 * Node {
 * 	val: node->val,
 * 	next: node->next,
 * 	previous: node->previous,
 * }
 */
void Node::print() const {
	printf("Node {\n  val: %d,\n  next: %ld,\n  previous: %ld\n}\n",
		   this->m_val, (size_t)this->getNext(), (size_t)this->getPrevious());
}

Node *Node::getNext() const { return m_next; }

Node *Node::getPrevious() const { return m_previous; }
