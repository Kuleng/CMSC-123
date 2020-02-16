#include "heap.h"
#include <stdio.h>


int main(){

	char command;
	int key, result;
	int *sorted= (int*)malloc(sizeof(int)*15);
	while(1){
		scanf("%c ", &command);

		switch(command){
			case '0':
				BST *H = createHeap(15, 0);
			case '1':
				BST *H = createHeap(15, 1);
			case '+':
				scanf(" %d\n", &key);
				printf("Inserting key: %d\n", key);
				insert(H, key);
				break;
			case '-':
				scanf(" %d\n", &key);
				delete(H); // result is unused. print if u want
				break;
			case 'p':
				printHeap(H);
				break;
			case 'C':
				printf("Removing all contents.\n");
				clear(H);
				break;
			case '~':
				sorted = heapSort(H);
				for(int i = 0; i < 15; i++)
					printf("%d ", sorted);
			case 'E':
				if(isEmpty(H)) printf("Empty heap!\n");
				else printf("Heap not empty!\n", );
				break;
			case 'F':
				if(isFull(H)) printf("Empty heap!\n");
				else printf("Heap not empty!\n", );
				break;
			case 'Q':
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}

	return 0;
}