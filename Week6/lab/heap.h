#ifndef _HEAP_H_
#define _HEAP_H_

typedef enum HeapType {MINHEAP, MAXHEAP} htype;

typedef struct heap_tag {
  int *heap;
  int size;
  int maxSize;
  htype type;
} HEAP;

void printHeap(HEAP *H);

/*
 *  requirements: none
 *  results:
    creates an integr array with size = maxSize+1
      the +1 is needed since this implementation
      will be using index 1 as the root of the heap
    initializes fields of the structure
    returns the created heap
*/
HEAP* createHeap(int maxSize, htype type);

/*
 *  requirements: none
 *  results:
      return 1 if the heap is full;
      otherwise return 0
*/
int isFull(HEAP *H);

/*
 *  requirements: none
 *  results:
      return 1 if the heap is empty;
      otherwise return 0
*/
int isEmpty(HEAP *H);

/*
 *  requirements:
      a non-null HEAP pointer
      a non-full *heap
 *  results:
      inserts `key` to the `heap`
*/
void insert(HEAP *H, int key);

/*
 *  requirements:
      a non-null HEAP pointer
      a non-empty *heap
 *  results:
      removes the minimum value (root) from the heap (if MINHEAP)
	  removes the maximum value (root) from the heap (if MAXHEAP)
      returns the deleted value
*/
int delete(HEAP *H);

/*
 *  requirements:
      a non-null HEAP pointer
      a non-empty *heap
 *  results:
 	  deletes all the items in the heap
*/
void clear(HEAP *H);

/*
 *  requirements:
      a non-null HEAP pointer
      a non-empty *heap
 *  results:
 	  returns an array containing the sorted values of the heap
	  (must not modify the original heap)
*/
int * heapSort(HEAP *H);

#endif
