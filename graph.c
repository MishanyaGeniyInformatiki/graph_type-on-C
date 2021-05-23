#include "graph.h"


int main() {

	dijkstra_test_dataset();

	return 0;
}


struct queue *queue_init(int num) {
	struct queue *q = (struct queue*)malloc(sizeof(struct queue));
	q->qu = (int*)malloc(num*sizeof(int));
  	q->frnt = 0;
  	q->rear = -1;
  	q->qmax = num;
  return q;
}

void queue_push(struct queue *q, int x) {

  if(q->rear < q->qmax - 1) {
  	q->rear++;
    q->qu[q->rear]=x;
  }
  else
    printf("Очередь полна!\n");
  return;
}

int queue_empty(struct queue *q) {

  	if(q->rear < q->frnt) 
  		return 1;
  	else  
  		return 0;
}

void queue_print(struct queue *q) {
	
 	if(queue_empty(q)==1) {
    	printf("Очередь пуста!\n");
    	return;
  	}

  	int h;
  	for(h = q->frnt; h<= q->rear; h++) {
    	printf("%d ",q->qu[h]);
  	}
	printf("\n");
  	return;
}

int queue_pop(struct queue *q) {

  if(queue_empty(q)==1) {
    printf("Очередь пуста!\n");
    return 0;
  }

  int x, h;
  x = q->qu[q->frnt];
  for(h = q->frnt; h < q->rear; h++) {
    q->qu[h] = q->qu[h+1];
  }
  q->rear--;
  return x;
}




struct Vertex* addVertex(struct Graph* graph, int val)
{
	struct Vertex* newVertex = (struct Vertex*)malloc(sizeof(struct Vertex));

	newVertex->num = val;
	newVertex->next = NULL;
	
	return newVertex;
}

struct Graph* createGraph(int numVertices)
{
	struct Graph* newGraph = (struct Graph*)malloc(sizeof(struct Graph));
	newGraph->numVertices = numVertices;

	newGraph->adjLists = (struct Vertex**)malloc(numVertices * sizeof(struct Vertex*));

	for (int i = 0; i < numVertices; i++)
		newGraph->adjLists[i] = addVertex(newGraph, i); // создаю столбец с вершинами: типо
	// 0 -> NULL
	// 1 -> NULL
	// 2 -> NULL
	// . -> NULL
	// . -> NULL
	// i -> NULL

	return newGraph;
}


void addEdge(struct Graph* graph, int start, int final, double weight)
{	
	/*
	struct Vertex* temp = graph->adjLists[start]->next; // указатель на ребенка start - вершины
	graph->adjLists[start]->next = addVertex(graph, final); // вставляю нужную
	// вершину после start (головной вершины)
	graph->adjLists[start]->next->next = temp; // организовываю связь между 
	// final и temp вершинами
	graph->adjLists[start]->next->weight = graph->adjLists[start]->weight;
	graph->adjLists[start]->weight = weight;
	*/

	struct Vertex* temp = graph->adjLists[start]->next;
	struct Vertex* vert = addVertex(graph, final);
	graph->adjLists[start]->next = vert; // вставляю нужную
	// вершину после start (головной вершины)
	vert->next = temp; // организовываю связь между final и temp
	vert->weight = weight; // вес ребра входящего из start вершины в final


	// заполнение за n^2
	/* 
	struct Vertex* temp = graph->adjLists[start];
	while(temp->next) // пока не NULL (пока не доберемся до конца списка данной вершины)
		temp = temp->next;
	
	temp->next = addVertex(graph, final); // вмечто NULL создаем указатель на необходимую вершину 
	temp->weight = weight;
	*/
	
}

int findWeightestEdge(struct Graph* graph)
{

	int weightestEdge = graph->adjLists[0]->weight;

	for (int i = 0; i < graph->numVertices; i++)
	{
		struct Vertex *temp = graph->adjLists[i];
		while(temp){
			
			if(temp->weight > weightestEdge)
				weightestEdge = temp->weight;
			
			temp = temp->next;
		}
	}
	return weightestEdge;
}


void printGraph(struct Graph* graph)
{

	for (int v = 0; v < graph->numVertices; v++)
    {
    	struct Vertex* temp = graph->adjLists[v]->next;
    	printf("\n Adjacency list of vertex %d\n ", v);

    	while(temp)
    	{	
    		printf("  %d    ",temp->weight);
    		temp = temp->next;
    	}
    	printf("\n");

    	temp = graph->adjLists[v];
        while(temp)
        {	
            printf("%d ---> ", temp->num);
            temp = temp->next;
        }
        printf("\n");
    }

	/*
    for (int v = 0; v < graph->numVertices; v++)
    {
        struct Vertex* temp = graph->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v);

        
        // печать весов ребер
        struct Vertex* temp2 = temp;
        struct Vertex* temp3 = temp->next;
        while(temp3)
        {
        	printf("  %d    ",temp2->weight);
        	temp2 = temp2->next;
        	temp3 = temp3->next;
        }
        printf("\n");
        

        while(temp)
        {	
            printf("%d ---> ", temp->num);
            temp = temp->next;
        }
        printf("\n");
    }
    */
}

