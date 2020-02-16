#include<stdio.h>
#include<stdlib.h>


/* Heap structure definition */

typedef enum HeapType {MINHEAP, MAXHEAP} htype;

typedef struct heap_tag {
  int *heap;
  int *heapIndex;
  int size;
  int maxSize;
  htype type;
} HEAP;


/* heap operations */

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

HEAP* createHeap(int maxSize, htype type){
	HEAP* newHeap = (HEAP*)malloc(sizeof(HEAP));

	newHeap->maxSize = maxSize;
	newHeap->heap = (int*)malloc(sizeof(int)*(newHeap->maxSize+1));
	newHeap->heapIndex = (int*)malloc(sizeof(int)*(newHeap->maxSize+1));
	newHeap->size = 0;
	newHeap->type = (type == 1) ? MAXHEAP : MINHEAP;

	return newHeap;
}


int isFull(HEAP *H){
	if(H->size >= H->maxSize) return 1;
	else return 0;
}
int isEmpty(HEAP *H){
	if(H->size == 0) return 1;
	else return 0;
}

void insert(HEAP *H, int key, int keyIndex){

	if(H == NULL){ //CATCHES NULL HEAP
		printf("HEAP IS NULL. \n");
		exit(1);
	} else if(isFull(H)){ //CATCHES FULL HEAP
		printf("HEAP IS FULL.\n");
		exit(1);
	} else{
		H->heap[++H->size] = key; //Add to the end of the array 
		H->heapIndex[H->size] = keyIndex;

		int index = H->size; //Set index for labeling array elements

		if(H->type == MAXHEAP){
			//Percolate up (MAXHEAP)
			while(index != 1){ 									//While index != to the index of the root
				if(H->heap[index] > H->heap[parent(index)]){ 	//Swap if the nodes violate the heap-order property
					swap(&(H->heap[index]), &(H->heap[parent(index)]));
					swap(&(H->heapIndex[index]), &(H->heapIndex[parent(index)]));
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
					swap(&(H->heapIndex[index]), &(H->heapIndex[parent(index)]));
					index = parent(index);
				}
				else break;
			}
		}

	}
}

int delete(HEAP *H, int returnLabel){
	if(H == NULL){
		// printf("HEAP IS NULL. \n");
		exit(1);
	} else if(isFull(H)){
		// printf("HEAP IS FULL.\n");
		exit(1);
	} else if(isEmpty(H)){
		// printf("HEAP IS EMPTY\n");
		return 0;
	} else if(H->size == 1){
		if(returnLabel == 0){
			return (H->heapIndex[H->size+1]);
		}
		H->size--;
		return (H->heap[H->size+1]);
	} else{
		if(returnLabel == 0){
			return (H->heapIndex[H->size+1]);
		}

		int index = 1;
		int max = 0, min = 0;


		swap(&(H->heap[1]), &(H->heap[H->size])); //Swap root and the last index
		swap(&(H->heapIndex[1]), &(H->heapIndex[H->size]));
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
					swap(&(H->heapIndex[index]), &(H->heapIndex[(max)]));
					index = max;
				}
				else 
					break;

			}
			else if(H->type == MINHEAP){ 									 //MINHEAP
																			//Get minimum on the index's children
				if(rightChild(index) > H->size) min = leftChild(index);     //If the right child is out of bounds, left is the min
				else   														//Else, get minimum
					if((H->heap[leftChild(index)]) == (H->heap[rightChild(index)])) min = leftChild(index);
					else
						min = ((H->heap[leftChild(index)]) < (H->heap[rightChild(index)])) ? leftChild(index) : rightChild(index);
				if(H->heap[index] > H->heap[min]){

					swap(&(H->heap[index]), &(H->heap[min])); 		//Call swap function
					swap(&(H->heapIndex[index]), &(H->heapIndex[min]));
					index = min;
				}
				else 
					break;

			}

		}

		if(returnLabel == 1)
			return (H->heap[H->size+1]);
	}
}

//FUnction to create and allocate memory for the matrix. Initializes all matrix indeces to 0.
int** createMatrix(int vertices){

	//Allocate memory for the new matrix to be created
	int** newMatrix = (int**)malloc(sizeof(int*)*vertices);
	for(int i = 0; i < vertices; i++){
		newMatrix[i] = (int*)malloc(sizeof(int)*vertices);
	}

	//Initialize the matrix to a matrix full of zeroes
	for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices; j++){
			newMatrix[i][j] = -1;
		}
	}

	//Return the matrix
	return newMatrix;
}


//Initialize the value of the matrix based from file input

void initializeMatrix(int **matrix, int edges){
	int x,y,wt;

	//Fill in the values and weight of the matrix through scanning from file input
	for(int i = 0; i < edges; i++){
		scanf("%d %d %d\n", &x, &y, &wt);
		matrix[x-1][y-1] = wt;
		matrix[y-1][x-1] = wt;
	}
}

//Function for testing and printing the array components of the algorithm
void printTab(int numOfVertices,int *visitedVs, int *cost, int *parent){
	printf("Visited: ");
	for(int i = 0; i < numOfVertices; i++){
		printf("%d ", visitedVs[i]);
	} printf("\n");
	printf("Cost: ");
	for(int i = 0; i < numOfVertices; i++){
		printf("%d ", cost[i]);
	} printf("\n");

	printf("Parent: ");
	for(int i = 0; i < numOfVertices; i++){
		printf("%d ", parent[i]);
	} printf("\n");
}


//Main prim's function
int* prims(int source, int **matrix, int numOfVertices, int *cost){

	int visitedVs[numOfVertices], fromV[numOfVertices], visited;
	int INT_MAX = 99999, tempSource = source, minIndex, minCost;

	//Create a heap
	HEAP* mainHeap = createHeap(numOfVertices, 0); //Create a MINHEAP

	for (int i = 0; i < numOfVertices; i++){
		//Initialize visited array and terminal index array to -1 (flagged as boolean false)
		visitedVs[i] = fromV[i] = -1;

		//Initialize cost to a very high number
		cost[i] = 99999;
	}

	cost[tempSource] = 0;
	fromV[tempSource] = -1;

	do{
		for(int j = 0; j < numOfVertices; j++){
			//Loop through all the adjacent vertices of i
			if(matrix[tempSource][j] >= 0 && visitedVs[j] == -1){ //If the vertex is adjacent and unvisited
				insert(mainHeap, matrix[tempSource][j], j); //Insert to the frontier
				fromV[j] = tempSource;
				// printf("Added %d, index %d to the frontier. \n", matrix[tempSource][j], j+1);
			}
		}

		//Mark as visited
		visitedVs[tempSource] = 1;
		// Uncomment for tracing
		// printf("Visited %d\n", tempSource + 1);

		//Get the minimum cost and index
		minCost = delete(mainHeap, 1);
		minIndex = delete(mainHeap, 0);

		// Uncomment for tracing
		// printf("Deleting..\n");
		// printHeap(mainHeap);
		// printf("Min cost: %d, Min index: %d \n", minCost, minIndex+1);

		//Update the list of cost
		if(visitedVs[minIndex] == -1){
			if(minCost < cost[minIndex]){
				cost[minIndex] = minCost;
			}
		}

		tempSource = minIndex;	

	}while(isEmpty(mainHeap)!= 1);

	// printTab(numOfVertices, visitedVs, cost, fromV);
	return cost;	
}
