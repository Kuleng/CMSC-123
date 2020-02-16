/*
	Tumpalan, John Karl B.
	Exercise 6: Heaps - October 11, 2019
*/

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
//include here additional header files

void printHeapHelper(HEAP *H, int index, int tabs){
	if(index > H->size) return;
	else{
		printHeapHelper(H, index*2+1, tabs + 1);
		for(int i=0; i<tabs; i++) printf("\t");
		printf("%d\n", H->heap[index]);
		printHeapHelper(H, index*2, tabs + 1);
	}
}

void printHeap(HEAP *H){
	if(H!=NULL && H->size>0){
		printHeapHelper(H, 1, 0);
	}else{
		printf("Empty heap!\n");
	}
}

//implement your functions here

//Relational functions
int parent(int index){ return (index/2); }
int leftChild(int index){ return (index*2); }
int rightChild(int index){ return ((index*2)+1); }

//Swapping function
void* swap(int *a, int *b){

	(*a) = (*a)^(*b);
	(*b) = (*b)^(*a);
	(*a) = (*a)^(*b);

}

/*
 *  requirements: none
 *  results:
    creates an integr array with size = maxSize+1
      the +1 is needed since this implementation
      will be using index 1 as the root of the heap
    initializes fields of the structure
    returns the created heap
*/
HEAP* createHeap(int maxSize, htype type){
	HEAP* newHeap = (HEAP*)malloc(sizeof(HEAP));

	newHeap->maxSize = maxSize;
	newHeap->heap = (int*)malloc(sizeof(int)*(newHeap->maxSize+1));
	newHeap->size = 0;
	newHeap->type = (type == 1) ? MAXHEAP : MINHEAP;

	return newHeap;
}

/*
 *  requirements: none
 *  results:
      return 1 if the heap is full;
      otherwise return 0
*/
int isFull(HEAP *H){
	if(H->size >= H->maxSize) return 1;
	else return 0;
}

/*
 *  requirements: none
 *  results:
      return 1 if the heap is empty;
      otherwise return 0
*/
int isEmpty(HEAP *H){
	if(H->size == 0) return 1;
	else return 0;
}

/*
 *  requirements:
      a non-null HEAP pointer
      a non-full *heap
 *  results:
      inserts `key` to the `heap`
*/
void insert(HEAP *H, int key){

	if(H == NULL){ //CATCHES NULL HEAP
		printf("HEAP IS NULL. \n");
		exit(1);
	} else if(isFull(H)){ //CATCHES FULL HEAP
		printf("HEAP IS FULL.\n");
		exit(1);
	} else{
		
		H->heap[++H->size] = key; //Add to the end of the array 
		int index = H->size; //Set index for labeling array elements

		if(H->type == MAXHEAP){
			//Percolate up (MAXHEAP)
			while(index != 1){ 									//While index != to the index of the root
				if(H->heap[index] > H->heap[parent(index)]){ 	//Swap if the nodes violate the heap-order property
					swap(&(H->heap[index]), &(H->heap[parent(index)]));
					index = parent(index); //Update index
				}
				else break;
			}
		}

		else if(H->type == MINHEAP){
			//Percolate up (MINHEAP)

			while(index != 1){ 									//While index != to the index of the root
				if(H->heap[index] < H->heap[parent(index)]){	//Swap if the nodes violate the heap-order property
					swap(&(H->heap[index]), &(H->heap[parent(index)]));
					index = parent(index);
				}
				else break;
			}
		}

	}
}

