#include "AVL.h"
#include "BST.h"
#include <stdio.h>
#include <stdlib.h>

AVL_NODE_PTR createAVLNode(int key){
	return createBSTNode(key, NULL, NULL, NULL);
}

AVL_PTR createAVL(int max){
	return createBST(max);
}


int getBalanceFactor(AVL_NODE_PTR node){
	if(node == NULL) return -1;

	int left_height = (node->left == NULL) ? -1 : node->left->height;
	int right_height = (node->right == NULL) ? -1 : node->right->height;

	return (left_height - right_height);
}

/*
** function: leftRotate
** requirements:
    a non-null node
** results:
    rotates the tree (or subtree) rooted at `node` to the left
    returns a pointer of the new root of the (sub)tree a.k.a. "promoted node"
*/
AVL_NODE_PTR leftRotate(AVL_NODE_PTR node){

	node->right->parent = node->parent;
	node->parent = node->right;
	node->right = node->parent->left;
	node->parent->left = node;
	if(node->right != NULL) node->right->parent = node;

	return node->parent; //newRoot of the subtree rotated
}

/*
** function: rightRotate
** requirements:
    a non-null node
** results:
    rotates the tree (or subtree) rooted at `node` to the right
    returns a pointer of the new root of the (sub)tree a.k.a. "promoted node"
*/
AVL_NODE_PTR rightRotate(AVL_NODE_PTR node){
	node->left->parent = node->parent;
	node->parent = node->left;
	node->left = node->parent->right;
	node->parent->right = node;
	if(node->left != NULL) node->left->parent = node;

	return node->parent; //newRoot of the subtree rotated
}

/*
** function: avlInsert
** requirements:
    a non-null AVL pointer and a non null node pointer
** results:
    inserts the given node, `node`, to the AVL tree described by `A`
*/
void avLInsert(AVL_PTR A, AVL_NODE_PTR node){
	AVL_NODE_PTR* directionPointer = NULL;


	//Insert the node via BST insert.
	insert(A, node);

	while (node != NULL){


		if( abs(getBalanceFactor(node)) >= 2){
			//Imbalance
			if(getBalanceFactor(node) < 0 && getBalanceFactor(*directionPointer) < 0){
				/*****************
					Right right imbalance, left rotate on the critical node, and then updateHeight from
					it after demotion
				***************/
				if(node->parent != NULL){
					if(node->parent->right == node) node->parent->right = leftRotate(node);
					else node->parent->left = leftRotate(node);
				}
				else{
					A->root = leftRotate(node);
				}

				updateHeight(node);

			} else if(getBalanceFactor(node) > 0 && getBalanceFactor(*directionPointer) > 0){
				/*****************
					Left left imbalance, Right rotate on the critical node, and then updateHeight from
					it after demotion
				***************/		
				if(node->parent != NULL){
					if(node->parent->right == node) node->parent->right = rightRotate(node);
					else node->parent->left = rightRotate(node);
				}
				else{
					A->root = rightRotate(node);
				}

				updateHeight(node);

			} else if(getBalanceFactor(node) < 0 && getBalanceFactor(*directionPointer) > 0){
				/*****************
					Right left imbalance. Right rotate on the Right child and then
				update from the node's right->right ( which is the demoted critical node of
				the right sub tree)
				***************/
				node->right = rightRotate(node->right);

				updateHeight(node->right->right);

				/*****************
					Perform basic left rotation on the criticalnode
					and then update height from the demoted critical node upwards
				***************/
				if(node->parent != NULL){
					if(node->parent->right == node) node->parent->right = leftRotate(node);
					else node->parent->left = leftRotate(node);
				}
				else{
					A->root = leftRotate(node);
				}

				updateHeight(node);
			} else if(getBalanceFactor(node) > 0 && getBalanceFactor(*directionPointer) < 0){
				/*****************
					Left right imbalance. Left rotate on the left child and then
				update from the node's left->left ( which is the demoted critical node of
				the left sub tree)
				***************/
				
				node->left = leftRotate(node->left);

				updateHeight(node->left->left);

				/*****************
					Perform basic right rotation on the critical node
					and then update height from the demoted critical node upwards
				***************/
				if(node->parent != NULL){
					if(node->parent->right == node) node->parent->right = rightRotate(node);
					else node->parent->left = rightRotate(node);
				}
				else{
					A->root = rightRotate(node);
				}

				updateHeight(node);
			}

		}

		/*****************
			Pointer to a pointer to know the path of the upward traversal
		***************/
		if(node->parent != NULL) 
			directionPointer = (node->parent->right == node) ? &node->parent->right : &node->parent->left;

		node = node->parent;
	}
}


