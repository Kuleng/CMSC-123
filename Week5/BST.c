/*
Tumpalan, John Karl B.
2018 - 02385
Exercise 04 - BST Part 2
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

void updateHeight(BST_NODE *root){
	/*sets height for null nodes as -1, then gets the maximum
	between the left or the right node.
	After getting the maximum, increments + 1 for height update then returns the value as the node's height
	*/
	int left_height, right_height;

	//Update the height of the parameter node up to the root of the tree
	while (1){
	    left_height = (root->left == NULL) ? -1 : (root->left->height);
		right_height = (root->right == NULL) ? -1 : (root->right->height);

		//(Maximum height) + 1
		root->height = (left_height > right_height) ? (left_height + 1) : (right_height+1);

		if(root->parent == NULL) break;

		root = root->parent;
	}
}
/****************
AVL FIX UP
****************/

int getBalanceFactor(BST_NODE *node){
	int left_height = (node->left == NULL) ? -1 : node->left->height;
	int right_height = (node->right == NULL) ? -1 : node->right->height;
	int balanceFactor = (left_height - right_height);

	return balanceFactor;
}

BST_NODE* avl_rightRotate(BST_NODE *criticalNode){
	BST_NODE* parentPointer = criticalNode->parent; //holds the parent of the node passed.

	criticalNode->left->parent = parentPointer;
	criticalNode->parent = criticalNode->left;
	criticalNode->left = criticalNode->left->right;
	if(criticalNode->left != NULL) criticalNode->left->parent = criticalNode;
	criticalNode->parent->right = criticalNode;

	return criticalNode->parent; //new root of the modified sub tree
}

BST_NODE* avl_leftRotate(BST_NODE *criticalNode){
	BST_NODE* parentPointer = criticalNode->parent; //holds the parent of the node passed.

	criticalNode->parent = criticalNode->right;
	criticalNode->right = criticalNode->right->left;
	if(criticalNode->right != NULL) criticalNode->right->parent = criticalNode;
	criticalNode->parent->left = criticalNode;
	criticalNode->parent->parent = parentPointer;

	return criticalNode->parent; //new root of the modified sub tree
}


