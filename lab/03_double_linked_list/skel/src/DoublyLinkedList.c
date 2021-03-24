#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DoublyLinkedList.h"
#include "utils.h"

doubly_linked_list_t* dll_create(unsigned int data_size)
{
    doubly_linked_list_t *list = malloc(sizeof(doubly_linked_list_t));
    DIE(!list, "List was not allocated\n");

    list->data_size = data_size;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

dll_node_t* dll_get_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    DIE(!list, "List was not allocated\n");

    if (!list->head) {
        fprintf(stderr, "List is empty\n");
        return NULL;
    }

    if (n < 0) {
        fprintf(stderr, "Invalid position\n");
        return NULL;
    }

    dll_node_t *curr = NULL;

    if (n < list->size - n) {       // se alege parcurgerea cu cele mai putine iteratii
        unsigned int count = n;
        curr = list->head;

        while (count) {
            curr = curr->next;
            count--;
        }

    } else {
        unsigned int count = list->size - n;
        curr = list->tail;

        while (count) {
            curr = curr->prev;
            count--;
        }

    }

    return curr;
}

static void dll_add_first(doubly_linked_list_t *list, const void *data)
{
    dll_node_t *new_head = malloc(sizeof(dll_node_t));
    DIE(!new_head, "Error in malloc()\n");

    new_head->data = malloc(list->data_size);
    memcpy(new_head->data, data, list->data_size);

    if (!list->head) {              // lista este goala
        new_head->next = NULL;
        new_head->prev = NULL;
        list->head = new_head;
        list->tail = new_head;
        list->size++;
        return;
    }

    list->head->prev = new_head;
    new_head->next = list->head;

    list->head = new_head;

    list->size++;
}

static void dll_add_last(doubly_linked_list_t *list, const void *data)
{
    dll_node_t *new_tail = malloc(sizeof(dll_node_t));
    DIE(!new_tail, "Error in malloc()\n");

    new_tail->data = malloc(list->data_size);
    memcpy(new_tail->data, data, list->data_size);

    dll_node_t *curr = list->tail;

    curr->next = new_tail;
    new_tail->prev = curr;
    new_tail->next = NULL;
    
    list->tail = new_tail;

    list->size++;
}


void dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* data)
{
    DIE(!list, "List is not initiated\n");

    if (n == 0 || !list->head) {
        dll_add_first(list, data);
        return;
    }

    if (n >= list->size) {
        dll_add_last(list, data);
        return;
    }

    dll_node_t *curr = list->head;
    unsigned int count = 0;
    
    while (count < n) {
        curr = curr->next;
        count++;
    }

    dll_node_t *prev = curr->prev;

    dll_node_t *new_node = malloc(sizeof(dll_node_t));
    DIE(!new_node, "Error in malloc()\n");

    new_node->data = malloc(list->data_size);
    memcpy(new_node->data, data, list->data_size);

    prev->next = new_node;
    new_node->prev = prev;
    curr->prev = new_node;
    new_node->next = curr;

    list->size++;
}

static void dll_remove_first_node(doubly_linked_list_t *list)
{
    if (list->size == 1) {  // stergerea singurului element din lista
      free_node(&list->head);
      
      list->head = NULL;
      list->tail = NULL;
      list->size = 0;
      
      return;
    }

    dll_node_t *curr = list->head;
    dll_node_t *next = curr->next;

    next->prev = NULL;
    list->head = next;
    
    list->size--;

    free_node(&curr);
}

static void dll_remove_last_node(doubly_linked_list_t *list)
{
    if (list->size == 1) {  // stergerea singurului element din lista
      free_node(&list->head);
      
      list->head = NULL;
      list->tail = NULL;
      list->size = 0;
      
      return;
    }

    dll_node_t *curr = list->tail;
    dll_node_t *prev = curr->prev;

    prev->next = NULL;
    list->tail = prev;

    list->size--;
    
    free_node(&curr);
}

void dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    DIE(!list, "List was not allocated\n");
    
    if (!list->size) {
      fprintf(stderr, "List is empty\n");
      return;
    }

    if (n < 0) {
        fprintf(stderr, "Invalid position");
        return;
    }

    if (n == 0) {
        dll_remove_first_node(list);
        return;
    }

    if (n >= list->size) {
        dll_remove_last_node(list);
        return;
    }

    dll_node_t *curr = dll_get_nth_node(list, n);
    dll_node_t *prev = curr->prev;

    prev->next = curr->next;
    curr->next->prev = prev;

    list->size--;

    free_node(&curr);
}

unsigned int dll_get_size(doubly_linked_list_t* list)
{

  DIE(!list, "List was not allocated\n");

   /* Daca structura nu ar avea campul size
    
    dll_node_t *curr = list->head;

    unsigned int size = 0;

    while (curr) {
        curr = curr->next;
        count++;
    }

    return count;
   */

   return list->size;
}

void dll_free(doubly_linked_list_t** pp_list)
{
    if (!(*pp_list)) {
        return ;
    } 
    dll_node_t *curr = (*pp_list)->head;

    while ((*pp_list)->size > 0) {
        dll_node_t *tmp = curr;
        curr = curr->next;
        
        free_node(&tmp);
        (*pp_list)->size--;
    }
    
    free(*pp_list);
    *pp_list = NULL;
}

void free_node(dll_node_t **node) {
  free((*node)->data);
  free(*node);

  *node = NULL;
}

void dll_print_int_list(doubly_linked_list_t* list)
{
    dll_node_t *curr = list->head;

    unsigned int count = 0;

    while (count < list->size) {
        printf("%d ", (*(int*)curr->data));
        curr = curr->next;
        count++;
    }

    printf("\n");

}

void dll_print_string_list(doubly_linked_list_t* list)
{
    dll_node_t *curr = list->head;

    unsigned int count = 0;

    while (count < list->size) {
        printf("%s ", ((char*)curr->data));
        curr = curr->next;
        count++;
    }

    printf("\n");
}
