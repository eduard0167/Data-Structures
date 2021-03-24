#ifndef __FUNCTIONS_H_
#define __FUNCTIONS_H_

void int_to_list(unsigned long int num, doubly_linked_list_t *list);
doubly_linked_list_t *sum_lists(doubly_linked_list_t *list1, doubly_linked_list_t *list2);

void remove_duplicates(doubly_linked_list_t *list);
void list_inversion(doubly_linked_list_t *list);

doubly_linked_list_t *sum_elem(doubly_linked_list_t *list1, doubly_linked_list_t *list2);

doubly_linked_list_t *merge_2_sorted_lists(doubly_linked_list_t *list1, doubly_linked_list_t *list2);

void sort_list(doubly_linked_list_t *list);

void add_sum_nodes(doubly_linked_list_t *list);


#endif