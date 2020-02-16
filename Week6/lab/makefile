CC = gcc
CFLAGS = -o

run: build
	./run < test.cs
build: compile
	$(CC) $(CFLAGS) run main.o heap_final.o
compile: main.c heap_final.c
	$(CC) -c main.c heap_final.c
clean:
	$(RM) *.o *.gch