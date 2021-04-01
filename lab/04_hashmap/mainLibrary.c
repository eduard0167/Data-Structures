#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashtable.h"
#include "Library.h"
#include "utils.h"

int main(void) {
  unsigned int num_books;
  scanf("%d", &num_books);

  // Task1
  printf("\nTask 1\n");

  book_t **books = readBooks(num_books);
  
  hashtable_t *library = ht_create(5, hash_function_string, compare_function_strings);
  fillLibrary(&library, books, num_books);
  printLibrary(library);

  // Task 2
  printf("\nTask 2\n");

  book_t *book = ht_get(library, "The Lord of the Rings");
  if (!book) {
     fprintf(stderr, "Can't find the book\n");
  } else {
    printf("Author: %s\tTitle: %s\tYear: %u\tStatus: %s\n", book->author,
             book->title, book->year, book->status);
  }
  // Task 3 - Pentru a extrage din hashtable toate cartile unui autor, fara a parcurge
  // tot ht, avem nevoie de un ht cu cheia numele autorului, iar toate intrarile cu aceeasi
  // cheie, se vor stoca in aceeasi lista, ceea ce ne permite sa afisam toate cartile unui 
  // autor prin simpla parcurgerea unei liste. (my_ht_put)
  printf("\nTask 3\n");

  hashtable_t *new_library = ht_create(100, hash_function_string, compare_function_strings);
  fillLibrary_Authors(&new_library, books, num_books);
  printLibrary(new_library);
  printf("\n");
//  printAuthor_Books(new_library, "George Orwell");

  // Task 4 
  printf("\nTask 4\n");

  removeBorrowed(library);
  
  book = ht_get(library, "Brave New Wolrd");
  if (!book) {
     fprintf(stderr, "Can't find the book\n");
  } else {
    printf("Author: %s\tTitle: %s\tYear: %u\tStatus: %s\n", book->author,
             book->title, book->year, book->status);
  }

  book = ht_get(library, "Animal farm");
  if (!book) {
     fprintf(stderr, "Can't find the book\n");
  } else {
    printf("Author: %s\tTitle: %s\tYear: %u\tStatus: %s\n", book->author,
             book->title, book->year, book->status);
  }

  // Bonus
  printf("\nBonus\n");
  unsigned int add_books;
  scanf("%d", &add_books);

  book_t **new_books = readBooks(add_books);

  fillLibrary(&library, new_books, add_books);
  printLibrary(library);

  freeBooks(&books, num_books);
  freeBooks(&new_books, add_books);
  ht_free(new_library);
  ht_free(library);
  return 0;
}