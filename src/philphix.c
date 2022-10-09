/*
 * Include the provided hash table library.
 */
#include "hashtable.h"

/*
 * Include the header file.
 */
#include "philphix.h"

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Character utility routines.
 */
#include <ctype.h>

/*
 * String utility routines.
 */
#include <string.h>

/*
 * This hash table stores the dictionary.
 */
HashTable *dictionary;

/*
 * The MAIN routine.  You can safely print debugging information
 * to standard error (stderr) as shown and it will be ignored in 
 * the grading process.
 */
#ifndef _PHILPHIX_UNITTEST
int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Specify a dictionary\n");
    return 1;
  }
  /*
   * Allocate a hash table to store the dictionary.
   */
  fprintf(stderr, "Creating hashtable\n");
  dictionary = createHashTable(0x61C, &stringHash, &stringEquals);

  fprintf(stderr, "Loading dictionary %s\n", argv[1]);
  readDictionary(argv[1]);
  fprintf(stderr, "Dictionary loaded\n");

  fprintf(stderr, "Processing stdin\n");
  processInput();

  /*
   * The MAIN function in C should always return 0 as a way of telling
   * whatever program invoked this that everything went OK.
   */
  return 0;
}
#endif /* _PHILPHIX_UNITTEST */

/* Task 3 */
void readDictionary(char *dictName) {
  // -- TODO --
  int len = 1000000;
  FILE *fp = fopen(dictName,"r");
  while(1) {
	  char *key = (char*)malloc(sizeof(char) * len);
	  char *data = (char*)malloc(sizeof(char) * len);
	  if (fscanf(fp, "%s%s", key, data) == EOF) {
		  break;
	  }
	  insertData(dictionary, key, data);
	  //free(key);
	  //free(data);
  }
  fclose(fp);
  //fprintf(stderr, "You need to implement readDictionary\n");
}

/* Task 4 */
void processInput() {
  // -- TODO --
  int len = 1000000;
  char *chars = (char*)malloc(sizeof(char) * len);
  int c;
  int pos = 0;
  while((c = getchar()) != EOF || strlen(chars) != 0) {
  //while ((c = getchar()) != EOF) {
  //char *chars = (char*)malloc(sizeof(char) * len);
	  if (isalpha(c) || isdigit(c)) {
		  *(chars + pos) = c;
		  pos++;
		  continue;
	  }
	  //putchar(c);
	  *(chars + pos) = '\0';
	  pos = 0;
	  char *cp_chars = (char*)malloc(sizeof(char) * len);
	  strcpy(cp_chars, chars);
	  
	  char *dict_data = findData(dictionary, chars);
	  if (dict_data != NULL) {
		  processOutput(dict_data, c, chars, cp_chars);
		  continue;
	  }
	  
	  int i;
	  for (i = 1; i < strlen(chars); i++) {
		  *(chars + i) = tolower(*(chars + i));
	  }
	  dict_data = findData(dictionary, chars);
	  if (dict_data != NULL) {
		  processOutput(dict_data, c, chars, cp_chars);
		  continue;
	  }

	 *(chars) = tolower(*(chars));
	  dict_data = findData(dictionary, chars);
	  if (dict_data != NULL) {
		  processOutput(dict_data, c, chars, cp_chars);
		  continue;
	  }
	  processOutput(cp_chars, c, chars, cp_chars);
  }
  free(chars);
  //fprintf(stderr, "You need to implement processInput\n");
}

void processOutput(char *dict_data, int c, char *chars, char *cp_chars) {
	printf("%s", dict_data);
	if (c != EOF) {
		printf("%c", c);
	}
	//printf("%s%c", dict_data, c);
	memset(chars, 0, sizeof(chars));
	free(cp_chars);
}
