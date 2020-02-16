/************
*	Tumpalan, John Karl B.
*	CMSC 123 U-5L
*	Graphs
*	2018-02385
*/

#include <stdio.h>
#include <stdlib.h>

int** createMatrix(int vertices){
	//Allocate memory for the new matrix to be created
	int** newMatrix = (int**)malloc(sizeof(int*)*vertices);
	for(int i = 0; i < vertices; i++){
		newMatrix[i] = (int*)malloc(sizeof(int)*vertices);
	}

	//Initialize the matrix to a matrix full of zeroes
	for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices; j++){
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

	//Fill in the values of the matrix through scanning from file input
	for(int i = 0; i < fileExtent; i++){
		scanf("%d %d\n", &x, &y);
		matrix[x-1][y-1] = 1;
		matrix[y-1][x-1] = 1;
	}
}

void dfs(int **matrix, int *visited, int vertices, int vertex)
{
	//Recursive dfs

	//Print the vertex and mark as visited node
	printf("%d ",vertex+1);
    visited[vertex]=1;
	
																	//For all vertices
	for(int adjacentV=0; adjacentV < vertices; adjacentV++)			//If the vertex is adjacent and unvisited
       if(visited[adjacentV] == 0 && matrix[vertex][adjacentV] == 1)//Recurse to the vertex
            dfs(matrix, visited, vertices, adjacentV);
}


int main(){
	int numOfVertices, numOfEdges;
	scanf("%d %d\n", &numOfVertices, &numOfEdges);

	int** mainMatrix = createMatrix(numOfVertices);
	initializeMatrix(mainMatrix, numOfVertices, numOfEdges);

	//Initialization of the visited flag array for the vertices
	int visitedVertices[numOfVertices];
	for(int i = 1; i < numOfVertices; i++){
		visitedVertices[i] = 0;
	}

	//Start DFS with 0
	printf("DFS: ");;
	dfs(mainMatrix, visitedVertices, numOfVertices, 0);
	printf("\n");
	
	return 0;
}