void avl_fixup(BST *tree, BST_NODE *node){

	BST_NODE **directionPointer;
	int absBalanceFactor;

	directionPointer = NULL; //starts from the leaf, so start from null.

	while(node != NULL){
		
		absBalanceFactor = abs(getBalanceFactor(node)); //balance factor of the node


		if(absBalanceFactor >= 2){

			/*********************
				If the critical node is the current root of the tree, manipulate
			the subtree in the function and then return the new root to be pointed by the 
			root pointer of the bst,
				else, point the left or right pointer of the parent to the root pointer returned
			by the rotate functions.
			**********************/

			if(getBalanceFactor(node) > 0 && getBalanceFactor(*directionPointer) > 0){

				printf("Left left imbalance\n");
				/*********************
				Left left imbalance, right rotate on the critical node.
				**********************/

				if(node->parent != NULL){

					if(node->parent->right == node)	node->parent->right = avl_rightRotate(node);
					else node->parent->left = avl_rightRotate(node);
				
				}
				else
					tree->root = avl_rightRotate(node);


				//Update height from the critical node upwards.
				updateHeight(node);

			} else if(getBalanceFactor(node) < 0 && getBalanceFactor(*directionPointer) < 0){
				printf("Right right imbalance\n");

				/*********************
				Right right imbalance, right rotate on the critical node.
				**********************/

				if(node->parent != NULL){
					if(node->parent->right == node) node->parent->right = avl_leftRotate(node);
					else node->parent->left = avl_leftRotate(node);
				}
				else
					tree->root = avl_leftRotate(node);

				updateHeight(node);

			} else if(getBalanceFactor(node) > 0 && getBalanceFactor(*directionPointer) < 0){

				/*********************
				Left right imbalance, left rotate on the left child of the critical node 
				and then right rotate on the critical node itself.
				**********************/
				printf("Left right imbalance\n");

				node->left = avl_leftRotate(node->left);

				updateHeight(node->left->left);

				if(node->parent != NULL){
					if(node->parent->right == node) node->parent->right = avl_rightRotate(node);
					else node->parent->left = avl_rightRotate(node);
				}
				else
					tree->root = avl_rightRotate(node);


				updateHeight(node);
			} else if (getBalanceFactor(node) < 0 && getBalanceFactor(*directionPointer) > 0){

				/*********************
				Right left imbalance, right rotate on the right child of the critical node
				and then left rotate on the critical node itself.
				**********************/
				printf("Right left imbalance\n");

				node->right = avl_rightRotate(node->right);

				updateHeight(node->right->right);

				if(node->parent != NULL){
					if(node->parent->right == node) node->parent->right = avl_leftRotate(node);
					else node->parent->left = avl_leftRotate(node);
				}
				else
					tree->root = avl_leftRotate(node);

				updateHeight(node);

			} else{
				printf("No cases found.\n");
			}
		}

		//points to whether the traversal is from the left child or from the right child.
		if(node->parent != NULL){
			directionPointer = (node->parent->left == node) ? &node->parent->left : &node->parent->right;
			// printf("Pointer BF: %d , Node: %d , Parent: %d \n", getBalanceFactor(*directionPointer), (*directionPointer)->key, (*directionPointer)->parent->key);
		}

		node = node->parent;
	}
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
	if (node == NULL){ 						//Returns the node to be inserted to fill the value of the last iteration of recursion
		return toInsert;					//means that the left/right pointer of the last node is already NULL
	} else if (node->key == toInsert->key){
		printf("Key is already present in the BST.\n");
		return node;						//returns node if the key is equal, doesn't add to the main BST
	} else if (node->key > toInsert->key){
		if(node->left == NULL){ 			//catches the null left pointer to avoid segmentation fault
			toInsert->parent = node;		//if the next iteration will be the last iteration, assign parent.
		}
		node->left = insertNode(node->left, toInsert);  //recurse tree to insert value on the left
	} else if (node->key < toInsert->key){ 
		if(node->right == NULL){ 						//catches the null right pointer instance to avoid segmentation fault
			toInsert->parent = node;					//if the next iteration will be the last iteration, assign parent.
		}
		node->right = insertNode(node->right, toInsert); //recurse tree to insert value on the right
	}
}

void insert(BST* B, BST_NODE* node){
	if(isFull(B) == 0){ 			//checks if the BST B is full
		if(B->root == NULL){		 //if the BST is empty
			B->root = node; 		 //the node to be created will automatically be the first and only node(root)
		} else if(B->root->key > node->key){ //if the node to insert is lower
			insertNode(B->root, node);		//call the helper function
		} else if(B->root->key < node->key){ //if the node to insert is higher
			insertNode(B->root, node); 		//call helper function
		}
	}

	updateHeight(node);
	avl_fixup(B, node);

	B->size ++; //Update Size of the tree
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
		keyPointer = node; 							//if the key is not in the tree, returns NULL, else, returns the node address.
	} else if(node->key < data){
		keyPointer = searchKey(node->right, data);  //search in the right side of the tree
	} else if(node->key > data){
		keyPointer = searchKey(node->left, data);   //search in the left side of the tree
	} else
		exit(1);

	return keyPointer; 							    //returns the pointer to the node
}

BST_NODE* search(BST* B, int key){
	BST_NODE* keyPointer = NULL;

	if(isEmpty(B) == 0){
		if(B->root == NULL){
			keyPointer = B->root;                 //return NULL
		} else{
			keyPointer = searchKey(B->root, key); //search for the value of node with the key
		}
	} else{
		printf("The tree is empty. \n");		//Empty tree prompt
	}

	return keyPointer;							//Return the address
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
		printf("%d ", root->key);        //Root
		preOrderWalkHelper(root->left);	 //Left
		preOrderWalkHelper(root->right); //Right
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
		inorderWalkHelper(root->left);   //left
		printf("%d ", root->key);		 //root
		inorderWalkHelper(root->right);	 //right
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
		postorderWalkHelper(root->left); //left
		postorderWalkHelper(root->right);//right
		printf("%d ", root->key);		 //root
	}
}

