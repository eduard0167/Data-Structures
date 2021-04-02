#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Library.h"
#include "Hashtable.h"
#include "LinkedList.h"
#include "utils.h"

book_t *read_book(void)
{
  book_t *book = malloc(sizeof(book_t));
  DIE(!book, "malloc() failed for book\n");

  char buff[MAX_STRING_SIZE];

  fgets(buff, NAME_LENGTH, stdin);
  buff[strlen(buff) - 1] = '\0';
  book->author = strdup(buff);
  memset(buff, 0, MAX_STRING_SIZE);

  fgets(buff, TITLE_LENGTH, stdin);
  buff[strlen(buff) - 1] = '\0';
  book->title = strdup(buff);
  memset(buff, 0, MAX_STRING_SIZE);

  fgets(buff, YEAR_LENGTH, stdin);
  buff[strlen(buff) - 1] = '\0';
  book->year = atoi(buff);
  memset(buff, 0, MAX_STRING_SIZE);

  fgets(buff, STATUS_LENGTH, stdin);
  buff[strlen(buff) - 1] = '\0';
  book->status = strdup(buff);
  memset(buff, 0, MAX_STRING_SIZE);

  return book;
}

book_t **readBooks(unsigned int num_books)
{
  book_t **books = malloc(num_books * sizeof(book_t *));
  DIE(!books, "malloc() failed for books\n");

  for (int i = 0; i < num_books; i++) {
    books[i] = read_book();
  }

  return books;
}

static void my_ht_put(hashtable_t *ht, void *key, unsigned int key_size,
	void *value, unsigned int value_size)
{
  int i;
	for (i = 0; i < ht->hmax; i++) {
    ll_node_t *curr = ht->buckets[i]->head;
    printf("3\n");
    if (!curr) {
      break;
    }

		if (ht->compare_function(((info_t *)curr->data)->key, key) == 0) {
			info_t new;
      new.key = malloc(key_size);
      memcpy(new.key, key, key_size);

      new.value = malloc(value_size);
      memcpy(new.value, value, value_size);

      ll_add_nth_node(((info_t*)ht->buckets[i]->head->data)->value, 0, &new);
      ht->size++;
			return;
		}
	}
  printf("1\n");
  ht->buckets[i]->head = malloc(sizeof(ll_node_t));
  ht->buckets[i]->head->data = ll_create(sizeof(info_t));
  
  info_t new;
  new.key = malloc(key_size);
  memcpy(new.key, key, key_size);

  new.value = malloc(value_size);
  memcpy(new.value, value, value_size);

  ll_add_nth_node(((info_t*)ht->buckets[i]->head->data)->value, 0, &new);
  ll_add_nth_node(ht->buckets[i], 0, &new);

	ht->size++;
}

static void resizeHashtable(hashtable_t **library, unsigned int new_hmax)
{
	void *p = realloc((*library)->buckets, new_hmax * sizeof(linked_list_t *));
  DIE(!p, "malloc() for buckets failed\n");

  (*library)->buckets = p;

  for (int i = (*library)->hmax; i < new_hmax; i++) {
    (*library)->buckets[i] = ll_create(sizeof(info_t));
  }

	(*library)->hmax = new_hmax;
 
}

void fillLibrary(hashtable_t **library, book_t **books, unsigned int num_books)
{
  for (int i = 0; i < num_books; i++) {
    if ((1.0 * (*library)->size / (*library)->hmax) > 0.75 ) {
      resizeHashtable(library, 2 * (*library)->hmax);
    }
    ht_put(*library, books[i]->title, strlen(books[i]->title) + 1, books[i], sizeof(*books[i]));
  }
}

void fillLibrary_Authors(hashtable_t **library, book_t **books, unsigned int num_books)
{
  for (int i = 0; i < num_books; i++) {
    if ((1.0 * (*library)->size / (*library)->hmax) > 0.75 ) {
      resizeHashtable(library, 2 * (*library)->hmax);
    }
    my_ht_put(*library, books[i]->author, strlen(books[i]->author) + 1, books[i], sizeof(*books[i]));
  }
}

void printAuthor_Books(hashtable_t *library, char *author)
{
  unsigned int index = library->hash_function(author) % library->hmax;

	ll_node_t *curr = library->buckets[index]->head;

	while (curr) {
    printf("Author: %s\tTitle: %s\tYear: %u\tStatus: %s\n", ((book_t*)((info_t *)curr->data)->value)->author,
             ((book_t*)((info_t *)curr->data)->value)->title, ((book_t*)((info_t *)curr->data)->value)->year, ((book_t*)((info_t *)curr->data)->value)->status);
		curr = curr->next;
	}
}

void printLibrary(hashtable_t *library)
{
  for (int i = 0; i < library->hmax; i++) {
    if (library->buckets[i]->head) {
      ll_node_t *curr = library->buckets[i]->head;
      while (curr) {
        printf("Author: %s\tTitle: %s\tYear: %u\tStatus: %s\n", ((book_t*)((info_t *)curr->data)->value)->author,
             ((book_t*)((info_t *)curr->data)->value)->title, ((book_t*)((info_t *)curr->data)->value)->year, ((book_t*)((info_t *)curr->data)->value)->status);
        curr = curr->next;
      }
    }
  }
}


void removeBorrowed(hashtable_t *library)
{
  for (int i = 0; i < library->hmax; i++) {
    if (library->buckets[i]->head) {
      ll_node_t *curr = library->buckets[i]->head;
      while (curr) {
        if (!strcmp(((book_t*)((info_t *)curr->data)->value)->status, "Borrowed")) {
          ll_node_t *prev = curr;
          curr = curr->next;
          ht_remove_entry(library, (((book_t*)((info_t *)prev->data)->value)->title));
        } else {
          curr = curr->next;
        }

      }
    }
  }
}

void freeBooks(book_t ***books, unsigned int num_books)
{
  for (int i = 0; i < num_books; i++) {
    free((*books)[i]->author);
    free((*books)[i]->title);
    free((*books)[i]->status);

    free((*books)[i]);
  }

  free(*books);
  *books = NULL;
}