#include "graph.h"


void dijkstra_test_dataset() {

  struct Graph *graph = createGraph(6);

  addEdge(graph, 0, 1, 7);
  addEdge(graph, 0, 5, 14);
  addEdge(graph, 0, 2, 9);
  addEdge(graph, 1, 0, 7);
  addEdge(graph, 1, 2, 10);
  addEdge(graph, 1, 3, 15);
  addEdge(graph, 2, 0, 9);
  addEdge(graph, 2, 1, 10);
  addEdge(graph, 2, 3, 11);
  addEdge(graph, 2, 5, 2);
  addEdge(graph, 3, 1, 15);
  addEdge(graph, 3, 2, 11);
  addEdge(graph, 3, 4, 6);
  addEdge(graph, 4, 3, 6);
  addEdge(graph, 4, 5, 9);
  addEdge(graph, 5, 4, 9);
  addEdge(graph, 5, 2, 2);
  addEdge(graph, 5, 0, 14);
  // 1 до 2-й составляет 7, до 3-й — 9, до 4-й — 20, до 5-й — 20, до 6-й — 11.

  printGraph(graph);

  dijkstra(graph, 0);
}

int main() {

  dijkstra_test_dataset();

  return 0;
}
