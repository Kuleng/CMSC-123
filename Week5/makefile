CC = gcc
CFLAGS = -o

run1: build1
	./run1 < test.cs
build1: compile1
	$(CC) -o run1 main.o BST.o
compile1: main.c BST.c
	$(CC) -c main.c BST.c
clean:
	$(RM) *.o *.gch