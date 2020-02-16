CC = gcc
CFLAGS = -O

default: run3
	
run3: build3
	./run3
build3: compile3
	$(CC) -o run3 postfix2.o stack.o list2.o
compile3:
	$(CC) -c postfix2.c stack.c list2.c

clean:
	$(RM) *.o *.gch
