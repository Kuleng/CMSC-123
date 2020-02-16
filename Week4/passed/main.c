#include "BST.h"
#include <stdio.h>


int main(){

	char command;
	int key, result;

	BST *B = createBST(100);
	BST_NODE* node;
	while(1){
		scanf("%c ", &command);

		switch(command){
			case '+':
				scanf(" %d\n", &key);
				printf("Inserting key: %d\n", key);
				insert(B, createBSTNode(key, NULL, NULL, NULL));
				break;
			case '-':
				scanf(" %d\n", &key);
				printf("Removing node with key: %d\n", key);
				result = delete(B, key); // result is unused. print if u want
				break;
			case '?':
				scanf(" %d\n", &key);
				printf("Searching node with key: %d. Location: %p\n", key, search(B, key));
				// (nil) means NULL pointer
				break;
			case 'p':
				printf("Tree (rotated +90 degrees): \n");
				showTree(B);
				printf("\n");
				break;
			case '<':
				printf("Pre-order Traversal: ");
				preorderWalk(B);
				printf("\n");
				break;
			case '>':
				printf("Post-order Traversal: ");
				postorderWalk(B);
				printf("\n");
				break;
			case '/':
				printf("In-order Traversal: ");
				inorderWalk(B);
				printf("\n");
				break;
			case 'E':
				printf("BST %s empty.\n", isEmpty(B)?"is":"is not");
				break;
			case 'F':
				printf("BST %s full.\n", isFull(B)?"is":"is not");
				break;
			case 'C':
				printf("Removing all contents.\n");
				clear(B);
				break;
			case 'm':
				node = minimum(B);
				if(node)printf("Minimum value: %d\n", node->key);
				else printf("(BST empty)\n");
				break;
			case 'M':
				node = maximum(B);
				if(node)printf("Maximum value: %d\n", node->key);
				else printf("(BST empty)\n");
				break;
			case '[':
				scanf(" %d\n", &key);
				node = search(B, key);
				if(!node){
					printf("%d not found\n", key);
				}else{
					node = predecessor(node);
					if(node)printf("Predecessor of %d is %d.\n", key, node->key);
					else printf("No predecessor for %d\n", key);
				}
				break;
			case ']':
				scanf(" %d\n", &key);
				node = search(B, key);
				if(!node){
					printf("%d not found\n", key);
				}else{
					node = successor(node);
					if(node)printf("Successor of %d is %d.\n", key, node->key);
					else printf("No successor for %d\n", key);
				}
				break;
			case 'Q':
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}

	return 0;
}