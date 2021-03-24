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
ll_node_t *remove_middle(linked_list_t *list) {
  if (!list->head) {
    return NULL;
  }

  if (!list->head->next) {
    ll_node_t *tmp = list->head;
    list->head = NULL;
    return tmp;
  }
  if (!list->head->next->next) {
    ll_node_t *tmp = list->head;
    list->head = list->head->next;
    return tmp;
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

  return slow;
}
