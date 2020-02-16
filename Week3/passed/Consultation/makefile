CC = gcc
CFLAGS = -o

run1: build1
	./run1 < test.cs
build1: compile1
	$(CC) -o run1 main.o BST_final.o
compile1: main.c BST_final.c
	$(CC) -c main.c BST_final.c

clean:
	$(RM) *.o *.gch