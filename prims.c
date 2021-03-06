/***************

Tumpalan, John Karl B.
Djikstra's and Prim's
CMSC 123 - U5L

**************/

#include<stdio.h>
#include<stdlib.h>


typedef struct graph_tag{
	int x;
	int weight;
	struct graph_tag *next;
}GRAPH;

//G is the main pointer of array of pointers
//Source is the starting vertex
//D indicates the minimum weight

GRAPH *createNode(int v, int w){
	GRAPH* newGraph = (GRAPH*)malloc(sizeof(GRAPH));
	newGraph->x = v;
	newGraph->weight = w;
	newGraph->next = NULL;

	return newGraph;
}
void initializeList(GRAPH **G, int edges){
	int vertexU = 0, vertexV = 0, weight = 0, edge = 0;

	//Loop through all the number of edges
	while(scanf("%d %d %d\n", &vertexU, &vertexV, &weight) != EOF){


		//If the vertex is NULL (no adjacent visited nodes yet, create the head of the linked list)
		if(G[vertexU-1] == NULL){
			G[vertexU-1] = createNode(vertexV-1, weight);
		}
		else{
			//If not NULL, insert at tail.
			GRAPH *temp;
			temp = G[vertexU-1];

			while(temp->next != NULL){
				temp = temp->next;
			}

			temp->next = createNode(vertexV-1, weight);
		}
	}
}


void prim(int source, GRAPH **G, int numOfVertices, int *minWeight){
	int visitedVs[numOfVertices], fromV[numOfVertices];

	for(int i = 0; i < numOfVertices; i++){
		//Initialize visited array and terminal index array to -1 (flagged as boolean false)
		visitedVs[i] = fromV[i] = -1;

		//Initialize minWeight to a very high number
		minWeight[i] = 999;
	}
 
 	minWeight[source] = 0;
 	fromV[source] = 0;

	int newSource = 999, minIndex = source;

	for (int i = 0; i < numOfVertices; i++){

		// printf("List of all looped weight: \n");
		for(int j = 0; j < numOfVertices; j++){
			if (i==0) break;
			// printf("%d < %d ? \n", minWeight[j], newSource);
			if (minWeight[j] < newSource && visitedVs[j] == -1){
				newSource = minWeight[j];
				minIndex = j;
			}
		}
		// printf("\n");

		// printf("Minimum: %d, Weight: %d\n", minIndex+1, minWeight[minIndex]);
		visitedVs[minIndex] = 1;
		
		GRAPH *temp1 = G[minIndex];
		while(temp1 != NULL){
			// if(visitedVs[temp1->x] == -1 && (temp1->weight + fromV[minIndex]) < minWeight[temp1->x]){
			if(visitedVs[temp1->x] == -1 && temp1->weight < minWeight[temp1->x]){ //For prim's
				minWeight[temp1->x] = temp1->weight;
				// minWeight[temp1->x] = temp1->weight+fromV[minIndex];
				fromV[temp1->x] = minIndex;
			}
			temp1 = temp1->next;
		}

		newSource = minIndex = 99;
	}


	printf("Visited: \n");
	for(int i = 0; i < numOfVertices; i++){
		printf("%d ", visitedVs[i]);
	}
	printf("\nFrom: \n");
	for(int i = 0; i < numOfVertices; i++){
		printf("%d ", fromV[i]+1);
	}
	printf("\nMin weight: \n");
	for(int i = 0; i < numOfVertices; i++){
		printf("%d ", minWeight[i]);
	}
	printf("\n");
}


void main(){
	int noOfVertices, noOfEdges;

	scanf("%d %d\n", &noOfVertices, &noOfEdges);

	int minWeight[noOfVertices];

	//Create a pointer to an array of pointers of graph
	GRAPH **mainGraph = (GRAPH**)malloc(sizeof(GRAPH*));
	for(int i = 0; i < noOfVertices; i++){
		mainGraph[i] = (GRAPH*)malloc(sizeof(GRAPH));
		mainGraph[i] = NULL;
	}

	initializeList(mainGraph, noOfEdges);

	//PRINT THE ADJACENCY OF THE LIST
	for(int i = 0; i < noOfVertices; i++){
		GRAPH *temp = mainGraph[i];
		while(temp != NULL){
			printf(" || %d to %d, weight: %d || \n", i+1, temp->x, temp->weight);
			temp = temp->next;
		}
	}

	prim(0, mainGraph, noOfVertices, minWeight);
}