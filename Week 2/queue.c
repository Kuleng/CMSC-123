// no need to include `list.h`
// since we are here to implement
// queue ADT

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>


QUEUE* createQueue(int maxLength){
	// since `QUEUE` is the same as the `LIST` structure
	// we can reuse the function `createList()` to create
	// a queue.
	return createList(maxLength);
}

/*
** function: enqueue
** requirements:
	queue must not be full.

** results: inserts `node` at the tail of the list.

** sample: L = [12, 6, 4, 10]
** enqueue(L, 55) -> L = [12, 6, 4, 10, 55]
** enqueue(L, 44) -> L = [12, 6, 4, 10, 55, 44]
** enqueue(L, 66) -> L = [12, 6, 4, 10, 55, 44, 66]
*/
void enqueue(QUEUE *Q, NODE* node){
	insertAt(Q, Q->length, node);
}

/*
** function: dequeue
** requirements:
	queue must not be empty.
** results:
	deletes node at position head of the list
	returns the value of the deleted node.
** sample: L = [44, 12, 6, 55, 4, 10, 66]
** dequeue(L) -> L = [12, 6, 55, 4, 10, 66]; returns 44
** dequeue(L) -> L = [6, 55, 4, 10, 66]; return 12
** dequeue(L) -> L = [55, 4, 10, 66]; returns 6
*/
int dequeue(QUEUE *Q){
	return deleteAt(Q, 0);
}



// implement other functions here