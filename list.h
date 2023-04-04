//
// Created by erickth on 04/04/23.
//

#ifndef LIST_LIST_H
#define LIST_LIST_H

struct node_t {
  int val;
  struct node_t *next;
  struct node_t *previous;
};

struct list_t {
  struct node_t *head;
  struct node_t *tail;
  unsigned long long len;
};

struct node_t *initialise_node(int val, struct node_t *next,
                               struct node_t *previous);

struct list_t *initialise_list(int *vals, int length);

struct node_t *get(struct list_t *list, unsigned long long index);

void push_val(int val, struct list_t *node);

void delete_list(struct list_t *list);

int pop(struct node_t *list);

int pop_next_node(struct node_t *list);

void print_list(struct node_t *list);

#endif // LIST_LIST_H
