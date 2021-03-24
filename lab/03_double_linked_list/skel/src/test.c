#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"
#include "functions.h"

int main (void) {

  doubly_linked_list_t *list1 = dll_create(sizeof(int));
  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    dll_add_nth_node(list1, i, &x);
  }

  dll_print_int_list(list1);

  add_sum_nodes(list1);

  dll_print_int_list(list1);

  dll_free(&list1);
  return 0;
}
