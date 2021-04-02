#ifndef __LIBRARY_H__
#define __LIBRARY_H__

#include "Hashtable.h"

#define MAX_STRING_SIZE	256
#define NAME_LENGTH 128
#define TITLE_LENGTH 256
#define YEAR_LENGTH 6
#define STATUS_LENGTH 14 // On the shelf / Borrowed
#define MAX_CAPACITY 512 // Capacity of hashtable
 
typedef struct book {
  char *title;
  char *author;
  unsigned int year;
  char *status;
} book_t;

book_t *read_book(void);
book_t **readBooks(unsigned int num_books);
void printLibrary(hashtable_t *library);
void fillLibrary(hashtable_t **library, book_t **books, unsigned int num_books);
void fillLibrary_Authors(hashtable_t **library, book_t **books, unsigned int num_books);
void printAuthor_Books(hashtable_t *library, char *author);
void removeBorrowed(hashtable_t *library);

void freeBooks(book_t ***books, unsigned int num_books);


#endif