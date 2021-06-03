#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "GraphUtils.h"

#define MAX_NODES 10

int main(void)
{
	list_graph_t* lg = lg_create(MAX_NODES);
	matrix_graph_t* mg = mg_create(MAX_NODES);

	int numbers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	printf("-------------------------------- Test ListGraph "
		"--------------------------------\n");
	/* Test add_edge_list_graph has_edge_list_graph */

	lg_add_edge(lg, numbers[0], &numbers[1]);
	lg_add_edge(lg, numbers[3], &numbers[2]);

	printf("#1:\nOutput: %d\nOutput asteptat: 1\n",
		lg_has_edge(lg, numbers[0], numbers[1]));

	printf("#2:\nOutput: %d\nOutput asteptat: 1\n",
		lg_has_edge(lg, numbers[3], numbers[2]));

	printf("#3:\nOutput: %d\nOutput asteptat: 0\n",
		lg_has_edge(lg, numbers[2], numbers[4]));

	/* Test remove_edge_list_graph */
	lg_remove_edge(lg, numbers[0], numbers[1]);
	printf("#4:\nOutput: %d\nOutput asteptat: 0\n",
		lg_has_edge(lg, numbers[0], numbers[1]));

	/* Test get_neighbours_list_graph */
	lg_add_edge(lg, numbers[0], &numbers[1]);
	lg_add_edge(lg, numbers[0], &numbers[2]);
	lg_add_edge(lg, numbers[0], &numbers[3]);
	lg_add_edge(lg, numbers[0], &numbers[4]);
	lg_add_edge(lg, numbers[1], &numbers[4]);
	lg_add_edge(lg, numbers[2], &numbers[3]);
	lg_add_edge(lg, numbers[4], &numbers[1]);

	linked_list_t* l = lg_get_neighbours(lg, numbers[0]);

	printf("#5:\n");
	printf("Output: ");
	ll_print_int(l);
	printf("\n");
	printf("Output asteptat: 1 2 3 4\n");

	printf("-------------------------------- Test MatrixGraph "
		"--------------------------------\n");
	/* test add edge_matrix_graph has_edge_matrix_graph */
	mg_add_edge(mg, numbers[0], numbers[1]);
	mg_add_edge(mg, numbers[3], numbers[2]);

	printf("#1:\nOutput: %d\nOutput asteptat: 1\n",
		mg_has_edge(mg, numbers[0], numbers[1]));

	printf("#2:\nOutput: %d\nOutput asteptat: 1\n",
		mg_has_edge(mg, numbers[3], numbers[2]));

	printf("#3:\nOutput: %d\nOutput asteptat: 0\n",
		mg_has_edge(mg, numbers[2], numbers[4]));

	/* test remove_edge_matrix_graph */
	mg_remove_edge(mg, numbers[0], numbers[1]);
	printf("#4:\nOutput: %d\nOutput asteptat: 0\n",
		mg_has_edge(mg, numbers[0], numbers[1]));

	lg_free(lg);
	mg_free(mg);
	return 0;
}