#include <stdio.h>

#include "list.h"

int main(void) {
  struct node_t *head = initialise_node(0, NULL, NULL);
  struct node_t *one = initialise_node(1, NULL, head);
  struct node_t *two = initialise_node(2, NULL, one);
  struct node_t *three = initialise_node(3, NULL, two);
  struct node_t *four = initialise_node(4, NULL , three);
  struct node_t *five = initialise_node(5, NULL, four);
  
  head->next = one;
  one->next = two;
  two->next = three;
  three->next = four;
  four->next = five;

  struct list_t list = { head, five, 4};
  print_list(&list);
  // print_node(get(&list, 0));
  print_list_reverse(&list);
}
