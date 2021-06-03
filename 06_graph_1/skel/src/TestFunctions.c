#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "GraphUtils.h"

#define MAX_NODES 8

int main(void)
{
	int color[MAX_NODES] = {0}, parent[MAX_NODES] = {0}, t_dest[MAX_NODES] = {0}, t_fin[MAX_NODES] = {0};
	list_graph_t* lg = lg_create(MAX_NODES);
	matrix_graph_t* mg = mg_create(MAX_NODES);

	int numbers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};

  fill_list_graph(lg, numbers);  
  printf("List representation:\n");
  print_list_graph(lg);
  
  fill_matrix_graph(mg, numbers);
  printf("\nMatrix representation:\n");
  print_matrix_graph(mg);

  //        TEST FOR BFS

  bfs_list_graph(lg, 0, color, parent);
  for (int i = 0; i < MAX_NODES; i++){
    parent[i] = 0;
    color[i] = 0;
  }
  printf("\n\n\n");
  bfs_matrix_graph(mg, 0, color, parent);

  //        TEST FOR DFS

  dfs_list_graph(lg, 0, color, parent, t_dest, t_fin);
  for (int i = 0; i < MAX_NODES; i++){
    parent[i] = 0;
    color[i] = 0;
    t_fin[i] = 0;
    t_dest[i] = 0;
  }
  printf("\n\n\n");
  
  dfs_matrix_graph(mg, 0, color, parent, t_dest, t_fin);

	lg_free(lg);
	mg_free(mg);

  //          TEST FOR FLOYD WARSHALL
  mg = mg_create(MAX_NODES);
  fill_floyd_matrix(mg, numbers);
  printf("\nFLoyd Marshal matrix:\n");
  print_matrix_graph(mg);
  printf("\n\n\n");

  floyd_warshall(mg);

	mg_free(mg);
	return 0;
}
