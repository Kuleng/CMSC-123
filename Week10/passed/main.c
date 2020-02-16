/***************

Tumpalan, John Karl B.
Djikstra's and Prim's
CMSC 123 - U5L

**************/
#include "tumpalan_mst.h"


void main(){
	int noOfVertices, noOfEdges, sum = 0, source;

	scanf("%d %d\n", &noOfEdges, &noOfVertices);

	int cost[noOfVertices];

	//Create a pointer to an array of pointers of graph
	int **mainMatrix = createMatrix(noOfVertices);

	initializeMatrix(mainMatrix, noOfEdges);

	//PRINT THE ADJACENCY OF THE LIST

	// for(int i = 0; i < noOfVertices; i++){
	// 	for(int j = 0; j < noOfVertices; j++){
	// 		printf("%d ", mainMatrix[i][j]);
	// 	}
	// 	printf("\n");
	// }


	//Loop all destination points from a specified source.
	prims(0, mainMatrix, noOfVertices, cost);

	for(int i = 0; i < noOfVertices; i++){
		sum += cost[i];
		printf("%d ", cost[i]);
	}
	printf("\nTotal sum: %d\n",sum);

}