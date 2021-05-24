#include "queue.h"
#include "graph.h"
#include "errors.h"


error_t addVertex(struct Vertex ** out, int val) {
  error_t err = NoErrors;
  struct Vertex *newVertex = (struct Vertex *)malloc(sizeof(struct Vertex));

  if (NULL == newVertex) {
	   err = MemoryError;
     return err;
  }

  newVertex->num = val;
  newVertex->next = NULL;

  *out = newVertex;

  return err;
}

error_t createGraph(  struct Graph ** out, int numVertices) {
  error_t err = NoErrors;

  if (out == NULL) {
    return MemoryError;
  }

  struct Graph *newGraph = (struct Graph *)malloc(sizeof(struct Graph));

  if (NULL == newGraph) {
	  err = MemoryError;
    return err;
  }

  newGraph->numVertices = numVertices;

  newGraph->adjLists =
      (struct Vertex **)malloc(numVertices * sizeof(struct Vertex *));
  
  if (NULL == newGraph->adjLists) {
	  err = MemoryError;
    return err;
  }

  for (int i = 0; i < numVertices; i++)
    addVertex(&(newGraph->adjLists[i]), i); // создаю столбец с вершинами: типа
  // 0 -> NULL
  // 1 -> NULL
  // 2 -> NULL
  // . -> NULL
  // . -> NULL
  // i -> NULL

  *out = newGraph;

  return err;
}

error_t addEdge(struct Graph *graph, int start, int final, double weight) {
  /*
  struct Vertex* temp = graph->adjLists[start]->next; // указатель на ребенка
  start - вершины graph->adjLists[start]->next = addVertex(graph, final); //
  вставляю нужную
  // вершину после start (головной вершины)
  graph->adjLists[start]->next->next = temp; // организовываю связь между
  // final и temp вершинами
  graph->adjLists[start]->next->weight = graph->adjLists[start]->weight;
  graph->adjLists[start]->weight = weight;
  */
  error_t err = NoErrors;
  
  if (final == start) {
	  err = LoopError;
    return err;
  }

  if ((final >= graph->numVertices) || (start >= graph->numVertices)) {
	  err = VertexNotExistsError;
    return err;
  }

  struct Vertex *temp = graph->adjLists[start]->next;
  struct Vertex *vert;
  addVertex(&vert, final);
  graph->adjLists[start]->next = vert; // вставляю нужную
  // вершину после start (головной вершины)
  vert->next = temp; // организовываю связь между final и temp
  vert->weight = weight; // вес ребра входящего из start вершины в final

  // заполнение за n^2
  /*
  struct Vertex* temp = graph->adjLists[start];
  while(temp->next) // пока не NULL (пока не доберемся до конца списка данной
  вершины) temp = temp->next;

  temp->next = addVertex(graph, final); // вмечто NULL создаем указатель на
  необходимую вершину temp->weight = weight;
  */

  return err;
}

error_t findWeightestEdge(double* out, struct Graph *graph) {
  error_t err = NoErrors;
  double weightestEdge = graph->adjLists[0]->weight;

  for (int i = 0; i < graph->numVertices; i++) {
    struct Vertex *temp = graph->adjLists[i];
    while (temp) {

      if (temp->weight > weightestEdge)
        weightestEdge = temp->weight;

      temp = temp->next;
    }
  }
  *out = weightestEdge; 
  return err;
}

error_t printGraph(struct Graph *graph) {
  error_t err = NoErrors;

  if (NULL == graph) {
    err = InvalidArg;
    return err;
  }

  for (int v = 0; v < graph->numVertices; v++) {
    struct Vertex *temp = graph->adjLists[v]->next;
    printf("\n Adjacency list of vertex %d\n ", v);

    while (temp) {
      printf("  %.0f    ", temp->weight);
      temp = temp->next;
    }
    printf("\n");

    temp = graph->adjLists[v];
    while (temp) {
      printf("%d ---> ", temp->num);
      temp = temp->next;
    }
    printf("\n");

  }
  return err;
}

error_t degree(int* out, struct Graph *graph, int num) {
  error_t err = NoErrors;

  if (num >= graph->numVertices) {
	  err = VertexNotExistsError;
    return err;
  }

  int count = 0;
  struct Vertex *temp = graph->adjLists[num]->next;
  while (temp) {
    temp = temp->next;
    count++;
  }
  *out = count;
  return err;
}

error_t deleteGraph(struct Graph *graph){

  error_t err = NoErrors;

  if (NULL == graph) {
    err = InvalidArg;
    return err;
  }

  for(int i = 0; i < graph->numVertices; i++){

    struct Vertex *temp = graph->adjLists[i];
    struct Vertex *pred = temp;

    while(temp){

      pred = temp;
      temp = pred->next;
      free(pred);
      //printf("free is success\n");
    }
  }
  free(graph->adjLists);
  free(graph);

  return err;
  //printf("free graph is success\n");
}

error_t dijkstra(struct Graph *graph, int start) {
  error_t err = NoErrors;

  struct queue *q;
  queue_init(&q, graph->numVertices); // создаю очередь

  bool visited[graph->numVertices];
  double dist[graph->numVertices];

  long INF = LONG_MAX; // LONG_MAX
  
  double weightest = INF;
  findWeightestEdge(&weightest, graph);
  
  if ((graph->numVertices)*weightest >= INF){
    err = WeightOutOfRangeError;
    queue_delete(q);
    return err;
  }

  for (int i = 0; i < graph->numVertices; i++) {
    visited[i] = false;
    dist[i] = INF;
  }

  dist[0] = 0;
  queue_push(q, 0);

  while (!queue_empty(q)) {

    int vert;
    queue_pop(&vert, q); // достаю из очереди вершину
    visited[vert] = true;    // помечаю ее как посещенную

    struct Vertex *currentVert =
        graph->adjLists[vert]; // текущая вершина
                               // (при i = 0 первая после head-вершины)
    int deg = 0;
    degree(&deg, graph, vert);
    for (int i = 0; i < deg;
         i++) { // рассматриваю все вершины смежные с vert

      currentVert = currentVert->next;
      double weight = currentVert->weight;
      int num = currentVert->num;

      if (!visited[num] && dist[vert] + weight < dist[num]) { // этап релаксации
        dist[num] = dist[vert] + weight;

      }
    }

    long min_dist = INF;
    for (int i = 0; i < graph->numVertices;
         i++) { // выбираю на роль следующей вершины вершину с минимальным dist

      if (!visited[i] && dist[i] < min_dist) {
        min_dist = dist[i];
        vert = i;
      }
    }

    if (!visited[vert]) { // проверяю, что эта вершина еще не посещена
      queue_push(q, vert);
    }
  }

  queue_delete(q);

  for (int i = 0; i < graph->numVertices; i++) { // печатаю расстояния
    printf("Distance from %d vertex to %d vertex = %.0f\n", start, i, dist[i]);
  }

  return err;
}