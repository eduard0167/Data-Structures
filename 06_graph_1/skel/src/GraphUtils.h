#ifndef __GRAPH_UTILS_H__
#define __GRAPH_UTILS_H__

#include "MatrixGraph.h"
#include "ListGraph.h"

void print_matrix_graph(matrix_graph_t* mg);
void print_list_graph(list_graph_t* lg);

void fill_matrix_graph(matrix_graph_t *mg, int *numbers);
void fill_list_graph(list_graph_t *lg, int *numbers);

void dfs_list_graph(list_graph_t* lg, int node, int* color, int *parent, int* t_desc, int* f_tin);
void dfs_matrix_graph(matrix_graph_t* mg, int node, int* color, int *parent, int* t_desc, int* f_tin);

void bfs_list_graph(list_graph_t* lg, int node, int* color, int* parent);
void bfs_matrix_graph(matrix_graph_t* mg, int node, int* color, int* parent);

void floyd_warshall(matrix_graph_t* mg);
void fill_floyd_matrix(matrix_graph_t *mg, int *numbers);
#endif  /* __GRAPH_UTILS_H__ */

