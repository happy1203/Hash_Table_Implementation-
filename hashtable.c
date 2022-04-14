#include <stdlib.h>
#include "hashtable.h"
#include "cs136-trace.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// SUCCESS indicates successful execution of the function.
const int SUCCESS = 0;
// COLLISION indicates that a hash collision has occurred.
const int COLLISION = 1;
// ALREADY_STORED indicates that a value was already stored in the hashtable.
const int ALREADY_STORED = 2;
// NOT_STORED indicates that a value was not stored in the hashtable.
const int NOT_STORED = 3; 

// expt(b, n) gives the exponent of b^n 
int expt(int b, int n) {
  assert(n >= 0);
  int ex = 1; 
  for (int i = 1; i <= n; ++i) {
    ex *= b; 
  }
  return ex; 
}

// See hashtable.h for documentation
struct hashtable {
  // Your fields go here.
  char **str; 
  int len;
  int size;
  int (*hash_function)(const char *, int);
};

// See hashtable.h for documentation
struct hashtable *ht_create(int (*hash_func)(const char *, int),
                            int hash_length) {
  struct hashtable *ht = malloc(sizeof(struct hashtable));   
  ht->len = hash_length;
  ht->size = expt(2, hash_length);
  ht->str = malloc(ht->size * sizeof(char *));
  for (int i = 0; i < ht->size; ++i) {
    ht->str[i] = NULL; 
  }
  ht->hash_function = hash_func; 
  return ht;
}

// See hashtable.h for documentation
void ht_destroy(struct hashtable *ht) {
  for (int i = 0; i < ht->size; ++i) {
    free(ht->str[i]); 
  } 
  free(ht->str); 
  free(ht);
}

// See hashtable.h for documentation
int ht_insert(struct hashtable *ht, const char *str) {
  int idx = ht->hash_function(str, ht->len); 
  if (ht->str[idx] == NULL) {
    ht->str[idx] = malloc((strlen(str) + 1) * sizeof(char)); 
    strcpy(ht->str[idx], str); 
    return SUCCESS;
  } 
  else if (strcmp(str, ht->str[idx]) == 0) {
    return ALREADY_STORED; 
  } 
  else {
    return COLLISION; 
  }
}

// See hashtable.h for documentation
int ht_remove(struct hashtable *ht, const char *str) {
  int idx = ht->hash_function(str, ht->len); 
  if (ht->str[idx] == NULL || (strcmp(str, ht->str[idx]) != 0)) {
    return NOT_STORED; 
  } 
  else {
    free(ht->str[idx]); 
    ht->str[idx] = NULL;
    return SUCCESS; 
  }
}

// See hashtable.h for documentation
void ht_print(const struct hashtable *ht) {
  for (int i = 0; i < ht->size; ++i) {
    if (ht->str[i] == NULL) {
      printf("[%d]: [empty]\n", i); 
    } 
    else {
      printf("[%d]: %s\n", i, ht->str[i]); 
    }
  }
}
