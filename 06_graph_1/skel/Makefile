CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99
DEBUG=-g -ggdb -O0 -march=native

build: TestFunctions Test clean

Test: src/Test.o src/Queue.o src/Stack.o src/LinkedList.o src/MatrixGraph.o src/GraphUtils.o src/ListGraph.o
	$(CC) $(CFLAGS) $(DEBUG) $^ -o $@

TestFunctions: src/TestFunctions.o src/Queue.o src/Stack.o src/LinkedList.o src/MatrixGraph.o src/GraphUtils.o src/ListGraph.o
	$(CC) $(CFLAGS) $(DEBUG) $^ -o $@

src/MatrixGraph.o: src/MatrixGraph.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

src/ListGraph.o: src/ListGraph.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

src/Queue.o: src/Queue.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

src/Stack.o: src/Stack.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

src/LinkedList.o: src/LinkedList.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

src/GraphUtils.o: src/GraphUtils.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

src/Test.o: src/Test.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

src/TestFunctions.o: src/TestFunctions.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

run:
	./Test

clean:
	rm src/*.o
