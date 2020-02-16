/*

	Child left: Index * 2
	Child right: Index * 2 + 1
	
	Parent: (Index/2) 
*/

#include <stdio.h>
#include <stdlib.h>


typedef struct heapTag{

	int *mainArray;
	int heapSize;
	int maxSize;

}HEAP;

int leftChild(int index){
	return (index*2+1);
}
int rightChild(int index){
	return ((index*2)+2);
}
int parent(int index){
	return ((index-1)/2);
}
HEAP* createHeap(int maxSize){
	HEAP *newHeap = (HEAP*)malloc(sizeof(HEAP));

	newHeap->mainArray = (int*) malloc(sizeof(int)*maxSize);
	newHeap->maxSize = maxSize;
	newHeap->heapSize = 0;

	return newHeap;
}

void swap(int *a, int *b){

	(*a) = (*a)^(*b);
	(*b) = (*b)^(*a);
	(*a) = (*a)^(*b);

}

void maxHeap_fixUp(HEAP *newHeap, int index){

	while (1){
		if(newHeap->mainArray[index] < newHeap->mainArray[parent(index)]){
			swap(&(newHeap->mainArray[index]), &(newHeap->mainArray[parent(index)]));
			index = parent(index);
		}
		else{
			break;
		}
	}

}

void minHeap_fixUp(HEAP *newHeap, int index){

	while (1){
		if(newHeap->mainArray[index] > newHeap->mainArray[parent(index)]){
			swap(&(newHeap->mainArray[index]), &(newHeap->mainArray[parent(index)]));
			index = parent(index);
		}
		else{
			break;
		}
	}

}

void insertNode(HEAP* heapheap, int key){
	
	heapheap->mainArray[heapheap->heapSize++] = key;
	minHeap_fixUp(heapheap, heapheap->heapSize-1);

}


void max_percolateDown(HEAP* heapheap){
	int index = 0;

	while(1){
		if(heapheap->mainArray[leftChild(index)] < heapheap->mainArray[rightChild(index)]){					//Gets the maximum of left/right
			if(heapheap->mainArray[index] < heapheap->mainArray[rightChild(index)]){						//Checks if the current index is less than the max of left/right
				swap(&(heapheap->mainArray[index]), &(heapheap->mainArray[rightChild(index)]));				//Swap if index < (max(right,left))
				index = rightChild(index);
			}
			else
				break;
		}
		else{

			if(heapheap->mainArray[index] < heapheap->mainArray[leftChild(index)]){						//Checks if the current index is less than the max of left/right
				swap(&(heapheap->mainArray[index]), &(heapheap->mainArray[leftChild(index)]));				//Swap if index < (max(right,left))
				index = leftChild(index);
			}
			else
				break;

		}
	}
}

void min_percolateDown(HEAP* heapheap){
	int index = 0;

	while(1){
		if(heapheap->mainArray[leftChild(index)] > heapheap->mainArray[rightChild(index)]){					//Gets the maximum of left/right
			if(heapheap->mainArray[index] > heapheap->mainArray[rightChild(index)]){						//Checks if the current index is less than the max of left/right
				swap(&(heapheap->mainArray[index]), &(heapheap->mainArray[rightChild(index)]));				//Swap if index > (max(right,left))
				index = rightChild(index);
			}
			else
				break;
		}
		else{

			if(heapheap->mainArray[index] > heapheap->mainArray[leftChild(index)]){						//Checks if the current index is less than the max of left/right
				swap(&(heapheap->mainArray[index]), &(heapheap->mainArray[leftChild(index)]));				//Swap if index > (max(right,left))
				index = leftChild(index);
			}
			else
				break;

		}
	}
}

void deleteNode(HEAP* heapheap){

	printf("Deleted %d \n", heapheap->mainArray[0]);
	heapheap->mainArray[0] = heapheap->mainArray[heapheap->heapSize];
	max_percolateDown(heapheap);

	heapheap->heapSize --;

}

int main(){	
	
	HEAP* mainHeap = createHeap(100);


	insertNode(mainHeap, 10);
	insertNode(mainHeap, 9);
	insertNode(mainHeap, 54);
	insertNode(mainHeap, 3);
	insertNode(mainHeap, 1);
	insertNode(mainHeap, 4);

	deleteNode(mainHeap);
	deleteNode(mainHeap);
	deleteNode(mainHeap);
	deleteNode(mainHeap);
	deleteNode(mainHeap);
	printf("Deleting root \n\n\n\n");

	for(int i = 0; i < mainHeap->heapSize; i++){

		printf("Parent: %d \n", mainHeap->mainArray[i]);
		printf("Left:  %d \n", mainHeap->mainArray[leftChild(i)]);
		printf("Right  %d \n", mainHeap->mainArray[rightChild(i)]);

	}
	return 0;
}