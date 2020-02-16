/************
*	Tumpalan, John Karl B.
*	CMSC 123 U-5L
*	Graphs
*	2018-02385
*/


#include <stdio.h>
#include <stdlib.h>

typedef struct stackTag{
	int *S;
	int stackSize;
	int maxStack;
} STACK;

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


int** createMatrix(int vertices){

	//Allocation for the new matrix
	int** newMatrix = (int**)malloc(sizeof(int*)*vertices+1);
	for(int i = 0; i < vertices+1; i++){
		newMatrix[i] = (int*)malloc(sizeof(int)*vertices+1);
	}

	//Initialization of new matrix to full of zeroes
	for(int i = 0; i < vertices+1; i++){
		for(int j = 0; j < vertices+1; j++){
			newMatrix[i][j] = 0;
			if(i == 0)
				newMatrix[i][j] = j;
			else if (j == 0)
				newMatrix[i][j] = i;
		}
	}

	return newMatrix;
}

void initializeMatrix(int **matrix, int vertices, int fileExtent){
	int x,y;

	//Fill in the values of the matrix based from file input
	for(int i = 0; i < fileExtent; i++){
		scanf("%d %d\n", &x, &y);
		matrix[x][y] = 1;
		matrix[y][x] = 1;
	}
}

void printMatrix(int** matrix, int vertices){

	//Print matrix for checking
	for(int i = 0; i < vertices+1; i++){
		for(int j = 0; j < vertices+1; j++){
			if (i==0&&j==0)
				printf("  ");
			else
				printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

void DFS_helper(int **matrix, STACK *stack, int* visited, int vertex, int vertices){
	//Helper recursive function for DFS

	//Mark vertex as visited and print
	visited[vertex] = 1;
	printf("%d ", vertex);

	for(int adjacentVertex = 1; adjacentVertex < vertices+1; adjacentVertex++){//for each edge
		if(matrix[vertex][adjacentVertex] == 1){								//if v is adjacent to u
			if(visited[adjacentVertex] == 0){ 									//if v is not visited
				push(stack, adjacentVertex);									 //push to stack
				DFS_helper(matrix, stack, visited, pop(stack),vertices); //recurse further to what is pushed
			}
		}
	}
}


void DFS(int **matrix, int vertices){

	//int array for the visited vertices
	int visitFlags[vertices];

	STACK *mainStack = createStack(vertices*2);

	//Initialization of visited flag array
	for(int node = 1; node < vertices+1; node++){
		visitFlags[node] = 0;
	}

	printf("DFS: ");
	for(int i = 1; i < vertices + 1; i++){
		if(visitFlags[i] == 0){
			push(mainStack, i);
			DFS_helper(matrix, mainStack, visitFlags, pop(mainStack), vertices);
		}
	}
}

int main(){

	//File handling
	int vertexNum ,lines;
	scanf("%d %d\n" , &vertexNum, &lines);

	//Create a dynamic 2D matrix
	int** mainMatrix = createMatrix(vertexNum);

	initializeMatrix(mainMatrix, vertexNum, lines);

	printMatrix(mainMatrix, vertexNum);
	printf("\n");
	
	DFS(mainMatrix,vertexNum);
	printf("\n");

	return 0;
}