int degree(struct Graph* graph, int num)
{
	int count = 0;
	struct Vertex *temp = graph->adjLists[num]->next;
	while(temp){
		temp = temp->next;
		count++;
	}
	return count;
}


void dijkstra(struct Graph* graph, int start)
{	

	struct queue *q = queue_init(graph->numVertices); // создаю очередь

	bool visited[graph->numVertices];
	double dist[graph->numVertices];

	long int INF = pow(2, (sizeof(long int)*4 - 1)) - 1; // 2 147 483 647

	for (int i = 0; i < graph->numVertices; i++){
		visited[i] = false;
		dist[i] = INF;
	}

	dist[0] = 0;
	queue_push(q, 0);

	while (!queue_empty(q)){


		int vert = queue_pop(q); // достаю из очереди вершину
		visited[vert] = true; // помечаю ее как посещенную

		struct Vertex *currentVert = graph->adjLists[vert]; // текущая вершина 
				// (при i = 0 первая после head-вершины)


		for (int i = 0; i < degree(graph, vert); i++){ // рассматриваю все вершины смежные с vert
	
			currentVert = currentVert->next;
			int weight = currentVert->weight; 
			int num = currentVert->num;

			if (!visited[num] && dist[vert] + weight < dist[num]){ // этап релаксации

				dist[num] = dist[vert] + weight;
			}
		}

		int min_dist = INF;
		for (int i = 0; i < graph->numVertices; i++){ // выбираю на роль следующей вершины вершину с минимальным dist 

			if (!visited[i] && dist[i] < min_dist){
				min_dist = dist[i];
				vert = i;
			}
		}

		if (!visited[vert]){ // проверяю, что эта вершина еще не посещена
			queue_push(q, vert);
		}
		
	}

	for (int i = 0; i < graph->numVertices; i++) { // печатаю расстояния
		printf("Distance from %d vertex to %d vertex = %d\n", start, i, dist[i]);
	}



	/*
	int i;
	struct Vertex* p;
	bool intree[100];
	int distance[100];
	int parent[100];
	int v;
	int w;
	int weight;
	int dist;
	for (i = 0; i < graph->numVertices; i++){
		intree[i] = false;
		distance[i] = 666;
		//parent[i] = -1;
	}

	distance[start] = 0;
	v = start;

	
	while (intree[v] == false){
		intree[v] == true;
		p = graph->adjLists[v];
		
		while (p != NULL){
			w = p->num;

			weight = p->weight;
			if (distance[w] > (distance[v] + weight)){
				distance[w] = distance[v] + weight;
				parent[w] = v;
			}
			p = p->next;

		}
		
		//v = 1;
		dist = 666;
		for (i = 0; i < graph->numVertices; i++){
			if ((intree[i] == false) && (dist > distance[i])){
				dist = distance[i];
				v = i;
			}
		}
	}
	
	
	printf("dfdf");

	for (i=0;i<graph->numVertices;i++){
		printf("%d\n ", distance[i]);
	}*/
		
}

