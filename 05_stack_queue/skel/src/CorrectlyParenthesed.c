#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Stack.h"

void checkParentheses(char *exp)
{
  stack_t *stack = st_create(sizeof(char));
  
  for (int i = 0; i < strlen(exp); i++) {
    if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[') {
      st_push(stack, &exp[i]);
      continue;
    }

    if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']') {
      // daca stiva este goala si se adauga o paranteaza "la dreata", aceasta nu
      // se va inchide niciodata
      if (st_is_empty(stack)) {
        printf("Not balanced\n");
        return;
      }

      if ((*(char*)st_peek(stack)) == '(' && exp[i] == ')') {
        st_pop(stack);
        continue;
      }

      if ((*(char*)st_peek(stack)) == '{' && exp[i] == '}') {
        st_pop(stack);
        continue;
      }

      if ((*(char*)st_peek(stack)) == '[' && exp[i] == ']') {
        st_pop(stack);
        continue;
      }
      
      break;
    }
  }

  // daca stiva este goala, inseamna ca nu au fost inchise toate parantezele
  if (!st_is_empty(stack)) {
    printf("Not balanced\n");
    return;
  }
  
  printf("Balanced\n");
  st_free(stack);
}

int main(void) {

  //    Test 1
  printf("\nOutput expected: Balanced\nOutput: ");
  char exp1[] = "([()[{([]()){}}[[]]]{}])[]({})";
  checkParentheses(exp1);

  //    Test 2
  printf("\nOutput expected: Not balanced\nOutput: ");
  char exp2[] = "([]({)})";
  checkParentheses(exp2);

  //    Test 3
  printf("\nOutput expected: Not balanced\nOutput: ");
  char exp3[] = "[{{}(())([]{";
  checkParentheses(exp3);


  //    Test 4
  printf("\nOutput expected: Balanced\nOutput: ");
  char exp4[] = "[()]{}{[()()]()}";
  checkParentheses(exp4);


  //    Test 5
  printf("\nOutput expected: Not balanced\nOutput: ");
  char exp5[] = "[(){}]]";
  checkParentheses(exp5);


  return 0;
}
