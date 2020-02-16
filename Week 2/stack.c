// no need to include `list.h`
// since we are here to implement
// queue ADT

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>


STACK* createStack(int maxLength){
	// since `QUEUE` is the same as the `LIST` structure
	// we can reuse the function `createList()` to create
	// a queue.
	return createList(maxLength);
}

void push(STACK *Q, NODE* node){
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
int pop(STACK *Q){
	return deleteAt(Q,Q->length-1);
}


// implement other functions here