void dijkstra_test_dataset(){

	struct Graph* graph = createGraph(6);

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

#include "graph.h"

int main() {

  dijkstra_test_dataset();

  return 0;
}

struct queue *queue_init(int num) {
  struct queue *q = (struct queue *)malloc(sizeof(struct queue));
  q->qu = (int *)malloc(num * sizeof(int));
  q->frnt = 0;
  q->rear = -1;
  q->qmax = num;
  return q;
}

void queue_push(struct queue *q, int x) {

  if (q->rear < q->qmax - 1) {
    q->rear++;
    q->qu[q->rear] = x;
  } else
    printf("Очередь полна!\n");
  return;
}

int queue_empty(struct queue *q) {

  if (q->rear < q->frnt)
    return 1;
  else
    return 0;
}

void queue_print(struct queue *q) {

  if (queue_empty(q) == 1) {
    printf("Очередь пуста!\n");
    return;
  }

  int h;
  for (h = q->frnt; h <= q->rear; h++) {
    printf("%d ", q->qu[h]);
  }
  printf("\n");
  return;
}

int queue_pop(struct queue *q) {

  if (queue_empty(q) == 1) {
    printf("Очередь пуста!\n");
    return 0;
  }

  int x, h;
  x = q->qu[q->frnt];
  for (h = q->frnt; h < q->rear; h++) {
    q->qu[h] = q->qu[h + 1];
  }
  q->rear--;
  return x;
}

struct Vertex *addVertex(struct Graph *graph, int val) {
  struct Vertex *newVertex = (struct Vertex *)malloc(sizeof(struct Vertex));

  newVertex->num = val;
  newVertex->next = NULL;

  return newVertex;
}

struct Graph *createGraph(int numVertices) {
  struct Graph *newGraph = (struct Graph *)malloc(sizeof(struct Graph));
  newGraph->numVertices = numVertices;

  newGraph->adjLists =
      (struct Vertex **)malloc(numVertices * sizeof(struct Vertex *));

  for (int i = 0; i < numVertices; i++)
    newGraph->adjLists[i] =
        addVertex(newGraph, i); // создаю столбец с вершинами: типо
  // 0 -> NULL
  // 1 -> NULL
  // 2 -> NULL
  // . -> NULL
  // . -> NULL
  // i -> NULL

  return newGraph;
}

void addEdge(struct Graph *graph, int start, int final, double weight) {
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

  struct Vertex *temp = graph->adjLists[start]->next;
  struct Vertex *vert = addVertex(graph, final);
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
}

int findWeightestEdge(struct Graph *graph) {

  int weightestEdge = graph->adjLists[0]->weight;

  for (int i = 0; i < graph->numVertices; i++) {
    struct Vertex *temp = graph->adjLists[i];
    while (temp) {

      if (temp->weight > weightestEdge)
        weightestEdge = temp->weight;

      temp = temp->next;
    }
  }
  return weightestEdge;
}

void printGraph(struct Graph *graph) {

  for (int v = 0; v < graph->numVertices; v++) {
    struct Vertex *temp = graph->adjLists[v]->next;
    printf("\n Adjacency list of vertex %d\n ", v);

    while (temp) {
      printf("  %d    ", temp->weight);
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

  /*
for (int v = 0; v < graph->numVertices; v++)
{
  struct Vertex* temp = graph->adjLists[v];
  printf("\n Adjacency list of vertex %d\n ", v);


  // печать весов ребер
  struct Vertex* temp2 = temp;
  struct Vertex* temp3 = temp->next;
  while(temp3)
  {
          printf("  %d    ",temp2->weight);
          temp2 = temp2->next;
          temp3 = temp3->next;
  }
  printf("\n");


  while(temp)
  {
      printf("%d ---> ", temp->num);
      temp = temp->next;
  }
  printf("\n");
}
*/
}

int degree(struct Graph *graph, int num) {
  int count = 0;
  struct Vertex *temp = graph->adjLists[num]->next;
  while (temp) {
    temp = temp->next;
    count++;
  }
  return count;
}

void dijkstra(struct Graph *graph, int start) {

  struct queue *q = queue_init(graph->numVertices); // создаю очередь

  bool visited[graph->numVertices];
  double dist[graph->numVertices];

  long int INF = pow(2, (sizeof(long int) * 4 - 1)) - 1; // 2 147 483 647

  for (int i = 0; i < graph->numVertices; i++) {
    visited[i] = false;
    dist[i] = INF;
  }

  dist[0] = 0;
  queue_push(q, 0);

  while (!queue_empty(q)) {

    int vert = queue_pop(q); // достаю из очереди вершину
    visited[vert] = true;    // помечаю ее как посещенную

    struct Vertex *currentVert =
        graph->adjLists[vert]; // текущая вершина
                               // (при i = 0 первая после head-вершины)

    for (int i = 0; i < degree(graph, vert);
         i++) { // рассматриваю все вершины смежные с vert

      currentVert = currentVert->next;
      int weight = currentVert->weight;
      int num = currentVert->num;

      if (!visited[num] && dist[vert] + weight < dist[num]) { // этап релаксации

        dist[num] = dist[vert] + weight;
      }
    }

    int min_dist = INF;
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

  for (int i = 0; i < graph->numVertices; i++) { // печатаю расстояния
    printf("Distance from %d vertex to %d vertex = %d\n", start, i, dist[i]);
  }

  /*
  int i;
  struct Vertex* p;
  bool intree[100];
  int distance[100];
  int parent[100];
  int v;
  int w;
  int weight;
  int dist;
  for (i = 0; i < graph->numVertices; i++){
          intree[i] = false;
          distance[i] = 666;
          //parent[i] = -1;
  }

  distance[start] = 0;
  v = start;


  while (intree[v] == false){
          intree[v] == true;
          p = graph->adjLists[v];

          while (p != NULL){
                  w = p->num;

                  weight = p->weight;
                  if (distance[w] > (distance[v] + weight)){
                          distance[w] = distance[v] + weight;
                          parent[w] = v;
                  }
                  p = p->next;

          }

          //v = 1;
          dist = 666;
          for (i = 0; i < graph->numVertices; i++){
                  if ((intree[i] == false) && (dist > distance[i])){
                          dist = distance[i];
                          v = i;
                  }
          }
  }


  printf("dfdf");

  for (i=0;i<graph->numVertices;i++){
          printf("%d\n ", distance[i]);
  }*/
}

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
