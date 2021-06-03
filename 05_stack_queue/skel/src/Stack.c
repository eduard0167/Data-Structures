#include <stdlib.h>

#include "Stack.h"
#include "utils.h"

stack_t *st_create(unsigned int data_size)
{
	stack_t *stack = malloc(sizeof(stack_t));
	DIE(!stack, "malloc() for stack failed\n");

	stack->list = ll_create(data_size);
	DIE(!stack->list, "malloc() for list failed\n");

	return stack;
}

unsigned int st_get_size(stack_t *st)
{
	if (!st || !st->list) {
		fprintf(stderr, "Stack hasn't been allocated or has been partially allocated\n");
	  return -1;
	}

	return st->list->size;
}

/*
 * Intoarce 1 daca stiva este goala si 0 in caz contrar.
 */
unsigned int st_is_empty(stack_t *st)
{
	if (!st || !st->list) {
		fprintf(stderr, "Stack hasn't been allocated or has been partially allocated\n");
	  return -1;
	}

	if (st->list->size == 0) {
		return 1;
	}
	
	return 0;
}

void *st_peek(stack_t *st)
{
	if (!st || !st->list) {
		fprintf(stderr, "Stack hasn't been allocated or has been partially allocated\n");
	  return NULL;
	}

	return st->list->head->data;
}

void st_pop(stack_t *st)
{
	if (!st || !st->list || st->list->size == 0) {
		fprintf(stderr, "Stack hasn't been allocated correctly or is empty\n");
	  return;
	}

	ll_node_t *removed = ll_remove_nth_node(st->list, 0);
	free(removed->data);
	free(removed);
}

void st_push(stack_t *st, void *new_data)
{
	if (!st || !st->list) {
		fprintf(stderr, "Stack hasn't been allocated or has been partially allocated\n");
	  return;
	}

	ll_add_nth_node(st->list, 0, new_data);
}

void st_clear(stack_t *st)
{
	if (!st || !st->list || st->list->size == 0) {
		fprintf(stderr, "Stack already empty or hasn't been allocated\n");
	  return;
	}

	int size = st->list->size;
	for (int i = 0; i < size; i++) {
		st_pop(st);
	}
}

void st_free(stack_t *st)
{
	if (!st || !st->list) {
		fprintf(stderr, "Stack already free'd or hasn't been allocated\n");
	  return;
	}

	if (!st_is_empty(st)) {
		st_clear(st);
	}

	ll_free(&st->list);
	free(st);
}
