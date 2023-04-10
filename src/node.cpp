#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "node.h"

Node::Node(int32_t val, Node *next, Node *previous) {
	this->_val = val;
	this->_next = next;
	this->_previous = previous;
}

/*
 * Prints out a node with the format (the next and previous nodes will just be
 * printed as pointers:
 *
 * Node {
 * 	val: node->val,
 * 	next: node->next,
 * 	previous: node->previous,
 * }
 */
void Node::print() const {
	printf("Node {\n  val: %d,\n  next: %ld,\n  previous: %ld\n}\n", this->_val,
		   (size_t)this->getNext(), (size_t)this->getPrevious());
}

int32_t Node::getVal() const { return _val; }
void Node::setVal(int32_t val) { _val = val; }

Node *Node::getNext() const { return _next; }
void Node::setNext(Node *next) { _next = next; }

Node *Node::getPrevious() const { return _previous; }
void Node::setPrevious(Node *previous) { _previous = previous; }

