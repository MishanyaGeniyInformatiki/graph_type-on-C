#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

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


struct Vertex* addVertex(int val);
struct Graph* createGraph(int numVertices);
void addEdge(struct Graph* graph, int start, int final, double weight);
int findWeightestEdge(struct Graph* graph);
void printGraph(struct Graph* graph);
int degree(struct Graph* graph, int num);

void dijkstra(struct Graph* graph, int start);

void dijkstra_test_dataset();