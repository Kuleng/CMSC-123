CC = gcc

run : build
	./run < input.in
build : compile
	$(CC) -o run main.o
compile: main.c
	$(CC) -c main.c
clean:
	$(RM) *.o *.gch