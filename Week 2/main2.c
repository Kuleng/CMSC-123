#include "stack.h"
#include <stdio.h>


int main(){

	char command;
	int value, result;

	STACK *Q = createStack(4);

	while(1){
		scanf("%c ", &command);

		switch(command){
			case '+':
				scanf("%d\n", &value);
				printf("Pushing %d\n", value);
				push(Q, createNode(value));
				break;
			case '-':
				printf("Popping\n");
				result = pop(Q); // result is unused. print if u want
				break;
			case 'p':
				printf("Stack: ");
				show(Q);
				printf("\n");
				break;
			case 'E':
				printf("Stack %s empty.\n", isEmpty(Q)?"is":"is not");
				break;
			case 'F':
				printf("Stack %s full.\n", isFull(Q)?"is":"is not");
				break;
			case 'C':
				printf("Popping all contents.\n");
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