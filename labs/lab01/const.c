#include <stdio.h>

int main(void) {
  int num1 = 2, num2 = 3; 

/*
  int *p = &num1; // pointer de tip int
  printf("p = %p\nnum1 = %p\t num2 = %p\n", p, &num1, &num2);
  //  p = 0x7ffda92aa5e8
  //  num1 = 0x7ffda92aa5e8	 num2 = 0x7ffda92aa5ec
  p = &num2;
  printf("p = %p\nnum1 = %p\t num2 = %p\n", p, &num1, &num2);
  //  p = 0x7ffda92aa5ec
  //  num1 = 0x7ffda92aa5e8	 num2 = 0x7ffda92aa5ec
*/

/* 
  int * const p = &num1; //point constant la un int variabil
  printf("p = %p\nnum1 = %p\t num2 = %p\n", p, &num1, &num2);
  p = &num2; //  assignment of read-only variable ‘p’
*/

/*
  int const *p = &num1; // pointer variabil catre un int constant
*/

/*
  int const * const p = &num1; // pointer constant catre un int constant
  p = &num2; // assignment of read-only variable ‘p’
*/
  return 0;
}