void postorderWalk(BST* B){
	postorderWalkHelper(B->root);
	printf("\n");
}

/*
** function: minimum
** requirements:
    a non-null BST pointer
    a non-empty BST
    an integer `key`
** results:
    finds the leftmost node from BST `B` and returns its node pointer if found, 
        otherwise, return `NULL`
*/
BST_NODE* minHelper(BST_NODE* root){
	BST_NODE* min = root;
	if(root == NULL && root->parent == NULL) printf("There is no successor. \n");
	else if(min->left == NULL){                //If the left of the right sub tree is NULL
		return min;
	}
	else{
		while(min->left != NULL){
			min = min->left;              //Traverse to the leftmost node of the node
		}
	}
	return min;

}

BST_NODE* minimum(BST* B){

	if(B == NULL) printf(" Tree is NULL. \n");
	else return minHelper(B->root);
}


/*
** function: minimum
** requirements:
    a non-null BST pointer
    a non-empty BST
    an integer `key`
** results:
    finds the rightmost node from BST `B` and returns its node pointer if found, 
        otherwise, return `NULL`
*/

BST_NODE *maxHelper(BST_NODE* root){
	BST_NODE *max = root;

	if(root == NULL) printf(" Root is NULL. \n");
	else if(max->right == NULL){
		return max;
	}
	else{
		while(max->right != NULL){
			max = max->right;
		}
	}
	
	return max;
}

BST_NODE* maximum(BST* B){
	if(B == NULL) printf(" Tree is NULL. \n");
	else{
		BST_NODE *max = maxHelper(B->root);
		return max;		
	}
}

/*
** function: predecessor
** requirements:
    a non-null BST_NODE pointer
** results:
    returns the node pointer of this node's predecessor, if it exists
    otherwis, return `NULL`
*/
BST_NODE* predecessor(BST_NODE* node){
	BST_NODE* parentcessor;

	if(node == NULL) printf(" Node is NULL. \n");
	else if(node ->left == NULL && node->parent != NULL){
		BST_NODE* temp = node;

		if(temp->parent != NULL && temp->key >= node->parent->key){
			return temp->parent;
		}
		else return NULL;
	}
	else
		return maxHelper(node->left);
}

/*
** function: successor
** requirements:
    a non-null BST_NODE pointer
** results:
    returns the node pointer of this node's successor, if it exists
    otherwis, return `NULL`
*/
BST_NODE* successor(BST_NODE* node){
	if(node == NULL) printf(" Node is NULL. \n");
	else if(node ->right == NULL && node->parent != NULL){
		BST_NODE* temp = node;

		if(temp->parent != NULL && temp->key <= node->parent->key){
			return temp->parent;
		} else
			return NULL;
	}
	else 
		return minHelper(node->right);
}


/*
** function: remove
** requirements:
    a non-null BST pointer
    a non-empty BST
    an integer `key`
** results:
    finds `key` and delete's it node from the BST `B`
    if found, delete then, return key
    otherwise, return 0

*/

