#ifndef LIST_H
#define LIST_H

#include "node.h"
#include <cstddef>
#include <cstdint>

class List {
  private:
	Node *_head;
	Node *_tail;
	size_t _len;

  public:
	List(int32_t *vals, size_t length);
	~List();
	Node *get(size_t index);
	Node *get_head();
	Node *get_tail();
	size_t len();

	void push(int32_t val);
	int insert(size_t index, int32_t val);

	int pop();
	int remove(size_t index);

	int is_valid();

	int print();
	int print_reversed();
};

struct list_t {
	struct node_t *head;
	struct node_t *tail;
	size_t len;
};

struct list_t initialise_list(int32_t *vals, size_t length);
void delete_list(struct list_t *list);

struct node_t *get(struct list_t *list, size_t index);

void push(struct list_t *list, int32_t val);
int insert(struct list_t *list, size_t index, int32_t val);

int pop(struct list_t *list);
int remove_node(struct list_t *list, size_t index);

int check_list_validity(struct list_t *list);

int print_list(struct list_t *list);
int print_list_reversed(struct list_t *list);

#endif // LIST_H
