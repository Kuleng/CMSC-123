#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

	char command;
	int key, result;
	int *sorted= (int*)malloc(sizeof(int)*15);
	HEAP *H;
	while(1){
		scanf("%c ", &command);

		switch(command){
			case '0':
				H = createHeap(15, 0);
				break;
			case '1':
				H = createHeap(15, 1);
				break;
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
				for(int i = 0; i < H->size; i++)
					printf("%d ", sorted[i]);
				printf("\n");
				break;
			case 'E':
				if(isEmpty(H)) printf("Empty heap!\n");
				else printf("Heap not empty!\n");
				break;
			case 'F':
				if(isFull(H)) printf("Empty heap!\n");
				else printf("Heap not empty!\n");
				break;
			case 'Q':
				return 0;
			default:
				printf("Unknown command: %c\n", command);
				break;
		}
	}

	return 0;
}