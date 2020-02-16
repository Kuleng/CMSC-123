#include <stdio.h>
#include <stdlib.h>

//Binary search tree declaration
typedef struct BST_tag{
	struct BST_tag* root;
	struct BST_tag* left;
	struct BST_tag* right;
	int key;
}BST;

//newNode function
BST* newNode(int data){
	BST *temp = (BST*)malloc(sizeof(BST)); 
    temp->key = data;
    temp->left = temp->right = NULL;

    return temp; 
}

//print function
void printInOrder(BST *root){
	if (root != NULL){
		printInOrder(root->left);
		printf("%d \n", root->key);
		printInOrder(root->right);
	}
}

//insert function, connected to newNode
BST* insert(BST *root, int key){
	if (root == NULL){
		return newNode(key);
	} else if (root->key < key){
		root->right = insert(root->right, key);
	} else if (root->key > key){
		root->left = insert(root->left, key);
	} else if (root->key == key){
		printf("key is equal\n");
	}
}

BST *search(BST *root, int key){
	if (root == NULL || root->key == key){
		return root;
	} else if (root->key < key){
		return search(root->right, key);
	} else if (root->key > key){
		return search(root->left, key);
	}
}

int main(){
	BST *mainRoot = NULL;


	mainRoot = insert(mainRoot, 2);
	insert(mainRoot, 1);
	insert(mainRoot, 4);
	insert(mainRoot, 4);
	insert(mainRoot, 3);

	printInOrder(mainRoot);

	BST *toFind = search(mainRoot, 3);
	printf("%d \n", toFind->key);
	toFind = search(mainRoot, 1);
	printf("%d \n", toFind->key);
	toFind = search(mainRoot, 5);
	printf("%d \n", toFind->key);


	return 0;
}