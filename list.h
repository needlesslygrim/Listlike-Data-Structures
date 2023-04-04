//
// Created by erickth on 04/04/23.
//

#ifndef LIST_LIST_H
#define LIST_LIST_H

struct list_t {
	struct node_t *head;
	struct node_t *tail;
	unsigned long long len;
};

struct list_t *initialise_list(int *vals, unsigned long long length);
void delete_list(struct list_t *list);

struct node_t *get(struct list_t *list, unsigned long long index);

void push(int val, struct list_t *node);
int pop(struct list_t *list);

int check_list_validity(struct list_t *list);

int print_list(struct list_t *list);
int print_list_reverse(struct list_t *list);

#endif // LIST_LIST_H
