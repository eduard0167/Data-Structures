#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 64

int main(void) {
  
  int n;
  scanf("%d", &n);
  
  linked_list_t *list1 = ll_create(sizeof(int));
  
  for (int i = 1; i <= n; i += 2) {
    ll_add_nth_node(list1, i, &i);
  }
  ll_print_int(list1);

  linked_list_t *list2 = ll_create(sizeof(int));

  for (int i = 2; i <= n; i += 2) {
    ll_add_nth_node(list2, i, &i);
  }
  ll_print_int(list2);

  linked_list_t *list3 = sort_2_list_int(list1, list2);

  ll_print_int(list3);

  //printf("%p %p %p\n", list1->head, list2->head, list3->head);
  ll_free(&list1);
  ll_free(&list2);
  ll_free(&list3);



  /*
  // Test for int

  linked_list_t *list = ll_create(sizeof(int));
  
  int n;
  printf("Enter number of nodes: ");
  scanf("%d", &n);
  printf("Enter data of nodes: value position\n");
  
  for (int i = 0; i < n; i++) {
    int val, pos;
    scanf("%d%d", &val, &pos);
    ll_add_nth_node(list, pos, &val);
  }
  ll_print_int(list);

  remove_middle(list);

  ll_print_int(list);

  ll_free(&list);

  // Test for strings

  list = ll_create(MAX_STRING_SIZE);

  printf("Enter number of nodes: ");
  scanf("%d", &n);
  printf("Enter data of nodes: value position\n");

  for (int i = 0; i < n; i++) {
    char val[MAX_STRING_SIZE];
    int pos;
    scanf("%s%d", val, &pos);
    ll_add_nth_node(list, pos, &val);
  }
  ll_print_string(list);

  remove_middle(list);

  ll_print_string(list);

  ll_free(&list);
  */

  return 0;
}