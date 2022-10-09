#include "hashtable.h"

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * String utility routines.
 */
#include <string.h>

/*
 * This creates a new hash table of the specified size and with
 * the given hash function and comparison function.
 */
HashTable *createHashTable(int size, unsigned int (*hashFunction)(void *),
                           int (*equalFunction)(void *, void *)) {
  int i = 0;
  HashTable *newTable = malloc(sizeof(HashTable));
  if (NULL == newTable) {
    fprintf(stderr, "malloc failed \n");
    exit(1);
  }
  newTable->size = size;
  newTable->buckets = malloc(sizeof(struct HashBucketEntry *) * size);
  if (NULL == newTable->buckets) {
    fprintf(stderr, "malloc failed \n");
    exit(1);
  }
  for (i = 0; i < size; i++) {
    newTable->buckets[i] = NULL;
  }
  newTable->hashFunction = hashFunction;
  newTable->equalFunction = equalFunction;
  return newTable;
}

/* Task 1.2 */
void insertData(HashTable *table, void *key, void *data) {
  // -- TODO --
  // HINT:
  // 1. Find the right hash bucket location with table->hashFunction.
  // 2. Allocate a new hash bucket entry struct.
  // 3. Append to the linked list or create it if it does not yet exist.
  int i = ((table->hashFunction(key) % table->size) + table->size) % table->size;
  HashBucketEntry *newEntry = malloc(sizeof(HashBucketEntry));
  newEntry->key = key;
  newEntry->data = data;
  if (table->buckets[i] == NULL) {
	  table->buckets[i] = newEntry;
  }
  else {
	  HashBucketEntry *headEntry = table->buckets[i];
	  while (headEntry->next != NULL) {
		  headEntry = headEntry->next;
	  }
	  headEntry->next = newEntry;
  }
}

/* Task 1.3 */
void *findData(HashTable *table, void *key) {
  // -- TODO --
  // HINT:
  // 1. Find the right hash bucket with table->hashFunction.
  // 2. Walk the linked list and check for equality with table->equalFunction.
  int i = ((table->hashFunction(key) % table->size) + table->size) % table->size;
  HashBucketEntry *headEntry = table->buckets[i];
	while (headEntry != NULL) {
		if (table->equalFunction(key, headEntry->key)) {
			return headEntry->data;
		}
		headEntry = headEntry->next;
	}
	return NULL;
}

/* Task 2.1 */
unsigned int stringHash(void *s) {
  // -- TODO --
  unsigned int sum = 0;
  while (*(char*)s) {
	  unsigned int intS = *(char*)s; 
	  sum *= 31;
	  sum += intS;
	  s++;
  }
  //fprintf(stderr, "need to implement stringHash\n");
  /* To suppress compiler warning until you implement this function, */
  return sum;
}

/* Task 2.2 */
int stringEquals(void *s1, void *s2) {
  // -- TODO --
  while (*(char*)s1 && *(char*)s2) {
	  if (*(char*)s1 != *(char*)s2) {
		  return 0;
	  }
	  s1++;
	  s2++;
  }
  if (*(char*)s1 || *(char*)s2) {
	  return 0;
  }
  else {
	  return 1;
  }
  //fprintf(stderr, "You need to implement stringEquals");
  /* To suppress compiler warning until you implement this function */
  return 0;
}
