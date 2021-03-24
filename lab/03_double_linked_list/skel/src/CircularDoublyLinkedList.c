#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"
#include "utils.h"

/*
 * Functie care trebuie apelata pentru alocarea si initializarea unei liste.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
doubly_linked_list_t* dll_create(unsigned int data_size)
{
    doubly_linked_list_t *list = malloc(sizeof(doubly_linked_list_t));
    DIE(!list, "merge");

    list->data_size = data_size;
    list->head = NULL;
    list->size = 0;

    return list;
}

/*
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 * Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se
 * afla pe pozitia n=0). Daca n >= nr_noduri, atunci se intoarce nodul de pe
 * pozitia rezultata daca am "cicla" (posibil de mai multe ori) pe lista si am
 * trece de la ultimul nod, inapoi la primul si am continua de acolo. Cum putem
 * afla pozitia dorita fara sa simulam intreaga parcurgere? Daca n < 0, eroare.
 */
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

    if (n >= list->size) {
        n %= list->size;
    }

    dll_node_t *curr = list->head;
    unsigned int count = 0;

    while (count < n && curr) {
        curr = curr->next;
        count++;
    }

    return curr;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Cand indexam pozitiile nu "ciclam" pe lista circulara ca la
 * get, ci consideram nodurile in ordinea de la head la ultimul (adica acel nod
 * care pointeaza la head ca nod urmator in lista). Daca n >= nr_noduri, atunci
 * adaugam nodul nou la finalul listei. Daca n < 0, eroare.
 */
static void dll_add_first(doubly_linked_list_t *list, const void *data)
{
    dll_node_t *new_head = malloc(sizeof(dll_node_t));
    DIE(!new_head, "Error in malloc()\n");

    new_head->data = malloc(list->data_size);
    memcpy(new_head->data, data, list->data_size);
    //strncpy(new_head->data, data, list->data_size);

    if (!list->head) {              // lista este goala
        new_head->next = new_head;
        new_head->prev = new_head;
        list->head = new_head;
        list->size++;
        return;
    }

    dll_node_t *aux = list->head->prev;

    new_head->next = list->head;
    aux->next = new_head;
    new_head->prev = aux;
    list->head->prev = new_head;

    list->head = new_head;

    list->size++;
}

static void dll_add_last(doubly_linked_list_t *list, const void *data)
{
    dll_node_t *new_tail = malloc(sizeof(dll_node_t));
    DIE(!new_tail, "Error in malloc()\n");

    new_tail->data = malloc(list->data_size);
    memcpy(new_tail->data, data, list->data_size);
    //strncpy(new_tail->data, data, list->data_size);


    dll_node_t *curr = list->head->prev;

    curr->next = new_tail;
    new_tail->prev = curr;
    new_tail->next = list->head;
    list->head->prev = new_tail; 

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
    //strncpy(new_node->data, data, list->data_size);

    prev->next = new_node;
    new_node->prev = prev;
    curr->prev = new_node;
    new_node->next = curr;

    list->size++;
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Functia intoarce un pointer spre acest nod
 * proaspat eliminat din lista. Daca n >= nr_noduri - 1, se elimina nodul de la
 * finalul listei. Daca n < 0, eroare. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */
static dll_node_t* dll_remove_first_node(doubly_linked_list_t *list)
{
    dll_node_t *curr = list->head;
    dll_node_t *prev = curr->prev;

    prev->next = curr->next;
    curr->next->prev = prev;
    
    list->head = curr->next;
    
    list->size--;

    return curr;
}

static dll_node_t* dll_remove_last_node(doubly_linked_list_t *list)
{
    dll_node_t *curr = list->head->prev;
    dll_node_t *prev = curr->prev;

    prev->next = curr->next;
    curr->next->prev = prev;

    list->size--;
    
    return curr;
}

dll_node_t* dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    DIE(!list, "List was not allocated\n");

    if (n < 0) {
        fprintf(stderr, "Invalid position");
        return NULL;
    }

    if (n == 0) {
        dll_node_t *curr = dll_remove_first_node(list);
        return curr;
    }

    if (n >= list->size) {
        dll_node_t *curr = dll_remove_last_node(list);
        return curr;
    }

    dll_node_t *curr = list->head;

    if (n < list->size - n) {       // se alege parcurgerea cu cele mai putine iteratii
        unsigned int count = n;

        while (count) {
            curr = curr->next;
            count--;
        }

    } else {
        unsigned int count = list->size - n;

        while (count) {
            curr = curr->prev;
            count--;
        }

    }
    
    dll_node_t *prev = curr->prev;

    prev->next = curr->next;
    curr->next->prev = prev;

    list->size--;

    return curr;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int dll_get_size(doubly_linked_list_t* list)
{
   /* Daca structura nu ar avea campul size
    
    dll_node_t *curr = list->head;

    unsigned int count = 1;

    while (curr->next != list->head) {
        curr = curr->next;
        count++;
    }

    return count;
   */

   return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista.
 */
void dll_free(doubly_linked_list_t** pp_list)
{
    if (!(*pp_list)) {
        return ;
    } 
    dll_node_t *curr = (*pp_list)->head;

    while ((*pp_list)->size > 0) {
        dll_node_t *tmp = curr;
        
        free(curr->data);
        curr = curr->next;
        
        free(tmp);
        (*pp_list)->size--;
    }
    
    free(*pp_list);
    *pp_list = NULL;
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista separate printr-un spatiu, incepand de la primul nod din lista.
 */
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

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista separate printr-un spatiu, incepand de la primul nod din
 * lista.
 */
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

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza o singura data toate valorile int
 * stocate in nodurile din lista, separate printr-un spatiu, incepand de la
 * nodul dat ca parametru si continuand la stanga in lista dublu inlantuita
 * circulara, pana cand sunt afisate valorile tuturor nodurilor.
 */
void dll_print_ints_left_circular(dll_node_t* start)
{
    dll_node_t *curr = start;

    while (curr->prev != start) {
        printf("%d ", (*(int*)curr->data));
        curr = curr->prev;
    }
    printf("%d ", (*(int*)curr->data));

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza o singura data toate valorile int
 * stocate in nodurile din lista, separate printr-un spatiu, incepand de la
 * nodul dat ca parametru si continuand la dreapta in lista dublu inlantuita
 * circulara, pana cand sunt afisate valorile tuturor nodurilor.
 */
void dll_print_ints_right_circular(dll_node_t* start)
{
    dll_node_t *curr = start;

    while (curr->next != start) {
        printf("%d ", (*(int*)curr->data));
        curr = curr->next;
    }
    printf("%d ", (*(int*)curr->data));
    
    printf("\n");
}
