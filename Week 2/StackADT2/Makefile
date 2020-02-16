CC = gcc
CFLAGS = -O

default: run3

run1: build1
	./run1 < program1.cs
build1: compile1
	$(CC) -o run1 main1.o queue.o list.o
compile1: main1.c queue.h queue.c list.h list.c
	$(CC) -c main1.c queue.c list.c

run2: build2
	./run2 < program2.cs
build2: compile2
	$(CC) -o run2 main2.o stack.o list.o
compile2: main2.c stack.h stack.c list.h list.c
	$(CC) -c main2.c stack.c list.c

run3: build3
	./run3
build3: compile3
	$(CC) -o run3 postfix2.o stack.o list2.o
compile3:
	$(CC) -c postfix2.c stack.c list2.c

clean:
	$(RM) *.o *.gch
