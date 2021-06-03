#include<stdio.h>
#include<stdlib.h>

int **alloc_matrix(int n, int m){
  int **mat = (int **)malloc(n * sizeof(int *));
  if (!mat) {
    fprintf(stderr, "ERROR in malloc()\n");
    return NULL;
  }

  for(int i = 0; i < n; i++){
    mat[i] = (int *)malloc(m * sizeof(int));
    if (!mat[i]) {
      fprintf(stderr, "ERROR in malloc()\n");

      while (i >= 0) {
        free(mat[i--]);
      }

      return NULL;
    }
  }

  return mat;
}

void read_matrix(int n, int m, int **mat){
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &mat[i][j]);
    }
  }
}

int find(int n, int m, int **mat, int elem, int *x, int *y){
  int min = mat[0][0], max = mat[n - 1][m - 1];
  if (min > elem || elem > max) { // element can't be in matrix
    return 0;
  }

  int i = 0, j = m - 1;
  while (i < n && j >= 0) {
    if (mat[i][j] == elem) {
      *x = i;
      *y = j;
      return 1;
    }

    if (mat[i][j] < elem) {
      i++;
    } else {
      j--;
    }
  }

  return 0;
}

void free_matrix(int n, int m, int **mat){
  for (int i = 0; i < n; i++) {
    free(mat[i]);
  }
  free(mat);
}

int main(void){
  int n, m;
  scanf("%d%d", &n, &m);

  int **mat = alloc_matrix(n, m);
  if (!mat) {
    fprintf(stderr, "ERROR in malloc()\n");
    return -1;
  }

  read_matrix(n, m, mat);
  
  int element;
  scanf("%d", &element);

  int x = 0, y = 0; 
  if (find(n, m, mat, element, &x, &y)) {
    printf("True, found at pozition (%d, %d)\n", x, y);
  } else {
    printf("False\n");
  }
  
  free_matrix(n, m, mat);
  return 1;
}
