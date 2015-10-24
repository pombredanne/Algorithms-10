#define WHITE 0
#define GRAY 1
#define BLACK -1

#define NIL 0
#define INF -1

#include<stdio.h>
#include<stdlib.h>

typedef struct vertex{
	int key;
	struct vertex *next;
}vertex;

typedef struct AdjList{
	vertex *head;
	int color;
	int d;
	int p;
}AdjList;

typedef struct Graph{
	int v;
	struct AdjList* arr;
}Graph;

struct vertex* newvertex(int val){
	vertex *temp;
	temp = (vertex *)malloc(sizeof(vertex));
	temp->key = val;
	temp->next = NULL;
	return temp;
}

struct Graph* addEdge(Graph* G, int s, int d){
	vertex* temp = newvertex(d);
	temp->next = (G->arr[s]).head;
	(G->arr[s]).head = temp;

	temp = newvertex(s);
	temp->next = G->arr[d].head;
	(G->arr[d]).head = temp;

	return G;
}

typedef struct Queue{
	int elements[100];
	int start;
	int end;
}Queue;

void Enqueue(Queue* Q, int v){
	Q->elements[(Q->end) % 100]= v;
	Q->end += 1;
}

int Dequeue(Queue* Q){
	if((Q->start) < (Q->end))
	{	int ret = Q->elements[(Q->start) % 100];
		Q->start += 1;
		return ret;	}
	else
		return -1;
}

Queue* init_Queue(Queue* Q){
	Q = (Queue *)malloc(sizeof(Queue)); 
	Q->start = Q->end = 0;
	return Q;
}

void print_queue(Queue *Q){
	int i = Q->start;
	printf("Printing Queue:");
	for (i ; i < Q->end; i++)
		printf(" %d -", Q->elements[i]);
	printf("End\n");
}

void bfs_check(Graph *G, int s){
		int i;
		for(i = 1; i<=G->v; i++)
		{
			printf("Distance of %d from %d : %d \n", i, s, (G->arr[i]).d);
		}
}

void BFS(Graph* G, int s)
{	
	printf("Breadth First Implementation Begins.\n");
	int i;
	for(i = 1; i <= (G->v); i++)
	{
		(G->arr[i]).color = WHITE;
		(G->arr[i]).d = INF;
		(G->arr[i]).p = NIL;
	}
	(G->arr[s]).color = GRAY;
	(G->arr[s]).d = 0;
	Queue* Q = init_Queue(Q);
	Enqueue(Q, s);
	while (Q->start < Q->end)
	{	
		int u = Dequeue(Q);
		vertex *temp =( G->arr[u]).head;
		while( temp != NULL)
		{	
			if(G->arr[temp->key].color == WHITE)
			{
				(G->arr[temp->key]).color = GRAY;
				(G->arr[temp->key]).d = (G->arr[u]).d + 1;
				(G->arr[temp->key]).p = u;
				Enqueue(Q, temp->key);
			}
			temp = temp->next;
		}
		G->arr[u].color = BLACK;  	
	}
	bfs_check(G, s);
	printf("Breadth First Implementation Complete.\n");
}

void print_graph(Graph *G){
	int i;
	printf("The Adjacency List implementation of the input Graph:\n");
	for (i = 1; i <= G->v; i++)
	{	
		printf("Adjacency List of %d : ", i);
		vertex *t =(G->arr[i]).head;
		while(t != NULL)
		{	
			printf("%d -> ",( t->key));
			t = t->next;
		}
		printf("NULL");
		printf("\n");
	}
}

int is_connected(Graph *G){
	int i;
	int count=0;
	for(i = 1; i <= G->v; i++)
	{
		if(G->arr[i].d <= 0)
			count++;
	}
	if (count > 1)
	{	
		printf("\nThe graph is NOT connected\n");	
		return 0;
	}
	else
	{
		printf("\nThe graph is connected.\n");	
		return 1;
	}
}

void main(){
	Graph *G;
	G = (Graph *)malloc(sizeof(Graph));
	printf("Enter the number of nodes :");
	scanf("%d", &(G->v));
	G->arr = (AdjList *)malloc(((G->v) + 1)*sizeof(AdjList));
	int i;
	for(i = 1; i <= (G->v); i++)
		(G->arr[i]).head = NULL;
	printf("Enter '1 2' for an edge between nodes 1 and 2\n");
	printf("Enter '0 0' to exit\n");
	for(;;)
	{
		printf("Enter the edges\n");
		int n1, n2;
		scanf ("%d %d", &n1, &n2);
		if((n1 <= (G->v) && n1 > 0) && (n2 <= (G->v) && n2 > 0))
			G = addEdge(G, n1, n2);
		else
		{	printf("Input Stop\n");
			break;
		}
	}
	int n;
	printf("Enter the node for BFS:");
	scanf("%d", &n);
	print_graph(G);
	BFS(G,n);
	is_connected(G);
}
