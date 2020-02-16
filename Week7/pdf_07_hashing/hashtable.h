#ifndef _CLOSED_HASHTABLE_H_
#define _CLOSED_HASHTABLE_H_

typedef unsigned int uint;
typedef char* STRING;
typedef char** STRING_ARRAY_PTR;

typedef struct hash_tag {
  // the current number of data elements
  // stored in the table
  uint size;
  // the size of the hash table
  // i.e. the number of lists
  uint tableSize;
  // an array of character pointers
  STRING_ARRAY_PTR list;
  // the hash function
  //  * a function that returns an int
  //  * a function that takes a character array
  //  * Sample usage;
  //  *   // declare some function that
  //  *   // follows required signature, e.g. int f(char* key){...}
  //  *   HASH_TABLE *ht = ...; //initialize hash table
  //  *   ht->hash = f; // assign function f as the hash function
  //  *   int index = ht->hash("19ritchie72"); // sample call
  int (*hash)(char* key, int i);
} HASH_TABLE;

// aliases which are used below and can be used in implementation
typedef HASH_TABLE* HASH_TABLE_PTR;

/*
 *  function: createHashTable
 *  requirements:
      * non-zero integer (tableSize)
 *  results:
      * creates a hash table
      * initializes fields
      * initializes array of strings
      * returns a non null HASH_TABLE_PTR
*/
HASH_TABLE_PTR createHashTable(uint tableSize);


// you know what these are
uint isEmpty(HASH_TABLE_PTR H);
uint isFull(HASH_TABLE_PTR H);

/*
 *  function: put
 *  requirements:
      * a non null HASH_TABLE_PTR
      * a non null NODE_PTR
      * non-full hash table
 *  results:
      * inserts node at the list at position identified by
        the hash value of the key.
*/
void put(HASH_TABLE_PTR H, STRING key, STRING data);

/*
 *  function: find
 *  requirements:
      * a non null HASH_TABLE_PTR
      * a non null string
      * non empty string
 *  results:
      * finds the node identified by key
      * returns the string data if found
      * returns NULL if not found
*/
STRING find(HASH_TABLE_PTR H, STRING key, STRING data);

/*
 *  function: erase
 *  requirements:
      * a non null HASH_TABLE_PTR
      * a non null string
      * non empty string
 *  results:
      * finds the node identified by key
      *   if found, delete the node and return the data
      *   otherwise, return NULL
*/
STRING erase(HASH_TABLE_PTR H, STRING key, STRING data);

/*
 *  function: destroy
 *  requirements:
      * a non null HASH_TABLE_PTR
 *  results:
      * deletes all nodes
      * frees all allocated memory for nodes
*/
void destroy(HASH_TABLE_PTR H);


// display the table
void printTable(HASH_TABLE_PTR H);


#endif
