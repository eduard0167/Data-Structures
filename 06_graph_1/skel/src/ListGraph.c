#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"
#include "utils.h"

list_graph_t *lg_create(int nodes)
{
	list_graph_t *graph = malloc(sizeof(list_graph_t));
	DIE(!graph, "Error in malloc() for graph\n");;

	graph->neighbors = malloc(nodes * sizeof(linked_list_t*));
	for (int i = 0; i < nodes; i++) {
		graph->neighbors[i] = ll_create(sizeof(int));
		DIE(!graph->neighbors[i], "Error in malloc() for neighbors list\n");
	}

	graph->nodes = nodes;
	return graph;
}

void lg_add_edge(list_graph_t* graph, int src, int* dest)
{
	if (!graph) {
		fprintf(stderr, "Graph hasn't been allocated\n");
		return;
	}

	unsigned int pos = graph->neighbors[src]->size;
	ll_add_nth_node(graph->neighbors[src], pos, dest);
}

int lg_has_edge(list_graph_t* graph, int src, int dest)
{
	if (!graph) {
		fprintf(stderr, "Graph hasn't been allocated\n");
		return -1;
	}

	ll_node_t *curr = graph->neighbors[src]->head;

	while (curr) {
		if ((*(int*)curr->data) == dest) {
			return 1;
		}
		curr = curr->next;
	}

	return 0;
}

linked_list_t *lg_get_neighbours(list_graph_t* graph, int node)
{
	if (!graph) {
		fprintf(stderr, "Graph hasn't been allocated\n");
		return NULL;
	}

	return graph->neighbors[node];
}

void lg_remove_edge(list_graph_t* graph, int src, int dest)
{
	if (!graph) {
		fprintf(stderr, "Graph hasn't been allocated\n");
		return;
	}

	ll_node_t *curr = graph->neighbors[src]->head;
	unsigned int pos = 0;

	while (curr) {
		if ((*(int*)curr->data) == dest) {
			ll_node_t *remove = ll_remove_nth_node(graph->neighbors[src], pos);
			free(remove->data);
			free(remove);
			return;
		}

		curr = curr->next;
		pos++;
	}
}

void lg_free(list_graph_t* graph)
{
	if (!graph) {
		fprintf(stderr, "Graph hasn't been allocated or already free'd\n");
		return;
	}

	for (int i = 0; i < graph->nodes; i++) {
		ll_free(&graph->neighbors[i]);
	}

	free(graph->neighbors);
	free(graph);
}