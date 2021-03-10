#ifndef __LISTE_H__
#define __LISTE_H__

typedef struct node{
  int data;
  struct node *next;
} Node;

typedef struct {
  Node* head;
  int size;
} LinkedList;

LinkedList *init_list(void);
LinkedList *read_list(LinkedList *list);

void list_inversion(LinkedList *list);

LinkedList *merge_list(LinkedList *list1, LinkedList *list2);

void add_first(LinkedList *list);
void add_last(LinkedList *list);
void add_nth(LinkedList *list, int poz);

void remove_first(LinkedList *list);
void remove_last(LinkedList *list);
void remove_nth(LinkedList *list, int poz);

void printList(Node *n);
void free_list(LinkedList *list);

#endif