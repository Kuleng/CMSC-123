#include "list.h"
#include <stdio.h>


int main(){

	char command;
	int index, value, result;

	LIST *L = createList(3);

	while(1){
		scanf("%c ", &command);

		switch(command){
			case '+':
				scanf("i%d %d\n", &index, &value);
				printf("Inserting %d at index %d\n", value, index);
				insertAt(L, index, createNode(value));
				break;
			case '-':
				scanf("i%d\n", &index);
				printf("Deleting node at index %d\n", index);
				result = deleteAt(L, index); // result is unused. print if u want
				break;
			case 'p':
				printf("List: ");
				show(L);
				printf("\n");
				break;
			case 'E':
				printf("List %s empty.\n", isEmpty(L)?"is":"is not");
				break;
			case 'F':
				printf("List %s full.\n", isFull(L)?"is":"is not");
				break;
			case 'C':
				printf("Deleting all contents.\n");
				clear(L);
				break;
			case 'Q':
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}

	return 0;
}