/*
 *  requirements:
      a non-null HEAP pointer
      a non-empty *heap
 *  results:
      removes the minimum value (root) from the heap (if MINHEAP)
	  removes the maximum value (root) from the heap (if MAXHEAP)
      returns the deleted value
*/
int delete(HEAP *H){
	if(H == NULL){
		printf("HEAP IS NULL. \n");
		exit(1);
	} else if(isFull(H)){
		printf("HEAP IS FULL.\n");
		exit(1);
	} else if(isEmpty(H)){
		printf("HEAP IS EMPTY\n");
		exit(1);
	} else if(H->size == 1){
		H->size--;
		return (H->heap[H->size+1]);
	}else{
		int index = 1;
		int max = 0, min = 0;


		swap(&(H->heap[1]), &(H->heap[H->size])); //Swap root and the last index
		H->size--;								  //Decrement the size of the heap

		while(leftChild(index) <= H->size){		//While left child is not out of bounds
			//Percolate down

			if(H->type == MAXHEAP){										//MAXHEAP
																		//Get maximum of the index's children
				if(rightChild(index) > H->size) max = leftChild(index); //If the right child is out of bounds, left child is automatically the max
				else  													//If not, get maximum
					max = ((H->heap[leftChild(index)]) > (H->heap[rightChild(index)])) ? leftChild(index) : rightChild(index);

				if(H->heap[index] < H->heap[max]){

					swap(&(H->heap[index]), &(H->heap[max]));		//Call swap function
					index = max;
				}
				else 
					break;

			}
			else if(H->type == MINHEAP){ 									 //MINHEAP
																			//Get minimum on the index's children
				if(rightChild(index) > H->size) min = leftChild(index);     //If the right child is out of bounds, left is the min
				else   														//Else, get minimum
					min = ((H->heap[leftChild(index)]) < (H->heap[rightChild(index)])) ? leftChild(index) : rightChild(index);
				if(H->heap[index] > H->heap[min]){

					swap(&(H->heap[index]), &(H->heap[min])); 		//Call swap function
					index = min;
				}
				else 
					break;

			}

		}

		return (H->heap[H->size+1]);
	}
}

/*
 *  requirements:
      a non-null HEAP pointer
      a non-empty *heap
 *  results:
 	  deletes all the items in the heap
*/
void clear(HEAP *H){
	if(H == NULL){
		printf("HEAP IS NULL. \n");
		exit(1);
	} else if(isEmpty(H)){
		printf("HEAP IS ALREADY EMPTY\n");
		exit(1);
	} else{
		while(H->size != 0){
			delete(H);
		}
	}
}

/*
 *  requirements:
      a non-null HEAP pointer
      a non-empty *heap
 *  results:
 	  returns an array containing the sorted values of the heap
	  (must not modify the original heap)
*/
int * heapSort(HEAP *H){

	//Create a duplicate heap to retain the original keys of the original heap after the continuous deletion of the root
	HEAP* clonedHeap = (HEAP*)malloc(sizeof(HEAP));
	clonedHeap->maxSize = H->maxSize;
	clonedHeap->heap = (int*)malloc(sizeof(int)*(clonedHeap->maxSize + 1));
	clonedHeap->heap = H->heap;
	clonedHeap->size = H->size;
	clonedHeap->type = H->type;


	//Create a dynamic array to store the deleted keys after deletion
	int *newArray = (int*)malloc(sizeof(int)*clonedHeap->size);

	//Loop deletion of the root
	for(int i = 0; i < H->size; i++){
		newArray[i] = delete(clonedHeap);
	}
	printf("\n");

	//Return the array
	return newArray;
}

// int main(){

// 	HEAP* mainHeap = createHeap(10,1);

// 	insert(mainHeap, 16);
// 	insert(mainHeap, 11);
// 	insert(mainHeap, 6);
// 	insert(mainHeap, 3);
// 	insert(mainHeap, 15);
// 	insert(mainHeap, 2);
// 	insert(mainHeap, 7);

// 	printHeap(mainHeap);

// 	printf("----DELETE----\n");
// 	printf("Node: %d \n", delete(mainHeap));
// 	printf("----DELETE----\n");
// 	printf("Node: %d \n", delete(mainHeap));
// 	printHeap(mainHeap);
// 	printf("----DELETE----\n");
// 	printf("Node: %d \n", delete(mainHeap));
// 	printf("----DELETE----\n");
// 	printf("Node: %d \n", delete(mainHeap));
// 	printHeap(mainHeap);

// 	int* sortedHeap = (int*)malloc(sizeof(int)*mainHeap->size);
// 	sortedHeap = heapSort(mainHeap);

// 	for(int i = 0; i < mainHeap->size; i++){
// 		printf("%d ", sortedHeap[i]);
// 	}
// 	printf("\n");

// 	printf("----CLEAR----\n");
// 	clear(mainHeap);
// 	printHeap(mainHeap);
// }
