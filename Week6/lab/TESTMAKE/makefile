CC = gcc
CFLAGS = -o

run: build
	./run < test.cs
build: compile
	$(CC) $(CFLAGS) run main.o heap.o
compile: main.c heap.c
	$(CC) -c main.c heap.c
clean:
	$(RM) *.o *.gch