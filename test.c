#include "errors.c"
#include "graph.h"


void dijkstra_test_dataset() {

  struct Graph *graph;
  createGraph(&graph, 6);

  error_catcher(addEdge(graph, 0, 1, 7));
  error_catcher(addEdge(graph, 0, 5, 14));
  error_catcher(addEdge(graph, 0, 2, 9));
  error_catcher(addEdge(graph, 1, 0, 7));
  error_catcher(addEdge(graph, 1, 2, 10));
  error_catcher(addEdge(graph, 1, 3, 15));
  error_catcher(addEdge(graph, 2, 0, 9));
  error_catcher(addEdge(graph, 2, 1, 10));
  error_catcher(addEdge(graph, 2, 3, 11));
  error_catcher(addEdge(graph, 2, 5, 2));
  error_catcher(addEdge(graph, 3, 1, 15));
  error_catcher(addEdge(graph, 3, 2, 11));
  error_catcher(addEdge(graph, 3, 4, 6));
  error_catcher(addEdge(graph, 4, 3, 6));
  error_catcher(addEdge(graph, 4, 5, 8));
  error_catcher(addEdge(graph, 5, 4, 8));
  error_catcher(addEdge(graph, 5, 2, 2));
  error_catcher(addEdge(graph, 5, 0, 14));
  // 1 до 2-й составляет 7, до 3-й — 9, до 4-й — 20, до 5-й — 20, до 6-й — 11.

  error_catcher(printGraph(graph));

  error_catcher(dijkstra(graph, 0));

  error_catcher(deleteGraph(graph));
}

void test_dataset(){
    int deg = 0;
    struct Graph *graph;
    error_catcher(createGraph(&graph, 2)); // тест на петлю

    error_catcher(addEdge(graph, 0, 1, 54));
    error_catcher(addEdge(graph, 0, 0, 1));
    error_catcher(deleteGraph(graph));

    error_catcher(createGraph(NULL, 5));

    error_catcher(createGraph(&graph, 2)); // тест на недопустимый номер вершины в функции addEdge

    error_catcher(addEdge(graph, 0, 1, 54));
    error_catcher(addEdge(graph, 0, 2, 54));
    error_catcher(deleteGraph(graph));

    error_catcher(createGraph(&graph, 2)); // тест на недопустимый номер вершины в функции degree

    error_catcher(addEdge(graph, 0, 1, 54));
    error_catcher(addEdge(graph, 1, 0, 54));
    error_catcher(degree(&deg, graph, 2));
    error_catcher(deleteGraph(graph));
}

int main() {

  dijkstra_test_dataset();
  test_dataset();
  
}