BST_NODE* deleteHelper(BST_NODE *toDelete, int key){
	BST_NODE** toDeletePos; 				//Pointer to a pointer (left or right pointer of the parent)
	BST_NODE* newRoot; 						//Pointer to be used for repointing roots

	if(toDelete->left == NULL && toDelete->right == NULL){ //If the node has no child
		
		if(toDelete->parent != NULL){ 						//If the node is not the root
			toDeletePos = (toDelete->parent->right == toDelete) ? &toDelete->parent->right: &toDelete->parent->left;
			(*toDeletePos) = NULL; 							//Set the value of the parent pointer to left/right to NULL before deletion
			updateHeight(toDelete->parent);
		}
		
		free(toDelete);
	} 

	//If the node has one child
	else if(toDelete->left != NULL && toDelete->right == NULL || toDelete->left == NULL && toDelete->right != NULL){
	
		if(toDelete->parent != NULL){      //If the node is not the root
	
			//Points the left/right pointer of the parent of the node to be deleted to its only child
			toDeletePos = (toDelete->parent->right == toDelete) ? &toDelete->parent->right: &toDelete->parent->left;

			//Points to the only child
			(*toDeletePos) = (toDelete->left == NULL) ? toDelete->right : toDelete->left;


			//Point the parent of the child to the parent of the node to be deleted
			(*toDeletePos)->parent = toDelete->parent;

			updateHeight(toDelete->parent);
			free(toDelete);
	
		} else{ //If the node with one child is the root

			//Points the left/right pointer of the node to be deleted to its only child
			toDeletePos = (toDelete->left == NULL) ? &toDelete->right: &toDelete->left;

			//Assigns deletion pointer to the only child of the node to be deleted
			toDelete = (toDelete->left == NULL) ? toDelete->right : toDelete->left;

			//Copies the key of the only child
			toDelete->parent->key = toDelete->key;

			//points new root to the memory of the parent(existing root)
			newRoot = toDelete->parent;
			updateHeight(toDelete->parent);

			(*toDeletePos) = NULL;
			//Free the only child and remove link from the parent
			free(toDelete);


			return newRoot; //Return to the main delete function for assignment as a new root
		}
	} 
	//If the node has 2 children
	else if(toDelete->left != NULL && toDelete->right != NULL){
		
		//if there is a successor, swap keys and then assign deletion pointer to the successor
		if(successor(toDelete) != NULL){
			int temp = toDelete->key;
			toDelete->key = successor(toDelete)->key;
			successor(toDelete)->key = temp;
	
			toDelete = successor(toDelete);
		}
		else{
			printf("successor is NULL\n");
		}

		//Delete the successor
		deleteHelper(toDelete, key); //Recursion process
	
	}
}

int delete(BST* B, int key){
	BST_NODE* toDelete;
	BST_NODE** toDeletePos;
	BST_NODE* tempCritNode;

	if(B == NULL) printf("Tree is NULL\n");
	else if(B->root == NULL) printf(" Tree doesn't have any nodes. \n");
	else{
		toDelete = search(B, key);

		//If the first and only node is to be deleted.
		if(toDelete->left == NULL && toDelete->right == NULL && toDelete->parent == NULL){

			printf("Deleting first and only node\n");
			B->root = NULL; 
			free(toDelete);

		} 
		//if the node to be deleted has no child
		else if(toDelete->left == NULL && toDelete->right == NULL){
			tempCritNode = toDelete->parent;

			printf("Deleting no child.\n");
			deleteHelper(toDelete, key);
			printf("Key of parent: %d \n", tempCritNode->key);
			avl_fixup(B, tempCritNode);

		} 
		//If the node has one child
		else if(toDelete->left != NULL && toDelete->right == NULL || toDelete->left == NULL && toDelete->right != NULL){
			tempCritNode = toDelete;
			
			if(toDelete->parent == NULL){
				B->root = deleteHelper(toDelete,key);
			}
			else deleteHelper(toDelete,key);


			avl_fixup(B, tempCritNode);
		} //If the node has 2 children
		else if(toDelete->left != NULL && toDelete->right != NULL){
			tempCritNode = toDelete;

			deleteHelper(toDelete, key);

			avl_fixup(B, tempCritNode);			
		}
		B->size --;

		return key;
	}
}


/*
** function: clear
** requirements:
    a non-null BST pointer
** results:
    removes all data items in the BST
*/
void clear(BST* B){
	if (B->root == NULL){
		printf("Tree is already empty.\n");
		return;
	}
	while(B->root != NULL){ //Continuous deletion at head of the BST.
		delete(B, B->root->key);
	}
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