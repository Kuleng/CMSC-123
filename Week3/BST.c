/*
Tumpalan, John Karl B.
2018 - 02385
Exercise 04 - BST Part 1
*/
#include "BST.h"
#include <stdio.h>
#include <stdlib.h>
// include other headers u need

/*
** function: createBSTNode
** requirements:
    an integer indicating the key of the node
    an initial value for the left pointer (L)
    an initial value for the right pointer (R)
    an initial value for the parent pointer (P)
    if L, R, or P is unknown, pass `NULL`
** results:
    creates a BST node with fields initialized
    returns a pointer of this instance
** notes:
    a node's height can be derived from left and right subtrees
        i.e. node->height = max(L->height, R->height) + 1
    if there are no subtrees i.e L==R==NULL, then node->height = 0
*/
BST_NODE* createBSTNode(int key, BST_NODE* L, BST_NODE* R, BST_NODE* P){
	BST_NODE* newNode = (BST_NODE*)malloc(sizeof(BST_NODE));

	newNode->left = L;
	newNode->right = R;
	newNode->parent = P;
	newNode->key = key;
	newNode->height = 0;

	return newNode;
}


/*
** function: createBST
** requirements:
    an integer indicating the maximum size of the BST
        i.e. the maximum number of elements that can be stored
** results:
    creates an empty BST with fields initialized
    returns a pointer of this instance
*/
BST* createBST(int max){
	BST* newTree = (BST*)malloc(sizeof(BST));

	newTree->root = NULL;
	newTree->maxSize = max;
	newTree->size = 0;

	return newTree;
}

/*
** function: isEmpty
** requirements:
    a non-null BST pointer
** results:
    returns 1 if BST is empty;
    otherwise, return 0
*/
int isEmpty(BST* B){
	if (B->size == 0)
		return 1;
	else
		return 0;
}

/*
** function: isFull
** requirements:
    a non-null BST pointer
** results:
    returns 1 if BST is full;
    otherwise, return 0
*/
int isFull(BST* B){
	if (B->size == B->maxSize)
		return 1;
	else
		return 0;
}


/*
Function: update height
	recurses the height attribute of the nodes starting from
	the root node down to the leaf node.
	uses pass by reference but has an int value due to the recursion
	process
*/

int updateHeight(BST_NODE *root){
	/*sets height for null nodes as -1, then gets the maximum
	between the left or the right node.
	After getting the maximum, increments + 1 for height update then returns the value as the node's height
	*/
	int left_height = (root->left == NULL) ? -1 : updateHeight(root->left);
	int right_height = (root->right == NULL) ? -1 : updateHeight(root->right);

	root->height = (left_height > right_height) ? (left_height + 1) : (right_height+1);

	return root->height;
}

/*
** function: insert
** requirements:
    a non-null BST pointer
    a non-full BST
    a non-null BST_NODE pointer
** results:
    inserts the given `node` to the BST `B`
*/

BST_NODE* insertNode(BST_NODE *node, BST_NODE *toInsert){
	if (node == NULL){ //Returns the node to be inserted to fill the value of the last recursion
		return toInsert; //means that the left/right pointer is already NULL
	} else if (node->key == toInsert->key){
		return node; //returns node if the key is equal, doesn't add to the main BST
	} else if (node->key > toInsert->key){
		if(node->left == NULL){ //catches the null left pointer to avoid segmentation fault
			toInsert->parent = node;
		}
		node->left = insertNode(node->left, toInsert); //recurse tree to get the value of left
	} else if (node->key < toInsert->key){ 
		if(node->right == NULL){ //catches the null right pointer instance to avoid segmentation fault
			toInsert->parent = node;
		}
		node->right = insertNode(node->right, toInsert); //recurse tree to continously get value for the right
	}
}

void insert(BST* B, BST_NODE* node){
	if(isFull(B) == 0){ //checks if the BST B is full
		if(B->root == NULL){ //if the BST is empty
			B->root = node;
		} else if(B->root->key > node->key){ //if the node to insert is lower
			insertNode(B->root, node);	//call the helper function
		} else if(B->root->key < node->key){ //if the node to insert is higher
			insertNode(B->root, node); //call helper function
		}
	}

	B->size ++; //Update Size of the tree
	updateHeight(B->root);
}

/*
** function: search
** requirements:
    a non-null BST pointer
    a non-empty BST
    an integer `key`
** results:
    finds `key` from BST `B` and returns its node pointer if found, 
        otherwise, return `NULL`
*/

BST_NODE* searchKey(BST_NODE* node, int data){
	BST_NODE* keyPointer = NULL;

	if(node == NULL || node->key == data){ //base case
		keyPointer = node; //if the key is not in the tree, returns NULL, else, returns the node address.
	} else if(node->key < data){
		keyPointer = searchKey(node->right, data); //search in the right side of the tree
	} else if(node->key > data){
		keyPointer = searchKey(node->left, data); //search in the left side of the tree
	} else
		exit(1);

	return keyPointer; //returns the pointer to the node
}

BST_NODE* search(BST* B, int key){
	BST_NODE* keyPointer = NULL;

	if(isEmpty(B) == 0){
		if(B->root == NULL){
			keyPointer = B->root; //return NULL
		} else{
			keyPointer = searchKey(B->root, key); //search for the value of node with the key
		}
	} else{
		printf("The tree is empty. \n");
	}

	return keyPointer;
}

/*
** function: preorderWalk
** requirements:
    a non-null BST pointer
** results:
    displays a list of elements of the BST using `pre-order traversal`
*/
void preOrderWalkHelper(BST_NODE *root){
	if (root != NULL){
		printf("%d ", root->key);
		preOrderWalkHelper(root->left);
		preOrderWalkHelper(root->right);
	}
}

void preorderWalk(BST* B){
	preOrderWalkHelper(B->root);
	printf("\n");
}

/*
** function: inorderWalk
** requirements:
    a non-null BST pointer
** results:
    displays a list of elements of the BST using `in-order traversal`
*/

void inorderWalkHelper(BST_NODE *root){
	if(root != NULL){
		inorderWalkHelper(root->left);
		printf("%d ", root->key);
		inorderWalkHelper(root->right);
	}
}

void inorderWalk(BST* B){
	inorderWalkHelper(B->root);
	printf("\n");
}

/*
** function: postorderWalk
** requirements:
    a non-null BST pointer
** results:
    displays a list of elements of the BST using `post-order traversal`
*/

void postorderWalkHelper(BST_NODE *root){
	if(root != NULL){
		postorderWalkHelper(root->left);
		postorderWalkHelper(root->right);
		printf("%d ", root->key);
	}
}

void postorderWalk(BST* B){
	postorderWalkHelper(B->root);
	printf("\n");
}


// a recursive subroutine to display the BST in tree mode
void showTreeHelper(BST_NODE* node, int tabs){
	if(!node) return; // node is null, do nothing

	showTreeHelper(node->right, tabs + 1);
	for(int i=0; i<tabs; i++) printf("\t");
	printf("%d(%d)\n", node->key, node->height);
	showTreeHelper(node->left, tabs + 1);
}

void showTree(BST* B){
	showTreeHelper(B->root, 0);
}

// insert your function definitions below