#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NMAX 256

int **read_matrix(int n, int m){
  int **mat = (int **)malloc(n * sizeof(int *));
  if(!mat){
    fprintf(stderr, "ERROR in malloc()\n");
    return NULL;
  }
  for(int i = 0; i < n; i++){
    mat[i] = (int *)malloc(m * sizeof(int));
    if(!mat[i]){
      fprintf(stderr, "ERROR in malloc()\n");
      
      while (i >= 0) {
        free(mat[i--]);
      }
      
      return NULL;
    }

    for(int j = 0; j < m; j++){
      scanf("%d", &mat[i][j]);
    }
  }

  return mat;
}

void print(int n, int m, int **mat){
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      printf("%d ", mat[j][i]);
    }
    printf("\n");
  }
}

void free_matrix(int n, int m, int **mat){
  for(int i = 0; i < n; i++){
    free(mat[i]);
  }
  free(mat);
}

int main(void){
  int n, m;
  scanf("%d%d", &n, &m);
  int **mat = read_matrix(n, m);

  print(n, m ,mat);

  free_matrix(n, m, mat);
  return 0;
}