#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

void int_to_list(unsigned long int num, linked_list_t *list)
{
  int pos = 0;
  while (num > 0) {
    int aux = num % 10;
    ll_add_nth_node(list, pos, &aux);

    num /= 10;
    pos++;
  }
}

linked_list_t *sum_lists(linked_list_t *list1, linked_list_t *list2)
{
  linked_list_t *sum = ll_create(sizeof(int));

  ll_node_t *num1 = list1->head;
  ll_node_t *num2 = list2->head;

  int rest = 0, pos = 0, rez = 0;
  while (num1 && num2) {
    rez = (*(int*)num1->data) + (*(int*)num2->data) + rest;
    rest = 0;

    if (rez > 9) {
      rest++;
    }

    rez %= 10;
    ll_add_nth_node(sum, pos, &rez);

    num1 = num1->next;
    num2 = num2->next;
    pos++;
  }

  while (num1) {
    rez = (*(int*)num1->data) + rest;
    rest = 0;

    if (rez > 9) {
      rest++;
    }
    rez %= 10;
    ll_add_nth_node(sum, pos, &rez);

    num1 = num1->next;
    pos++;
  }

  while (num2) {
    rez = (*(int*)num2->data) + rest;
    rest = 0;

    if (rez > 9) {
      rest++;
    }
    rez %= 10;
    ll_add_nth_node(sum, pos, &rez);

    num2 = num2->next;
    pos++;
  }

  if (rest) {
    ll_add_nth_node(sum, pos, &rest);
  }

  return sum;
}

int main(void) {
  unsigned long int num1, num2;

  printf("Enter 2 natural numbers: ");
  scanf("%ld%ld", &num1, &num2);

  linked_list_t *list1 = ll_create(sizeof(int));
  linked_list_t *list2 = ll_create(sizeof(int));

  int_to_list(num1, list1);
  int_to_list(num2, list2);

  printf("Representation in lists:\n");
  ll_print_int(list1);
  ll_print_int(list2);

  linked_list_t *sum = NULL;
  sum = sum_lists(list1, list2);

  printf("Sum:\n");
  ll_print_int(sum);

  ll_free(&sum);
  ll_free(&list1);
  ll_free(&list2);
  
  return 0;
}