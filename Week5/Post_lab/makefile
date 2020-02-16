CC = gcc
CFLAGS = -o
file = main.c BST.c AVL.c


run1: build1
	./run1 < test.cs
build1: compile1
	$(CC) -o run1 main.o BST.o AVL.o
compile1: main.c BST.c BST.h AVL.c AVL.h
	$(CC) -c main.c BST.c BST.h AVL.c AVL.h
clean:
	$(RM) *.o *.gch