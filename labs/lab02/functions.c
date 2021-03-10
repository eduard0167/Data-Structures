#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

LinkedList *init_list(void) {
  LinkedList *list = malloc(sizeof(LinkedList));
  scanf("%d", &list->size);
  list->head = NULL;

  return list;
}

LinkedList *read_list(LinkedList *list) {

  if (list->size <= 0) {
    return NULL;
  }
  
  add_first(list);

  for (int i = 1; i < list->size; i++) {
    add_nth(list, i + 1);
  }


  return list;
}

LinkedList *merge_list(LinkedList *list1, LinkedList *list2) {
  LinkedList *list = malloc(sizeof(LinkedList));
  list->size = list1->size + list2->size;
  
  Node *tmp = malloc(sizeof(Node));
  list->head = tmp;

  Node *a = list1->head;
  Node *b = list2->head;
  

  while (a && b) {
  
    if (a->data < b->data) {
      tmp->data = a->data;
      a = a->next;
    } else {
      tmp->data = b->data;
      b = b->next;
    }
    
    tmp->next = malloc(sizeof(Node));
    tmp = tmp->next;
  }


  while (a) {
    tmp->data = a->data;
    a = a->next;
    if (a) {
      tmp->next = malloc(sizeof(Node));
      tmp = tmp->next;
    }
  }

  while (b) {
    tmp->data = b->data;
    b = b->next;

    if (b) {
      tmp->next = malloc(sizeof(Node));
      tmp = tmp->next;
    }
  }
  tmp->next = NULL;
  //printList(list->head);
  
  return list;
}


void list_inversion(LinkedList *list) {
  Node *prev = NULL;
  Node *current = list->head;
  Node *next = NULL;

  while (current) {

    next = current->next;

    current->next = prev;

    prev = current;
    current = next;
  }

  list->head = prev;
}


void add_first(LinkedList *list) {
  Node *new_head = malloc(sizeof(Node));
  scanf("%d", &new_head->data);

  new_head->next = list->head;
  list->head = new_head;  
}

void add_last(LinkedList *list) {
  Node *new_tail = malloc(sizeof(Node));
  Node *n = list->head;

  while (n->next) {
    n = n->next;
  }

  n->next = new_tail;
  scanf("%d", &new_tail->data);
  new_tail->next = NULL;
}

void add_nth(LinkedList *list, int poz) {
  Node *n = list->head;
  int count = 1;

  while (count < poz - 1 && n) {
    n = n->next;
    count++;
  }
  
  if (!n) {
    return;
  }

  Node *tmp = n->next;
  Node *new_node = malloc(sizeof(Node));
  
  n->next = new_node;
  scanf("%d", &new_node->data);
  new_node->next = tmp;
  
}

void remove_first(LinkedList *list) {
  Node *tmp = list->head;
  list->head = list->head->next;

  free(tmp);
}

void remove_last(LinkedList *list) {
  Node *n = list->head;
  
  while (n->next->next) {
    n = n->next;
  }

  Node *tmp = n->next;
  n->next = NULL;

  free(tmp);
}

void remove_nth(LinkedList *list, int poz) {
  int count = 1;
  Node *n = list->head;

  while (n && count < poz - 1) {
    n = n->next;
    count++;
  }

  Node *tmp = n->next;
  n->next = tmp->next;

  free(tmp);

}

void printList(Node *n) {
  while (n) {
    printf("%d\n", n->data);
    n = n->next;
  }
}

void free_list(LinkedList *list) {
  Node *n = list->head;
  
  while (n) {
    Node *tmp = n;
    n = n->next;
    free(tmp);
  }

  free(list);
}
