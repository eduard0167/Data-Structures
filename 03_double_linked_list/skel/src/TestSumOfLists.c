#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DoublyLinkedList.h"

void int_to_list(unsigned long int num, doubly_linked_list_t *list)
{
  int pos = 0;
  while (num > 0) {
    int aux = num % 10;
    dll_add_nth_node(list, pos, &aux);

    num /= 10;
    pos++;
  }
}

doubly_linked_list_t *sum_lists(doubly_linked_list_t *list1, doubly_linked_list_t *list2)
{
  doubly_linked_list_t *sum = dll_create(sizeof(int));

  dll_node_t *num1 = list1->head;
  dll_node_t *num2 = list2->head;

  int rest = 0, pos = 0, rez = 0;
  while (num1 && num2) {
    rez = (*(int*)num1->data) + (*(int*)num2->data) + rest;
    rest = 0;

    if (rez > 9) {
      rest++;
    }

    rez %= 10;
    dll_add_nth_node(sum, pos, &rez);

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
    dll_add_nth_node(sum, pos, &rez);

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
    dll_add_nth_node(sum, pos, &rez);

    num2 = num2->next;
    pos++;
  }

  if (rest) {
    dll_add_nth_node(sum, pos, &rest);
  }

  return sum;
}

int main(void) {
  unsigned long int num1, num2;

  printf("Enter 2 natural numbers: ");
  scanf("%ld%ld", &num1, &num2);

  doubly_linked_list_t *list1 = dll_create(sizeof(int));
  doubly_linked_list_t *list2 = dll_create(sizeof(int));

  int_to_list(num1, list1);
  int_to_list(num2, list2);

  printf("Representation in lists:\n");
  dll_print_int_list(list1);
  dll_print_int_list(list2);

  doubly_linked_list_t *sum = NULL;
  sum = sum_lists(list1, list2);

  printf("Sum:\n");
  dll_print_int_list(sum);

  dll_free(&sum);
  dll_free(&list1);
  dll_free(&list2);
  
  return 0;
}