#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListGraph.h"
#include "Queue.h"
#include "Stack.h"
#include "utils.h"


#define MAX_NODES	100
#define INF		0x3f3f3f3f

// Detectarea componentelor conexe - DFS
static void dfs_connected_comps(list_graph_t *lg,	int node,	int *visited,	linked_list_t *component)
{
	stack_t *stack = st_create(sizeof(int));

	visited[node] = 1;
	st_push(stack, &node);
	ll_add_nth_node(component, 0, &node);

	while (!st_is_empty(stack)) {
		node = (*(int*)st_peek(stack));
		ll_node_t *curr = lg->neighbors[node]->head;

		while (curr) {
			if (!visited[(*(int*)curr->data)]) {
				st_push(stack, curr->data);
				ll_add_nth_node(component, 0, curr->data);
				visited[(*(int*)curr->data)] = 1;
				break;
			}

			curr = curr->next;
		}

		if (!curr) {
			visited[node] = 2;
			st_pop(stack);
		}
	}

	st_free(stack);
}

static linked_list_t **connected_components(list_graph_t *lg, int *visited, unsigned int *num_comp)
{
	linked_list_t **comps = malloc(lg->nodes * sizeof(*comps));
	DIE(!comps, "malloc comps failed");

	for (int i = 0; i < lg->nodes; i++) {
		if (!visited[i]) {
			comps[*num_comp] = ll_create(sizeof(int));
			dfs_connected_comps(lg, i, visited, comps[*num_comp]);

			(*num_comp)++;
		}
	}

	return comps;
}

// Sortare topologica - DFS
static void dfs_topo_sort(list_graph_t *lg, int node, int *visited, linked_list_t *sorted)
{
	stack_t *stack = st_create(sizeof(int));
	st_push(stack, &node);
	visited[node] = 1;

	while (!st_is_empty(stack)) {
		node = (*(int*)st_peek(stack));
		ll_node_t *curr = lg->neighbors[node]->head;

		while (curr) {
			if (!visited[(*(int*)curr->data)]) {
				st_push(stack, curr->data);
				int new_node = (*(int*)curr->data);

				visited[new_node] = 1;	
				break;
			}
			curr = curr->next;
		}

		if (!curr) {
			ll_add_nth_node(sorted, 0, &node);
			visited[node] = 2;
			st_pop(stack);
		}
	}

	st_free(stack);
}

static linked_list_t *topo_sort(list_graph_t *lg, int *visited)
{
	linked_list_t *sorted = ll_create(sizeof(int));

	for (int i = 0; i < lg->nodes; i++) {
		if (!visited[i]) {
			dfs_topo_sort(lg, i, visited, sorted);
		}
	}

	return sorted;
}

// Gasirea drumurilor cele mai scurte dintre un nod si toate celalte dintr-un graf - BFS
static void min_path(list_graph_t *lg, int start, int *dist)
{
	queue_t *queue = q_create(sizeof(int), MAX_NODES);

	int visited[MAX_NODES] = {0};
	visited[start] = 1;
	dist[start] = 0;
	q_enqueue(queue, &start);

	while (!q_is_empty(queue)) {
		int node = (*(int*)q_front(queue));
		ll_node_t *curr = lg->neighbors[node]->head;
		if (!curr) {
			break;
		}

		while (curr) {
			if (!visited[(*(int*)curr->data)]) {
				q_enqueue(queue, curr->data);
				int new_node = (*(int*)curr->data);

				visited[new_node] = 1;
				dist[new_node] = dist[node] + 1;
			}

			curr = curr->next;
		}

		visited[node] = 2;
		q_dequeue(queue);
	}

	q_free(queue);
}

// Verificare daca un graf este bipartit - BFS
static int check_bipartite(list_graph_t *lg, int *color)
{
	queue_t *queue = q_create(sizeof(int), MAX_NODES);

	int node = 0;
	color[node] = 1;
	q_enqueue(queue, &node);

	while (!q_is_empty(queue)) {
		node = (*(int*)q_front(queue));
		ll_node_t *curr = lg->neighbors[node]->head;

		while (curr) {
			int new_node = (*(int*)curr->data);
			if (!color[new_node]) {
				color[new_node] = color[node] % 2 + 1;
				q_enqueue(queue, curr->data);
			}

			if (color[new_node] == color[node]) {
				q_free(queue);
				return 0;
			}

			curr =  curr->next;
		}

		q_dequeue(queue);
	}

	q_free(queue);
	return 1;
}

// ------------------ TEST FUNCTIONS -------------------

static void test_connected_comp(void)
{
	unsigned int num_comps = 0, i, nodes, edges;
	int x, y;
	int visited[MAX_NODES] = {0};
	list_graph_t *lg;
	linked_list_t **comps;

	printf("UNDIRECTED graph for the connected components problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}

	comps = connected_components(lg, visited, &num_comps);

	printf("Found %d connected components:\n", num_comps);
	for (i = 0; i != num_comps; ++i) {
		ll_print_int(comps[i]);
		ll_free(comps + i);
	}
	printf("\n");

	free(comps);
	lg_free(lg);
}

static void test_topo_sort(void)
{
	unsigned int i, nodes, edges;
	int x, y;
	int visited[MAX_NODES] = {0};
	list_graph_t *lg;
	linked_list_t *sorted;

	printf("DIRECTED graph for the topological sort problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
	}

	sorted = topo_sort(lg, visited);

	printf("Topologically sorted nodes:\n");
	ll_print_int(sorted);
	printf("\n");

	ll_free(&sorted);
	lg_free(lg);
}

static void test_min_dist(void)
{
	unsigned int i, nodes, edges;
	int x, y;
	int dist[MAX_NODES] = {0};
	list_graph_t *lg;

	printf("UNDIRECTED graph for the minimum distance problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}

	for (i = 0; i != nodes; ++i)
		dist[i] = INF;

	min_path(lg, 0, dist);

	printf("Minimum distances to node 0:\n");
	for (i = 0; i != nodes; ++i)
		printf("%u: %d\n", i, dist[i]);
	printf("\n");

	lg_free(lg);
}

static void test_bipartite(void)
{
	unsigned int i, nodes, edges;
	int color[MAX_NODES] = {0};
	int x, y;
	list_graph_t *lg;

	printf("UNDIRECTED graph for the bipartite graph problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}
	
	if (check_bipartite(lg, color)) {
		printf("Nodes with colour 1:\n");
		for (int i = 0; i < lg->nodes; ++i)
			if (color[i] == 1)
				printf("%d ", i);
		printf("\nNodes with colour 2:\n");
		for (int i = 0; i < lg->nodes; ++i)
			if (color[i] == 2)
				printf("%d ", i);
		printf("\n");
	} else
		printf("The graph is not bipartite\n");

	lg_free(lg);
}

int main(void)
{
	/* Ex 1 */
	test_connected_comp();

	/* Ex 2 */
	test_topo_sort();

	/* Ex 3 */
	test_min_dist();

	/* Ex 4 */
	test_bipartite();

	return 0;
}
