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

void print_poz(int n, int m, int **mat, int x, int y){
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      if(i == x && y == j){
        printf("x ");
      } else {
        printf("%d ", mat[i][j]);
      }
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

  int x = 0, y = 0;
  printf("Initial position\n");
  print_poz(n, m, mat, x, y);

  printf("Move the robot: ");
  char buff[NMAX];
  scanf("%s", buff);
  char *oper = strdup(buff);
  int size = strlen(oper);
  for(int i = 0; i < size; i++){
    if(oper[i] == 'R'){
      y++;
    }
    if(oper[i] == 'L'){
      y--;
    }
    if(oper[i] == 'U'){
      x--;
    }
    if(oper[i] == 'D'){
      x++;
    }
  }
  printf("\n");

  print_poz(n, m , mat, x, y);

  free_matrix(n, m, mat);
  return 0;
}