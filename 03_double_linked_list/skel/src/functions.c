#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DoublyLinkedList.h"
#include "utils.h"

/*
 * Se dau două liste dublu înlănțuite, A și B, ale căror noduri stochează în ordine 
 * inversă cifrele câte unui număr natural reprezentat în baza 10 (primul nod al unei
 *  liste stochează cea mai puțin semnificativă cifră). Creați o nouă listă dublu 
 * înlănțuită, C, care stochează suma celor două numere. Lista C trebuie construită în
 *  timp ce se parcurg listele A și B!
 * Exemplu: pentru listele A: 4 ⇔ 3 ⇔ 2 ⇔ 9 și B: 6 ⇔ 6 ⇔ 7, va rezulta lista C: 0 ⇔ 0 ⇔ 0 ⇔ 0 ⇔ 1
*/
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

/*
 *Implementați o funcție care primește ca parametru un pointer la începutul
 * unei liste dublu înlănțuite sortată crescător și elimină nodurile cu valori
 * duplicate (păstrând un singur nod din fiecare grup de duplicate).
 * 
 * Exemplu: pentru lista 1 ⇔ 2 ⇔ 2 ⇔ 3 ⇔ 5 ⇔ 5 ⇔ 5 ⇔ 9 rezultă lista 1 ⇔ 2 ⇔ 3 ⇔ 5 ⇔ 9.
*/

void remove_duplicates(doubly_linked_list_t *list)
{
  DIE(!list, "List was not allocated\n");
  
  if (!list->size) {
    fprintf(stderr, "List is empty\n");
    return;
  }

  if (!list->head) {
    fprintf(stderr, "List is empty\n");
  }

  dll_node_t *curr = list->head;
  unsigned int pos = 0;

  while (curr->next->next) {
    if ((*(int*)curr->data) == (*(int*)curr->next->data)) {
      dll_remove_nth_node(list, pos + 1);
    }
    if (curr->next) {
      curr = curr->next;
    }
    pos++;
  }

  if ((*(int*)curr->data) == (*(int*)curr->next->data)) {
    dll_remove_nth_node(list, list->size);
  }
  
}

/*
 * Implementați o funcție care primește ca parametru un pointer la începutul
 *  unei liste dublu înlănțuite și inversează ordinea nodurilor din listă 
 * (fără alocare de memorie auxiliară pentru o nouă listă).
 * 
 * Exemplu: pentru lista 1 ⇔ 2 ⇔ 3 rezultă lista 3 ⇔ 2 ⇔ 1
 * 
*/

void list_inversion(doubly_linked_list_t *list)
{
  DIE(!list, "List was not allocated\n");
  
  if (!list->size) {
    fprintf(stderr, "List is empty\n");
    return;
  }
 
  dll_node_t *curr = list->head;
  dll_node_t *tmp = NULL;

  while (curr) {
    tmp = curr->prev;
    curr->prev = curr->next;
    curr->next = tmp;

    curr = curr->prev;
  }

  dll_node_t *old_head = list->head;
  list->head = tmp->prev;
  list->tail = old_head;

  
}

/*
 * Fiind date două liste dublu înlănţuite, A şi B, ale căror noduri stochează 
 * valori integer, construiţi o nouă listă dublu înlănţuită, C, pentru care 
 * fiecare nod i este suma nodurilor asociate din A şi B. Mai exact, nodul i 
 * din C reţine suma dintre valoarea nodului i din A şi valoarea nodului i 
 * din B. Dacă una dintre listele primite este mai lungă decât cealaltă, se
 * consideră că nodurile asociate lipsă din cealaltă listă conţin valoarea 0,
 *  adică se păstrează valorile din lista mai lungă.
 * 
 * Exemplu: pentru listele A: 3 ⇔ 7 ⇔ 29 ⇔ 4 și B: 2 ⇔ 4 ⇔ 3, va rezulta lista C: 5 ⇔ 11 ⇔ 32 ⇔ 4.
 * 
*/

doubly_linked_list_t *sum_elem(doubly_linked_list_t *list1, doubly_linked_list_t *list2)
{
  doubly_linked_list_t *list3 = dll_create(sizeof(int));

  dll_node_t *a = list1->head;
  dll_node_t *b = list2->head;
  
  unsigned int pos = 0;
  
  while (a || b) {
    int num = (*(int*)a->data) + (*(int*)b->data);
    dll_add_nth_node(list3, pos, &num);

    a = a->next;
    b = b->next;
    pos++;
  }

  while (a) {
    int num = (*(int*)a->data);
    dll_add_nth_node(list3, pos, &num);

    a = a->next;
    pos++;
  }

  while (b) {
    int num = (*(int*)b->data);
    dll_add_nth_node(list3, pos, &num);

    b = b->next;
    pos++;
  }

  return list3;
}

