#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 64

int main(void) {
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

  ll_node_t *removed = remove_middle(list);
  
  if (removed) {
    free(removed->data);
    free(removed);
    removed = NULL;
  }

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

  removed = remove_middle(list);

    if (removed) {
    free(removed->data);
    free(removed);
    removed = NULL;
  }

  ll_print_string(list);

  ll_free(&list);

  return 0;
}