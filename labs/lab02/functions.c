#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "utils.h"

/*
 * Functia primeste ca singur parametru lista si returneaza pointerul nodului 
 * care trebuie eliminat din lista. Se verifica initial cazurile speciale care 
 * sunt tratate separat (lista este goala, are un singur element sau doar doua
 * elemente). Altfel, sunt utilizati trei pointeri auxiliari: prev (retine 
 * adresa anterioara lui slow), slow (avanseaza cu pasul 1), fast (avanseaza cu
 * pasul 2), astfel incat slow se va afla la jumatatea listei cand parcurgerea
 * este terminata (fast ajunge la sfarsitul listei), iar prev se afla pe pozitia
 * anterioara lui slow pentru a reface legaturile din lista
*/
void remove_middle(linked_list_t *list)
{
  if (!list->head) {
    return;
  }

  if (!list->head->next) {
    ll_node_t *tmp = list->head;
    list->head = NULL;
    
    free_node(tmp);
  }

  if (!list->head->next->next) {
    ll_node_t *tmp = list->head;
    list->head = list->head->next;
   
    free_node(tmp);
  }

  ll_node_t *fast = list->head;
  ll_node_t *slow = list->head;
  ll_node_t *prev;

  while (fast->next && fast->next->next) {
    prev = slow;
    fast = fast->next->next;
    slow = slow->next;
  }
  prev->next = slow->next;

  free_node(slow);
}

/*
 *
 * 
 * 
 * 
 * 
*/
void reverse_list(linked_list_t *list)
{
  ll_node_t *prev = NULL;
  ll_node_t *curr = list->head;
  ll_node_t *next;

  while (curr) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  list->head = prev;
}

linked_list_t *sort_2_list_int(linked_list_t *list1, linked_list_t *list2)
{
  linked_list_t *new_list = ll_create(list1->data_size);
  new_list->size = list1->size + list2->size;

  ll_node_t *curr1 = list1->head;
  ll_node_t *curr2 = list2->head;
  unsigned int count = 0;
  
  while (curr1 && curr2) {
    if ((*(int*)curr1->data) < (*(int*)curr2->data)) {
      ll_add_nth_node(new_list, count, curr1->data);
      curr1 = curr1->next;
      count++;
    } else {
      ll_add_nth_node(new_list, count, curr2->data);
      curr2 = curr2->next;
      count++;
    }

  }

  while (curr1) {
    ll_add_nth_node(new_list, count, curr1->data);
    curr1 = curr1->next;
    count++;
  }

  while (curr2) {
    ll_add_nth_node(new_list, count, curr2->data);
    curr2 = curr2->next;
    count++;
  }
  
  return new_list;
}


