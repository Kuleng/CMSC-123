/***************

Tumpalan, John Karl B.
Djikstra's and Prim's
CMSC 123 - U5L

**************/

#include<stdio.h>
#include<stdlib.h>


/* Stack structure definition */

typedef struct stackTag{
	int *S;
	int stackSize;
	int maxStack;
} STACK;


/*stack operations */

STACK* createStack(int max){
	STACK* newStack = (STACK*)malloc(sizeof(STACK));
	newStack->S = (int*)malloc(sizeof(int)*max);
	newStack->stackSize = 0;
	newStack->maxStack = max;

	return newStack;
}

void push(STACK *stack, int num){
	if(stack->stackSize < stack->maxStack)
		stack->S[stack->stackSize++] = num;
	else
		printf("overflow!\n");
}

int pop(STACK *stack){
	if(stack->stackSize > 0)
		return stack->S[--stack->stackSize];
	else
		printf("underflow!\n");
}

int isEmpty(STACK *stack){
	if(stack->stackSize <= 0) return 1;

	return 0;
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
	}
}

void initializeQueries(int *destination, int queries){
	int x;
	for(int i = 0;i < queries; i++){
		scanf("%d\n", &x);
		destination[i] = x - 1;
	}
}

//Function for testing and printing the array components of the algorithm
void printTab(int numOfVertices, int queries, int *visitedVs, int *minWeight, int *parent, int *targets){
	printf("Visited: ");
	for(int i = 0; i < numOfVertices; i++){
		printf("%d ", visitedVs[i]);
	} printf("\n");
	printf("Weight: ");
	for(int i = 0; i < numOfVertices; i++){
		printf("%d ", minWeight[i]);
	} printf("\n");

	printf("Parent: ");
	for(int i = 0; i < numOfVertices; i++){
		printf("%d ", parent[i]);
	} printf("\n");

	printf("Queries: ");
	for(int i = 0; i < queries; i++){
		printf("%d ", targets[i]);
	} printf("\n");
}


//Main dijkstra's function
void dijkstra(int source, int **matrix, int numOfVertices, int destination, int *minWeight){

	int visitedVs[numOfVertices], fromV[numOfVertices], visited;
	int INT_MAX = 99999, tempSource = source, minIndex;

	//Create a stack
	STACK *mainStack = createStack(numOfVertices);

	for(int i = 0; i < numOfVertices; i++){
		//Initialize visited array and terminal index array to -1 (flagged as boolean false)
		visitedVs[i] = fromV[i] = -1;

		//Initialize minWeight to a very high number
		minWeight[i] = 99999;
	}

	minWeight[tempSource] = 0;
	fromV[tempSource] = 0;

	for(int i = 0; i < numOfVertices; i++){
		for(int j = 0; j < numOfVertices; j++){
			//Loop through all the adjacent vertices of i
			if(matrix[tempSource][j] >= 0 && visitedVs[j] == -1){ //If the vertex is adjacent and unvisited
				if(minWeight[tempSource] + matrix[tempSource][j] < minWeight[j]){
					minWeight[j] = minWeight[tempSource] + matrix[tempSource][j];
					fromV[j] = tempSource;
				}
			}
		}

		//Mark as visited
		visitedVs[tempSource] = 1;


		int minimum = INT_MAX;
		for(int k = 0; k < numOfVertices; k++){
			if(minWeight[k] < minimum && visitedVs[k] == -1){ //If the vertex is adjacent and unvisited
				minIndex = k;								  //change the minimum index and minimum weight based from the updated minimum weight array.
				minimum = minWeight[k];
			}
		}

		if(tempSource == destination){
			//Destination reached.
			break;
		}
		else if(minWeight[minIndex] == INT_MAX)
			break; //if the loop is done and the weight of the destination source is still MAX, it is not connected through the source.
		else
			tempSource = minIndex; //Update source index

	}


	//Code block for printing path and weight
	
	int traceback = destination, displayV; //traceback is the destination

	displayV = 0;
	if(fromV[traceback] == -1) printf("Impossible\n-1 \n");
	else{
		while(1){
			if(traceback == source){
				printf("%d ", source + 1);
				break;
			}
			else{
				if(displayV++ == 0) push(mainStack, traceback+1);
				else 
					push(mainStack, traceback+1);
				traceback = fromV[traceback];
			}
		}

		//print all the stacked inputs inversely from the path array.
		while(isEmpty(mainStack) == 0){
			printf("%d ", pop(mainStack));
		}

		// print the minimum weight of all the path from a source to the destination
		printf("\n%d\n", minWeight[destination]);
	}
}



void main(){
	int noOfVertices, noOfEdges, queries, source;

	scanf("%d %d %d %d\n", &noOfVertices, &noOfEdges, &queries, &source);

	int minWeight[noOfVertices], destination[queries], *path;

	//Create a pointer to an array of pointers of graph
	int **mainMatrix = createMatrix(noOfVertices);

	initializeMatrix(mainMatrix, noOfEdges);

	initializeQueries(destination, queries);

	//PRINT THE ADJACENCY OF THE LIST

	// for(int i = 0; i < noOfVertices; i++){
	// 	for(int j = 0; j < noOfVertices; j++){
	// 		printf("%d ", mainMatrix[i][j]);
	// 	}
	// 	printf("\n");
	// }


	//Loop all destination points from a specified source.
	for(int i = 0; i < queries; i++){
		dijkstra(source-1, mainMatrix, noOfVertices, destination[i], minWeight);
	}
}