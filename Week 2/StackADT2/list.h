#ifndef _LIST_H_
#define _LIST_H_

typedef struct node_tag{
	int value;
	struct node_tag* next;
}NODE;


typedef struct list_tag{
	NODE* head;
	NODE* tail;
	int length;
	int maxLength;
}LIST;

/*
** requirements:
	an integer data
** results:
	creates an empty node with value `data`
	initializes fields of the structure
	returns the created node
*/
NODE* createNode(int data);

/*
** requirements: none
** results:
	creates an empty list with specified max length
	initializes fields of the structure
	returns the created node
*/
LIST* createList(int maxLength);

/*
** requirements: none
** results:
	returns 1 if the list is full; 
	otherwise return 0
*/
int isFull(LIST *L);
/*
** requirements: none
** results:
	returns 1 if the list is empty; 
	otherwise return 0
*/
int isEmpty(LIST *L);

/*
** requirements:
	List must not be full.
	index must be between 0 and list length.

** results: inserts `node` at position `index` of the list.

** sample: L = [12, 6, 4, 10]
** insertAt(L, 2, 55) -> L = [12, 6, 55, 4, 10]
** insertAt(L, 0, 44) -> L = [44, 12, 6, 55, 4, 10]
** insertAt(L, 5, 66) -> L = [44, 12, 6, 55, 4, 66, 10]
*/
void insertAt(LIST *L, int index, NODE* node);

/*
** requirements:
	List must not be empty.
	index must be between 0 and list length minus 1
** results:
	deletes node at position `index` of the list
	returns the value of the deleted node.
** sample: L = [44, 12, 6, 55, 4, 10, 66]
** deleteAt(L, 2) -> L = [44, 12, 55, 4, 10, 66]; returns 6
** deleteAt(L, 0) -> L = [12, 55, 4, 10, 66]; return 44
** deleteAt(L, 4) -> L = [12, 55, 4, 10]; returns 66
*/
int deleteAt(LIST *L, int index);


/*
** requirements: list is not empty
** results:
	deletes all nodes of the list the list
*/
void clear(LIST *L);

/*
** requirements: none
** results:
	if list is empty, prints "*empty*"
	otherwise, prints the contents of a list
*/
void show(LIST *L);

#endif
