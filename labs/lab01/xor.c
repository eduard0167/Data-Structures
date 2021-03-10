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

void print_matrix(int n, int m, const int **mat){
  for (int i = 0; i < n ; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d ", mat[i][j]);
    }
    printf("\n");
  }
}

int xor_line(int n, int m, int **mat){
  int sum = 1;
  for (int i = 0; i < m; i++) {
    sum = sum ^ mat[n][i];
  }

  return sum;
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
  //print_matrix(n, m, mat);

  int max = 0;
  for (int i = 0; i < n; i++) {
    int line = xor_line(i, m, mat);
    if (line > max) {
      max = line;
    }
  }

  printf("%d\n", max);
  
  free_matrix(n, m, mat);
  return 1;
}