void avl_fixup(AVL_PTR tree, AVL_NODE_PTR node){
	AVL_NODE_PTR child, grandchild;

	while(node != NULL){

		if(abs(getBalanceFactor(node)) >= 2){
			//Finding the unbalanced node
			int left_height = (node->left == NULL) ? -1 : node->left->height;
			int right_height = (node->right == NULL) ? -1 : node->right->height;
			
			child = (left_height > right_height) ? node->left : node->right;
			
			//Grand child may be null in cases of the child of node having 0 children.
			if(child != NULL){
				int child_left_height = (child->left == NULL) ? -1 : child->left->height;
				int child_right_height = (child->right == NULL) ? -1 : child->right->height;
				grandchild = (child_left_height > child_right_height) ? child->left : child->right;
			}

			//Perform rotations
			//Imbalance
			if(getBalanceFactor(node) < 0 && getBalanceFactor(child) <= 0){
				/*****************
					Right right imbalance, left rotate on the critical node, and then updateHeight from
					it after demotion
				***************/
				if(node->parent != NULL){
					if(node->parent->right == node) node->parent->right = leftRotate(node);
					else node->parent->left = leftRotate(node);
					}
				else
					tree->root = leftRotate(node);
				
				updateHeight(node);

			}else if(getBalanceFactor(node) > 0 && getBalanceFactor(child) >= 0){
				/*****************
					Left left imbalance, Right rotate on the critical node, and then updateHeight from
					it after demotion
				***************/	
				if(node->parent != NULL){
					if(node->parent->right == node) node->parent->right = rightRotate(node);
					else node->parent->left = rightRotate(node);
					}
				else
					tree->root = rightRotate(node);

				updateHeight(node);
				} else if(getBalanceFactor(node) < 0 && getBalanceFactor(child) >= 0){
					/*****************
						Right left imbalance. Right rotate on the Right child and then
					update from the node's right->right ( which is the demoted critical node of
					the right sub tree)
					***************/
					node->right = rightRotate(node->right);
					updateHeight(node->right->right);
					/*****************
						Perform basic left rotation on the criticalnode
						and then update height from the demoted critical node upwards
					***************/
				
					if(node->parent != NULL){
						if(node->parent->right == node) node->parent->right = leftRotate(node);
						else node->parent->left = leftRotate(node);
					}
					else{
						tree->root = leftRotate(node);
					}
						updateHeight(node);
					} 

				else if(getBalanceFactor(node) > 0 && getBalanceFactor(child) <= 0){
					/*****************
						Left right imbalance. Left rotate on the left child and then
					update from the node's left->left ( which is the demoted critical node of
					the left sub tree)
					***************/
						
					node->left = leftRotate(node->left);

					updateHeight(node->left->left);
					/*****************
						Perform basic right rotation on the critical node
						and then update height from the demoted critical node upwards
					***************/
					if(node->parent != NULL){
						if(node->parent->right == node) node->parent->right = rightRotate(node);
						else node->parent->left = rightRotate(node);
					}
					else
						tree->root = rightRotate(node);
					
					updateHeight(node);
				}
			}
		node = node->parent;
	}
}

int avlDelete(AVL_PTR tree, int key){
	AVL_NODE_PTR toDelete = search(tree, key);
	AVL_NODE_PTR node;
	int tempKey;

	if(toDelete->left == NULL || toDelete->right == NULL){
		//If there's a null, no child or one child
		AVL_NODE_PTR temp = (toDelete->left == NULL) ? toDelete->right : toDelete->left;

		/*******
			Assigning of Node M, based on the number of its child. if temp is NULL, there is no child and
			M will be the parent of the node to be deleted, else, the only child will be the M
		***********/
		node = (temp == NULL) ? toDelete->parent : temp;

		tempKey = delete(tree, key);

		avl_fixup(tree, node);

		return tempKey;
	}
	else{
		//2 children case
		/*******
			finds the successor of the node to be deleted, apply basic BST deletion and then
			assign M to the parent of that successor. that will be the node M and then
			the child and grandchildren will be identified through the fix up function.
		***********/
		AVL_NODE_PTR temp = successor(toDelete)->parent;

		//Delete the key
		tempKey = delete(tree, key);

		//re-balance the tree using the acquired unbalanced nodes
		avl_fixup(tree, temp);

		return tempKey;
	}
}