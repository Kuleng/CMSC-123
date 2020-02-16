/******************
	Tumpalan, John Karl  B.
	2018 - 02385
	Lab 08_ HashTable ADT
	CMSC 123 U-5L

**************/

#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>


int main(){

	char command;
	STRING key;
	STRING data;
	STRING result;

	uint tsize;
	HASH_TABLE_PTR H;
	
	// get table size then maxsize
	scanf("%d\n", &tsize); 
	H = createHashTable(tsize);
	// assume max key size is 20
	key = (STRING)malloc(sizeof(char)*20);
	key[0] = '\0';
	// assume max data size is 100
	data = (STRING)malloc(sizeof(char)*100);
	data[0] = '\0';

	while(1){
		scanf("%c ", &command);

		switch(command){
			case '+':
				scanf(" k:%s d:%s\n", key, data);
				printf("Inserting data %s with key %s\n", data, key);
				put(H, key, data);
				break;
			case '-':
				scanf(" k:%s d:%s\n", key, data);
				printf("Deleting data %s with key %s\n", data, key);
				result = erase(H, key, data); 
				// result is unused. print if u want
				printf("Result: %s\n", result);

				break;
			case '?':
				scanf(" k:%s d:%s\n", key, data);
				printf("Searching data with key: %s. Location: %p\n", key, find(H,key, data));
				// (nil) means NULL pointer
				break;
			case 'p':
				printf("Hash Table: \n");
				printTable(H);
				printf("\n");
				break;
			case 'E':
				printf("Hash table %s empty.\n", isEmpty(H)?"is":"is not");
				break;
			case 'F':
				printf("Hash table %s full.\n", isFull(H)?"is":"is not");
				break;
			case 'C':
				printf("Deleting all contents.\n");
				destroy(H);
				break;
			case 'Q':
				free(key); free(data);
				destroy(H); // ensure deletion
				free(H->list);
				free(H);
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}
	
	return 0;
}