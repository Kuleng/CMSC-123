/******************
	Tumpalan, John Karl  B.
	2018 - 02385
	Lab 08_ HashTable ADT
	CMSC 123 U-5L

**************/

#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//insert other headers here

void printTable(HASH_TABLE_PTR H){
	if(isEmpty(H)) {
		printf("*empty\n");
		return;
	}

	for(int index=0; index<H->tableSize; index++){
		printf("Cell#%d: ", index);
		if(H->list[index]){
			printf("%s\n", H->list[index]);
		}else{
			printf("*empty*\n");
		}
	}
}

int hashFunction2(char *key, int i){
	// int index = key[0] + key[strlen(key)/2];
	int index = 0; 

	for(int i = 0; i < strlen(key)/2; i++){
		index += (key[i]); //Sum of all ascii values for truncated key (truncated to half)
	}

	return index;
}


int hashFunction1(char *key, int i){
	// int index = key[0] + key[strlen(key)-1];
		
	int index= 0;

	for(int i = 0; i < strlen(key); i++){
		index += (key[i]); //Sum of all ascii values of the characters of the whole key
	}

	if(i > 0){
		index = (index + (i*hashFunction2(key, i)));
	}

	return index;
}

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
HASH_TABLE_PTR createHashTable(uint tableSize){
	HASH_TABLE_PTR newHashTable = (HASH_TABLE_PTR)malloc(sizeof(HASH_TABLE));
	newHashTable->size = 0;
	newHashTable->tableSize = tableSize;
	newHashTable->list = (STRING_ARRAY_PTR)malloc(sizeof(STRING)*tableSize);
	for(int i = 0; i < newHashTable->tableSize; i++){
		newHashTable->list[i] = '\0';
	}
	newHashTable->hash = hashFunction1;

	return newHashTable;
}


// you know what these are
uint isEmpty(HASH_TABLE_PTR H){
	if (H->size == 0) return 1;
	return 0;
}
uint isFull(HASH_TABLE_PTR H){
	if (H->size >= H->tableSize) return 1;
	return 0;
}

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
void put(HASH_TABLE_PTR H, STRING key, STRING data){
	
	if(!isFull(H)){												//If the HTable is not yet full
		int iterations = 0;										//Insert based on the hashed index
		int index = H->hash(key, iterations)%H->tableSize;

		while(H->list[index] != NULL && iterations < H->tableSize){
			index = H->hash(key, ++iterations)%H->tableSize;
		}
		
		char *newString = (char*)malloc(sizeof(char)*strlen(data)); //Create a new dynamic string
		strcpy(newString, data);									//Copy the contents of data to the new dynamic string
																	//Point the char pointer ot the Htable index to the new string
		H->list[index] = newString;
		H->size++;										//Increment size
	}else{
		printf("HASH TABLE IS EMPTY/FULL.\n");
	}
}

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
STRING find(HASH_TABLE_PTR H, STRING key, STRING data){
	if(!isEmpty(H)){
		int iterations = 0;
		int index = H->hash(key, iterations)%H->tableSize;

		while(1){
			if(H->list[index] == NULL){									//If the index is null or empty, continue iteration
				index = H->hash(key, ++iterations)%H->tableSize;		//Increment iteration count
				continue;
			}
			else if (strcmp(H->list[index], data) == 0) break; 			//If the data and the hashed index has the same value of data, break
			else if (iterations >= H->tableSize) break;					// If the iteration count exceeded the table size, break
			else index = H->hash(key, ++iterations)%H->tableSize;		//If it has a data but is not the same with the searched string, recompute index
		}

		if(iterations >= H->tableSize) return NULL;

		return H->list[index];
	}else{
		printf("HASH TABLE IS EMPTY/FULL.\n");
	}
}

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

STRING erase(HASH_TABLE_PTR H, STRING key, STRING data){
	if(!isEmpty(H)){
		int iterations = 0;											//If the hash table is not empty
		int index = H->hash(key, iterations)%H->tableSize;			//Insert based on the hashed index


		while(1){
			if(H->list[index] == NULL){								//If the index is null or empty, continue iteration
				index = H->hash(key, ++iterations)%H->tableSize;	//Increment iteration count
				continue;
			}
			else if (strcmp(H->list[index], data) == 0) break;		//If the data and the hashed index has the same value of data, break
			else if (iterations >= H->tableSize) break;				// If the iteration count exceeded the table size, break
			else index = H->hash(key, ++iterations)%H->tableSize;	//If it has a data but is not the same with the searched string, recompute index

		}

		if(iterations >= H->tableSize) return NULL;				//If the iteration exceeded the limit, it means the data has not been found

		STRING dataToDelete = (STRING) malloc(sizeof(char)*strlen(H->list[index]));		//Create a new string to store the deleted string
		strcpy(dataToDelete, H->list[index]);

		free(H->list[index]);					//Free the hash table index of the string to be deleted
		H->list[index] = NULL;					//initialize to NULL
		H->size--;								//Decrement size

		return dataToDelete;
	}else{
		printf("HASH TABLE IS EMPTY/FULL.\n");
	}
}

/*
 *  function: destroy
 *  requirements:
      * a non null HASH_TABLE_PTR
 *  results:
      * deletes all nodes
      * frees all allocated memory for nodes
*/
void destroy(HASH_TABLE_PTR H){
	for(int i = 0; i < H->tableSize; i++){ //Continuous erase indeces
		free(H->list[i]);
		H->list[i] = NULL;
	}

	free(H->list);
	H = NULL;
}
