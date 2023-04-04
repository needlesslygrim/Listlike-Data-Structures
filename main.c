#include <stdio.h>

#include "list.h"

int main(void) {
  struct node_t *head = (struct node_t *)malloc(sizeof(struct node_t));
  head->val = 0;
  head->previous = NULL;
  head->next = NULL;

  struct node_t *one = (struct node_t *)malloc(sizeof(struct node_t));
  one->previous = head;
  one->val = 1;
  head->next = one;

  struct node_t *two = (struct node_t *)malloc(sizeof(struct node_t));
  two->previous = one;
  two->next = NULL;
  two->val = 2;
  one->next = two;
  print_from_head(head);
  push_val(4, two);
  print_from_head(head);

  pop_previous_node(two->next);
  print_from_head(head);

  delete_list(head);
}
