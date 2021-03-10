#include<stdio.h>
#include<stdlib.h>
#define NMAX 10

int main (void) {
  int (*v)[NMAX] = (int (*)[NMAX])malloc(3 * sizeof(*v));
  printf("%lu\n", sizeof(*v));
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 10; j++){
      scanf("%d", &v[i][j]);
    }
  }
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 10; j++){
      printf("%d ", v[i][j]);
    }
    printf("\n");
  }
  int *p = *v;
  printf("\n%p\n%p\n", *v, p);
  *v++;
  p++;
  printf("\n%p\n%p\n", *v, p);
  free(--v);
  return 0;
}