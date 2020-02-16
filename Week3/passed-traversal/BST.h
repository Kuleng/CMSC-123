#ifndef _BST_H_
#define _BST_H_

typedef struct bst_node{
    // left pointer
    struct bst_node* left;

    // right pointer 
    struct bst_node* right;

    // up or parent pointer
    // for easier implementation of operations
    struct bst_node* parent;

    // key of this node (used to compare)
    int key;

    // path length from this node to the deepest leaf
    int height;
} BST_NODE;

typedef struct bst{
    // the root of the tree
    BST_NODE* root;

    // the maximum number of elements w/c can be stored
    int maxSize;

    // the current number of elements stored.
    int size;
}BST;

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
BST_NODE* createBSTNode(int key, BST_NODE* L, BST_NODE* R, BST_NODE* P);


/*
** function: createBST
** requirements:
    an integer indicating the maximum size of the BST
        i.e. the maximum number of elements that can be stored
** results:
    creates an empty BST with fields initialized
    returns a pointer of this instance
*/
BST* createBST(int max);

/*
** function: isEmpty
** requirements:
    a non-null BST pointer
** results:
    returns 1 if BST is empty;
    otherwise, return 0
*/
int isEmpty(BST* B);

/*
** function: isFull
** requirements:
    a non-null BST pointer
** results:
    returns 1 if BST is full;
    otherwise, return 0
*/
int isFull(BST* B);

/*
** function: insert
** requirements:
    a non-null BST pointer
    a non-full BST
    a non-null BST_NODE pointer
** results:
    inserts the given `node` to the BST `B`
*/
void insert(BST* B, BST_NODE* node);

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
BST_NODE* search(BST* B, int key);

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
int delete(BST* B, int key);

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
BST_NODE* minimum(BST* B);


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
BST_NODE* maximum(BST* B);

/*
** function: predecessor
** requirements:
    a non-null BST_NODE pointer
** results:
    returns the node pointer of this node's predecessor, if it exists
    otherwis, return `NULL`
*/
BST_NODE* predecessor(BST_NODE* node);

/*
** function: successor
** requirements:
    a non-null BST_NODE pointer
** results:
    returns the node pointer of this node's successor, if it exists
    otherwis, return `NULL`
*/
BST_NODE* successor(BST_NODE* node);

/*
** function: showTree
** requirements:
    a non-null BST pointer
** results:
    displays elements of the BST in tree mode.
*/
void showTree(BST* B);

/*
** function: preorderWalk
** requirements:
    a non-null BST pointer
** results:
    displays a list of elements of the BST using `pre-order traversal`
*/
void preorderWalk(BST* B);

/*
** function: inorderWalk
** requirements:
    a non-null BST pointer
** results:
    displays a list of elements of the BST using `in-order traversal`
*/
void inorderWalk(BST* B);

/*
** function: postorderWalk
** requirements:
    a non-null BST pointer
** results:
    displays a list of elements of the BST using `post-order traversal`
*/
void postorderWalk(BST* B);

/*
** function: clear
** requirements:
    a non-null BST pointer
** results:
    removes all data items in the BST
*/
void clear(BST* B);

#endif