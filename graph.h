#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "errors.h"


struct Vertex
{
	int num;
	struct Vertex* next;
	double weight; // вес исходящего из вершины ребра
};

struct Graph
{
	int numVertices;
	struct Vertex** adjLists; // массив списков смежных вершин
	// в каждой строке этого массива хранится вершина графа по номеру.
	// эта вершина - типо head в list. Соответственно от head через *next
	// формируется список смежных вершин с данной.
};


error_t addVertex(struct Vertex ** out, int val);
error_t createGraph( struct Graph ** out, int numVertices);
error_t addEdge(struct Graph* graph, int start, int final, double weight);
error_t findWeightestEdge(double* out, struct Graph *graph);
error_t printGraph(struct Graph *graph);
error_t degree(int* out, struct Graph *graph, int num);
error_t deleteGraph(struct Graph *graph);

error_t dijkstra(struct Graph *graph, int start);