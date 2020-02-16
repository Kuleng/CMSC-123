CC = gcc

run : build
	./run < program.cs
build: compile
	$(CC) -o run main.o hashtable.o
compile: main.c hashtable.c
	$(CC) -c main.c hashtable.c
clean:
	$(RM) *.o *.gch