/*
Tumpalan, John Karl B.
Exercise 01 - Diagnostics
CMSC 123 - Data Structures
August 9, 2019
*/

#include "list.h"
#include <stdio.h>
// include other headers you need
#include <stdlib.h>
// implement each function in list.h here

NODE* createNode(int data){
	NODE *newNode = (NODE*) malloc(sizeof(NODE));
	newNode->value = data;
	newNode->next = NULL;

	return newNode;
}

LIST* createList(int maxLength){
	LIST *newList = (LIST*)malloc(sizeof(LIST));
	newList->head = NULL;
	newList->tail = NULL;
	newList->length = 0;
	newList->maxLength = maxLength;

	return newList;
}

int isFull(LIST *L){
	return (L->length == L->maxLength) ? 1 : 0;
}

int isEmpty(LIST *L){
	return (L->length == 0) ? 1 : 0;
}

void insertAt(LIST *L, int index, NODE* node){
	if (L->length == L->maxLength){ //Full list catcher
		printf("List must not be full\n");
	}else if(index < 0 && index > L->length){ //Out of range index catcher
		printf("Index must be between 0 and list length\n");
	}else{
		NODE *tempNode; //temporary pointer
		NODE *nodeHolder; //will hold the address of node before the target index
		if (index == 0){ //catches the instance of new node becoming the new head
			node->next = L->head;
			L->head = node;
		}
		else{ //Main algorithm, catches index 1 up to list length
			tempNode = L-> head;
			for (int a = 0; a < L->length-1; a++){
				if (a == index-1){ //breaks the loop if the node before the target index is found
					nodeHolder = tempNode;
					break;
				}
				tempNode = tempNode->next;
			}

			node->next = nodeHolder->next;
			tempNode->next = node;
		}
		L->length ++; //Increments the list length/size
	}
}

int deleteAt(LIST *L, int index){
	int deletedValue;

	if (L->length == 0){ //catches empty list instance
		printf("List must not be empty!\n");
	}else if(index < 0 && index > L->length - 1){ //catches invalid index instance
		printf("Index must be between 0 and list length\n");
	}else{ //Main algorithm, catches 1 to length - 1 indeces
		NODE *tempNode = L->head;
		NODE *deletionNode;

		if (index == 0){ //re-assigns the head then deletes the past head
			deletionNode = L->head;
			L->head = deletionNode->next;
			free(deletionNode);
		}else{ //saves the address of the node to be deleted and the node before it.
			for (int a = 0; a < L->length-1; a++){
				if (a == index-1){
					deletionNode = tempNode->next;
					break;
				}
				tempNode = tempNode->next;
			}

			tempNode->next = deletionNode->next;
			deletedValue = deletionNode->value;
			free(deletionNode); //deletion
		}
		L->length --;
	}

	return deletedValue;
}

void clear(LIST *L){
	if (L->length == 0){
		printf("List must not be empty!\n");
	} else{
		while (L->head != NULL){
			deleteAt(L, 0); //calls past function for iterative deletion of the first element
		}
	}
}

// routine for printing a list is given already.
void show(LIST *L){
	if(isEmpty(L)){
		printf("*empty*");
	}else{
		for(NODE* node = L->head; node != NULL; node=node->next){
			printf("%2d", node->value);
		}
	}
}