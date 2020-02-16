CC = gcc
CFLAGS = -O

default: run

run: build
	./run < program.cs
build: compile
	$(CC) -o run main.o list.o
compile: main.c list.c list.h
	$(CC) -c main.c
	$(CC) -c list.c
clean:
	$(RM) *.o *.gch
