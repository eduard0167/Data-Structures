#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "GraphUtils.h"
#include "Queue.h"
#include "Stack.h"

#define MAX_NODES 8

void print_matrix_graph(matrix_graph_t* g)
{
	for (int i = 0; i < g->nodes; i++) {
		for (int j = 0; j < g->nodes; j++) {
			printf("%d ", g->matrix[i][j]);
		}
		printf("\n");
	}
}

void print_list_graph(list_graph_t* g)
{
	for (int i = 0; i < g->nodes; i++) {
		printf("%d --> ", i);
		ll_print_int(g->neighbors[i]);
	}
}

void dfs_list_graph(list_graph_t* lg, int node, int* color, int *parent, int* t_desc, int* t_fin)
{
	stack_t *stack = st_create(sizeof(int));

	int cont = 1;
	color[node] = 1;
	t_desc[node] = 1;

	st_push(stack, &node);

	while (!st_is_empty(stack)) {
		node = (*(int*)st_peek(stack));
		ll_node_t *curr = lg->neighbors[node]->head;

		while (curr) {
			if (!color[(*(int*)curr->data)]) {
				st_push(stack, curr->data);
				int new_node = (*(int*)curr->data);

				t_desc[new_node] = ++cont;
				color[new_node] = 1;
				parent[new_node] = node;
				break;
			}
			curr = curr->next;
		}

		if (!curr) {
			t_fin[node] = ++cont;
			color[node] = 2;
			st_pop(stack);
		}
	}

	/*		// Check algorithm
	for(int i = 0; i < MAX_NODES; i++) {
		printf("%d --> %d %d\t Parent: %d\n", i, t_desc[i], t_fin[i], parent[i]);
	}
	*/

	st_free(stack);
}

void dfs_matrix_graph(matrix_graph_t* mg, int node, int* color, int *parent, int* t_desc, int* t_fin)
{
	stack_t *stack = st_create(sizeof(int));

	int cont = 1;
	color[node] = 1;
	t_desc[node] = 1;

	st_push(stack, &node);

	while (!st_is_empty(stack)) {
		node = (*(int*)st_peek(stack));
		int find = 0;
		for (int j = 0; j < MAX_NODES; j++) {
			if (mg->matrix[node][j] && !color[j]) {
				st_push(stack, &j);

				t_desc[j] = ++cont;
				color[j] = 1;
				parent[j] = node;
				find = 1;
				break;
			}
		}

		if (!find) {
			t_fin[node] = ++cont;
			color[node] = 2;
			st_pop(stack);
		}
	}

	/* 		// Check algorithm
	for(int i = 0; i < MAX_NODES; i++) {
		printf("%d --> %d %d\t Parent: %d\n", i, t_desc[i], t_fin[i], parent[i]);
	}
	*/

	st_free(stack);
}

void bfs_list_graph(list_graph_t* lg, int node, int* color, int* parent)
{
	queue_t *queue = q_create(sizeof(int), MAX_NODES);

	int d[MAX_NODES] = {0};
	color[node] = 1;
	parent[node] = node;
	q_enqueue(queue, &node);

	while (!q_is_empty(queue)) {
		node = (*(int*)q_front(queue));
		ll_node_t *curr = lg->neighbors[node]->head;
		if (!curr) {
			break;
		}

		/*		// Check the algorithm
		printf("\n");
		for (int i = 0; i < MAX_NODES; i++) {
			printf("%d ", color[i]);
		}
		*/

		while (curr) {
			if (!color[(*(int*)curr->data)]) {
				q_enqueue(queue, curr->data);
				int new_node = (*(int*)curr->data);

				color[new_node] = 1;
				parent[new_node] = node;
				d[new_node] = d[node] + 1;
			}
			curr = curr->next;
		}

		color[node] = 2;
		q_dequeue(queue);
	}

		/*		// Check the algorithm
		printf("\n\n");
		for (int i = 0; i < MAX_NODES; i++) {
			printf("%d ", d[i]);
		}
		*/

	q_free(queue);
}

void bfs_matrix_graph(matrix_graph_t* mg, int node, int* color, int* parent)
{
	queue_t *queue = q_create(sizeof(int), MAX_NODES);

	int d[MAX_NODES] = {0};
	
	color[node] = 1;
	parent[node] = node;
	q_enqueue(queue, &node);

	while (!q_is_empty(queue)) {
		node = (*(int*)q_front(queue));

		/*		// Check the algorithm
		printf("\n");
		for (int i = 0; i < MAX_NODES; i++) {
			printf("%d ", color[i]);
		}
		*/

		for (int j = 0; j < MAX_NODES; j++) {
			if (mg->matrix[node][j] && !color[j]) {
				q_enqueue(queue, &j);

				color[j] = 1;
				parent[j] = node;
				d[j] = d[node] + 1;
			}
		}

		color[node] = 2;
		q_dequeue(queue);
	}

	 	/*	// Check the algorithm
		printf("\n");
		for (int i = 0; i < MAX_NODES; i++) {
			printf("%d ", d[i]);
		}
		*/

	q_free(queue);
}

