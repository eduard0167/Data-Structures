#include <stdlib.h>
#include <string.h>

#include "Queue.h"
#include "utils.h"

queue_t *q_create(unsigned int data_size, unsigned int max_size)
{
	queue_t *queue = malloc(sizeof(queue_t));
	DIE(!queue, "malloc() for queue failed\n");

	queue->max_size = max_size;
	queue->data_size = data_size;
	queue->size = 0;
	queue->read_idx = 0;
	queue->write_idx = 0;

	queue->buff = malloc(max_size * sizeof(void*));
	DIE(!queue->buff, "malloc() for buff failed\n");

	return queue;
}

unsigned int q_get_size(queue_t *q)
{
	if (!q) {
		fprintf(stderr, "Queue hasn't been allocated\n");
	  return -1;
	}

	return q->size;
}

/*
 * Intoarce 1 daca stiva este goala si 0 in caz contrar.
 */
unsigned int q_is_empty(queue_t *q)
{
	if (!q) {
		fprintf(stderr, "Queue hasn't been allocated\n");
	  return -1;
	}

	if (q_get_size(q) > 0) {
		return 0;
	}

	return 1;
}

void *q_front(queue_t *q)
{
	if (!q || !q->buff) {
		fprintf(stderr, "Queue hasn't been allocated or has been partially allocated\n");
	  return 	NULL;
	}
	
	return q->buff[q->read_idx];
}

/* Functia intoarce true daca operatia s-a efectuat si false in caz contrar */
bool q_dequeue(queue_t *q)
{
	if (!q) {
		fprintf(stderr, "Queue hasn't been allocated\n");
	  return false;
	}

	if (q->size == 0) {
		fprintf(stderr, "Queue is already empty\n");
		return false;
	}

	free(q->buff[q->read_idx]);
	q->read_idx = (q->read_idx + 1) % q->max_size;
	q->size--;

	return true;
}

/* Functia intoarce true daca operatia s-a efectuat si false in caz contrar */
bool q_enqueue(queue_t *q, void *new_data)
{
	if (!q) {
		fprintf(stderr, "Queue hasn't been allocated\n");
	  return false;
	}

	if (q->size == q->max_size) {
		fprintf(stderr, "Queue is already full\n");
		return false;
	}

	q->buff[q->write_idx] = malloc(q->data_size);
	memcpy(q->buff[q->write_idx], new_data, q->data_size);

	q->write_idx = (q->write_idx + 1) % q->max_size;
	q->size++;

	return true;
}

void q_clear(queue_t *q)
{
	if (!q) {
		fprintf(stderr, "Queue hasn't been allocated\n");
	  return;
	}

	if (q->read_idx > q->write_idx) {

		for (int i = q->read_idx; i < q->max_size; i++) {
			free(q->buff[i]);
		}
		for (int i = 0; i < q->write_idx; i++) {
			free(q->buff[i]);
		}

	} else {

		for (int i = q->read_idx; i < q->write_idx; i++) {
			free(q->buff[i]);
		}

	}

	q->read_idx = 0;
	q->write_idx = 0;
}

void q_free(queue_t *q)
{
	if (!q) {
		fprintf(stderr, "Queue hasn't been allocated\n");
	  return;
	}

	if (!q_is_empty(q)) {
		q_clear(q);
	}

	free(q->buff);
	free(q);
}
