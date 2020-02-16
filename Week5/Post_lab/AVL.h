#ifndef _AVL_H_
#define _AVL_H_

#include <stddef.h>
#include "BST.h"
// AVL is a BST wherein the height of the tree is ensured to be log(N)
// where N is the number of nodes

// AVL_NODE is a BST_NODE
typedef BST_NODE AVL_NODE;

// AVL is a BST
typedef BST AVL;

// aliasing pointers as another data type
// to reduce complexity of *stars*
typedef AVL* AVL_PTR;
typedef AVL_NODE* AVL_NODE_PTR;

/*
** function: createAVLNode
** requirements:
    an integer indicating the key of the node
** results:
    creates an AVL node with fields initialized
    returns a pointer of this instance
*/
AVL_NODE_PTR createAVLNode(int key);
/*
** function: createAVL
** requirements:
    an integer indicating the maximum size of the AVL
        i.e. the maximum number of elements that can be stored
** results:
    creates an empty AVL with fields initialized
    returns a pointer of this instance
*/
AVL_PTR createAVL(int max);

/*
** function: leftRotate
** requirements:
    a non-null node
** results:
    rotates the tree (or subtree) rooted at `node` to the left
    returns a pointer of the new root of the (sub)tree a.k.a. "promoted node"
*/
AVL_NODE_PTR leftRotate(AVL_NODE_PTR node);

/*
** function: rightRotate
** requirements:
    a non-null node
** results:
    rotates the tree (or subtree) rooted at `node` to the right
    returns a pointer of the new root of the (sub)tree a.k.a. "promoted node"
*/
AVL_NODE_PTR rightRotate(AVL_NODE_PTR node);

/*
** function: avlInsert
** requirements:
    a non-null AVL pointer and a non null node pointer
** results:
    inserts the given node, `node`, to the AVL tree described by `A`
*/
void avLInsert(AVL_PTR A, AVL_NODE_PTR node);

#endif