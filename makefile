CFLAGS = -Wall -g -fprofile-arcs -ftest-coverage
all: graph rm

graph: queue.o graph.o test.o
	gcc queue.o graph.o test.o -o graph ${CFLAGS}

queue.o: queue.c
	gcc -c queue.c

graph.o: graph.c
	gcc -c graph.c

test.o: test.c
	gcc -c test.c

rm:
	rm *.o