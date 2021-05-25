CFLAGS = -Wall -Wextra -g -fprofile-arcs -ftest-coverage
all: graph rm

graph: errors.o queue.o graph.o test.o
	gcc errors.o queue.o graph.o test.o -o graph ${CFLAGS}

errors.o: errors.c
	gcc -c errors.c ${CFLAGS}

queue.o: queue.c
	gcc -c queue.c ${CFLAGS}

graph.o: graph.c
	gcc -c graph.c ${CFLAGS}

test.o: test.c
	gcc -c test.c ${CFLAGS}

rm:
	rm *.o