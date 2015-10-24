#define WHITE 0
#define GRAY 1
#define BLACK -1

#define NIL 0
#define INF -1

#include<stdio.h>
#include<stdlib.h>

int time;

typedef struct vertex{
	int key;
	struct vertex *next;
}vertex;

typedef struct AdjList{
	vertex *head;
	int color;
	int d;
	int f;
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

void DFS_Visit(Graph *G, int index){
	AdjList vert = G->arr[index];
	vert.color = GRAY;
	time += 1;
	vert.d = time;
	vertex *temp = vert.head;
	while(temp != NULL)
	{	
		int vert_index = temp->key;  
		
		if ((G->arr[vert_index]).color == WHITE)
		{
			G->arr[vert_index].p = index;
			DFS_Visit(G, temp->key);
		}
		temp = temp -> next;
	}
	vert.color = BLACK;
	time += 1;
	vert.f = time;
}

void DFS(Graph *G){
	int i;
	for(i=1; i<= G->v; i++)
	{
		(G->arr[i])->color = WHITE;
		(G->arr[i])->p = NIL;
	}
	time = 0;
	for(i=1; i<=G->v; i++)
	{
		printf("\nDFS for %d :", i);
		if((G->arr[i])->color == WHITE)
			DFS_Visit(G, i);
	}
}

void dfs_check(Graph *G){
	int i;
	printf("\nDFS Checking Init\n");
	for(i = 1; i<=G->v; i++)
	{
		printf("For %d:\t Parent: %d \t d: %d \t f: %d\n ",i, G->arr[i].p,
				G->arr[i].d, G->arr[i].f);
	}
	printf("\nDFS Checking End\n");
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
	print_graph(G);
	DFS(G);
	dfs_check(G);
}	