/*
 * Implementați o funcție care primește ca parametri doi pointeri la începuturile
 * a două liste dublu înlănțuite sortate și întoarce o listă dublu înlănțuită 
 * sortată ce conține toate elementele din cele două liste.
 * 
 * Exemplu: pentru listele 1 ⇔ 2 ⇔ 5 ⇔ 9 și 2 ⇔ 3 ⇔ 7 ⇔ 8 ⇔ 10 rezultă lista 1 ⇔ 2 ⇔ 2 ⇔ 3 ⇔ 5 ⇔ 7 ⇔ 8 ⇔ 9 ⇔ 10.
*/

doubly_linked_list_t *merge_2_sorted_lists(doubly_linked_list_t *list1, doubly_linked_list_t *list2)
{
  doubly_linked_list_t *list3 = dll_create(sizeof(int));

  dll_node_t *curr1 = list1->head;
  dll_node_t *curr2 = list2->head;

  unsigned int pos = 0;

  while (curr1 && curr2) {
    
    if ((*(int*)curr1->data) < (*(int*)curr2->data)) {
      dll_add_nth_node(list3, pos, (int*)curr1->data);
      curr1 = curr1->next;
    } else {
      dll_add_nth_node(list3, pos, (int*)curr2->data);
      curr2 = curr2->next;
    }

    pos++;
  }

  while (curr1) {
    dll_add_nth_node(list3, pos, (int*)curr1->data);
    curr1 = curr1->next;

    pos++;
  }

  while (curr2) {
    dll_add_nth_node(list3, pos, (int*)curr2->data);
    curr2 = curr2->next;

    pos++;
  }

  return list3;
}

/*
 * Se dă o listă dublu înlănţuită ale cărei noduri reţin valori de tip int şi,
 * se dă de asemenea, un integer X. Reordonaţi nodurile din listă astfel încât 
 * toate nodurile cu valori mai mici sau egale decât X să apară înaintea nodurilor
 * cu valori mai mari decât X. Nu alocaţi noduri noi!
 * 
 * Exemplu: pentru lista 3 ⇔ 6 ⇔ 5 ⇔ 4 ⇔ 2 şi integer-ul 3, o posibilă listă rezultat este 2 ⇔ 3 ⇔ 4 ⇔ 6 ⇔ 5.
 * 
*/
static void swap_data(dll_node_t *a, dll_node_t *b)
{
  int aux = (*(int*)a->data);
  (*(int*)a->data) = (*(int*)b->data);
  (*(int*)b->data)= aux;
}

void sort_list(doubly_linked_list_t *list)
{
  DIE(!list, "List was not allocated\n");
  
  if (!list->size) {
    fprintf(stderr, "List is empty\n");
    return;
  }

  int sorted = 0;
  while (!sorted) {
    sorted = 1;
    dll_node_t *curr = list->head;
    while (curr->next) {
      if ((*(int*)curr->data) > (*(int*)curr->next->data)) {
        swap_data(curr, curr->next);

        sorted = 0;
      }
      curr = curr->next;
    }
  }
}

/*
 * Implementați o funcție care primește ca parametru un pointer la începutul unei
 * liste dublu înlănțuite și întoarce o listă dublu înlănțuită obținută prin următoarea
 * procesare a listei inițiale: între fiecare nod și succesorul său (din lista inițială)
 * se introduce un nou nod, având ca valoare suma valorilor celor două noduri învecinate.
 * 
 * Exemplu: pentru lista 1 ⇔ 2 ⇔ 5 ⇔ 6 ⇔ 7 ⇔ 9 rezultă lista 1 ⇔ 3 ⇔ 2 ⇔ 7 ⇔ 5 ⇔ 11 ⇔ 6 ⇔ 13 ⇔ 7 ⇔ 16 ⇔ 9.
 * 
*/

void add_sum_nodes(doubly_linked_list_t *list)
{
  DIE(!list, "List was not allocated\n");
  
  if (!list->size) {
    fprintf(stderr, "List is empty\n");
    return;
  }

  dll_node_t *curr = list->head;
  unsigned int pos = 1;

  while (curr->next) {
    int data = (*(int*)curr->data) + (*(int*)curr->next->data);
    dll_add_nth_node(list, pos, &data);

    pos += 2;
    curr = curr->next->next;
  }

}