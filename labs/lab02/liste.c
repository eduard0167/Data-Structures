#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

int main (void) {

  LinkedList *list = init_list();
  read_list(list);

  LinkedList *list2 = init_list();
  read_list(list2);

  LinkedList *list3 = NULL;
  list3 = merge_list(list, list2);
  printList(list->head);
  printList(list2->head);
  printList(list3->head);

/*
  list_inversion(list);
  printList(list->head);

  printList(list->head);
  printf("\n");
  
  add_first(list);

  printList(list->head);
  printf("\n");

  add_last(list);

  printList(list->head);
  printf("\n");

  add_nth(list, 3);

  printList(list->head);
  printf("\n");

  remove_first(list);

  printList(list->head);
  printf("\n");

  remove_last(list);

  printList(list->head);
  printf("\n");

  remove_nth(list, 2);

  printList(list->head);
  printf("\n");
*/

  free_list(list);
  free_list(list2);
  free_list(list3);
  return 0;
}