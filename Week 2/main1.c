#include "queue.h"
#include <stdio.h>


int main(){

	char command;
	int value, result;

	QUEUE *Q = createQueue(4);

	while(1){
		scanf("%c ", &command);

		switch(command){
			case '+':
				scanf("%d\n", &value);
				printf("Enqueueing %d\n", value);
				enqueue(Q, createNode(value));
				break;
			case '-':
				printf("Dequeueing\n");
				result = dequeue(Q); // result is unused. print if u want
				break;
			case 'p':
				printf("Queue: ");
				show(Q);
				printf("\n");
				break;
			case 'E':
				printf("Queue %s empty.\n", isEmpty(Q)?"is":"is not");
				break;
			case 'F':
				printf("Queue %s full.\n", isFull(Q)?"is":"is not");
				break;
			case 'C':
				printf("Dequeueing all contents.\n");
				clear(Q);
				break;
			case 'Q':
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}

	return 0;
}