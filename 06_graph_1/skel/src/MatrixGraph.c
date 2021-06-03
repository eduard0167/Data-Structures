#include <stdio.h>
#include <stdlib.h>

#include "MatrixGraph.h"
#include "utils.h"
/**
 * Initializeaza graful cu numarul de noduri primit ca parametru si aloca
 * memorie pentru matricea de adiacenta a grafului.
 */
matrix_graph_t *mg_create(int nodes)
{
	matrix_graph_t *graph = malloc(sizeof(matrix_graph_t));
	DIE(!graph, "Error in calloc() for graph\n");

	graph->matrix = calloc(nodes, sizeof(int*));
	DIE(!graph->matrix, "Error in calloc() for matrix\n");
	for (int i = 0; i < nodes; i++) {
		graph->matrix[i] = calloc(nodes, sizeof(int));
	}
	
	graph->nodes = nodes;
	return graph;
}

/* Adauga o muchie intre nodurile sursa si destinatie */
void mg_add_edge(matrix_graph_t* graph, int src, int dest)
{
	if (!graph) {
		fprintf(stderr, "Graph hasn't been allocated\n");
		return;
	}

	graph->matrix[src][dest] = 1;
}

/* Returneaza 1 daca exista muchie intre cele doua noduri, 0 in caz contrar */
int mg_has_edge(matrix_graph_t* graph, int src, int dest)
{
	if (!graph) {
		fprintf(stderr, "Graph hasn't been allocated\n");
		return -1;
	}

	return graph->matrix[src][dest];
}

/* Elimina muchia dintre nodurile sursa si destinatie */
void mg_remove_edge(matrix_graph_t* graph, int src, int dest)
{
	if (!graph) {
		fprintf(stderr, "Graph hasn't been allocated\n");
		return;
	}

	graph->matrix[src][dest] = 0;
}

/* Elibereaza memoria folosita de matricea de adiacenta a grafului */
void mg_free(matrix_graph_t* graph)
{
	if (!graph) {
		fprintf(stderr, "Graph hasn't been allocated or already free'd\n");
		return;
	}

	for (int i = 0; i < graph->nodes; i++) {
		free(graph->matrix[i]);
	}
	free(graph->matrix);
	free(graph);
}