// Calculeaza cea mai mica distanta intre oricare doua noduri din graf.
void floyd_warshall(matrix_graph_t *mg)
{
	float dist[MAX_NODES][MAX_NODES];

	for (int i = 0; i < MAX_NODES; i++) {
		for (int j = 0; j < MAX_NODES; j++) {
			if (mg->matrix[i][j]) {
				dist[i][j] = mg->matrix[i][j];
			} else {
				dist[i][j] = INFINITY;
			}
		}
		dist[i][i] = 0;
	}

	printf("\n\n");
	for (int k = 0; k < MAX_NODES; k++) {
		for (int i = 0 ; i < MAX_NODES; i++) {
			for (int j = 0; j < MAX_NODES; j++) {
				if (dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}

	/*			// CHECK THE ALGORITHM
	for (int i = 0; i < MAX_NODES; i++) {
		for (int j = 0; j < MAX_NODES; j++) {
			if (dist[i][j] == INFINITY) {
				printf("inf\t");
			} else {
				printf("%.0lf\t", dist[i][j]);
			}
		}
		printf("\n");
	}
	*/
}

void fill_matrix_graph(matrix_graph_t *mg, int *numbers)
{
  mg_add_edge(mg, numbers[0], numbers[1]);
  mg_add_edge(mg, numbers[1], numbers[2]);
  mg_add_edge(mg, numbers[1], numbers[5]);
  mg_add_edge(mg, numbers[1], numbers[6]);
  mg_add_edge(mg, numbers[2], numbers[1]);
  mg_add_edge(mg, numbers[2], numbers[4]);
  mg_add_edge(mg, numbers[2], numbers[5]);
  mg_add_edge(mg, numbers[3], numbers[1]);
  mg_add_edge(mg, numbers[3], numbers[7]);
  mg_add_edge(mg, numbers[4], numbers[2]);
  mg_add_edge(mg, numbers[5], numbers[1]);
  mg_add_edge(mg, numbers[5], numbers[7]);
  mg_add_edge(mg, numbers[6], numbers[4]);
  mg_add_edge(mg, numbers[6], numbers[5]);
  mg_add_edge(mg, numbers[6], numbers[7]);
  mg_add_edge(mg, numbers[7], numbers[6]);
}

void fill_list_graph(list_graph_t *lg, int *numbers)
{
  lg_add_edge(lg, numbers[0], &numbers[1]);
  lg_add_edge(lg, numbers[1], &numbers[2]);
  lg_add_edge(lg, numbers[1], &numbers[5]);
  lg_add_edge(lg, numbers[1], &numbers[6]);
  lg_add_edge(lg, numbers[2], &numbers[1]);
  lg_add_edge(lg, numbers[2], &numbers[4]);
  lg_add_edge(lg, numbers[2], &numbers[5]);
  lg_add_edge(lg, numbers[3], &numbers[1]);
  lg_add_edge(lg, numbers[3], &numbers[7]);
  lg_add_edge(lg, numbers[4], &numbers[2]);
  lg_add_edge(lg, numbers[5], &numbers[1]);
  lg_add_edge(lg, numbers[5], &numbers[7]);
  lg_add_edge(lg, numbers[6], &numbers[4]);
  lg_add_edge(lg, numbers[6], &numbers[5]);
  lg_add_edge(lg, numbers[6], &numbers[7]);
  lg_add_edge(lg, numbers[7], &numbers[6]);
}

static void mg_add_edge_floyd(matrix_graph_t* graph, int src, int dest, int cost)
{
	if (!graph) {
		fprintf(stderr, "Graph hasn't been allocated\n");
		return;
	}
	graph->matrix[src][dest] = cost;
}

void fill_floyd_matrix(matrix_graph_t *mg, int *numbers)
{
  mg_add_edge_floyd(mg, numbers[0], numbers[1], 1);
  mg_add_edge_floyd(mg, numbers[1], numbers[2], 4);
  mg_add_edge_floyd(mg, numbers[1], numbers[5], 1);
  mg_add_edge_floyd(mg, numbers[1], numbers[6], 3);
  mg_add_edge_floyd(mg, numbers[2], numbers[1], 4);
  mg_add_edge_floyd(mg, numbers[2], numbers[4], 1);
  mg_add_edge_floyd(mg, numbers[2], numbers[5], 2);
  mg_add_edge_floyd(mg, numbers[3], numbers[1], 2);
  mg_add_edge_floyd(mg, numbers[3], numbers[7], 3);
  mg_add_edge_floyd(mg, numbers[4], numbers[2], 1);
  mg_add_edge_floyd(mg, numbers[5], numbers[1], 4);
  mg_add_edge_floyd(mg, numbers[5], numbers[7], 1);
  mg_add_edge_floyd(mg, numbers[6], numbers[4], 5);
  mg_add_edge_floyd(mg, numbers[6], numbers[5], 1);
  mg_add_edge_floyd(mg, numbers[6], numbers[7], 2);
  mg_add_edge_floyd(mg, numbers[7], numbers[6], 1);
}