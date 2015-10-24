#define NIL 0
#define MAX_SIZE 100
#include <stdio.h>
#include <stdlib.h>

// Implementation of Stack ADT
typedef struct Stack {
	int arr[MAX_SIZE];
	int top;
}Stack;

// Stack operations
Stack *init_Stack(){
	Stack* S;
	S = (Stack *)malloc(sizeof(Stack));
	S->top = -1;
}

void push(Stack* S, int data) {
	S->top = S->top + 1;
	S->arr[S->top] = data;
}

int pop(Stack* S) {
	S->top = S->top - 1;
	return S->arr[S->top + 1];
}

int top(Stack* S) {
	return S->arr[S->top];
}

int is_empty(Stack* S) {
	if (S->top < 0) 	
		return 1;
	else 
		return 0;
}

typedef struct vertex{
	int key;
	struct vertex *next;
}vertex;

typedef struct AdjList{
	vertex *head;
	int color;
	int DFN;
	int p;
	int visited;
}AdjList;

typedef struct Graph{
	int V;
	struct AdjList* arr;
}Graph;

vertex* newvertex(int val){
	vertex *temp;
	temp = (vertex *)malloc(sizeof(vertex));
	temp->key = val;
	temp->next = NULL;
	return temp;
}

Graph* addEdge(Graph* G, int s, int d){
	vertex* temp = newvertex(d);
	temp->next = (G->arr[s]).head;
	(G->arr[s]).head = temp;

	temp = newvertex(s);
	temp->next = G->arr[d].head;
	(G->arr[d]).head = temp;

	return G;
}

Graph* init_Graph(Graph *G, int nodes){
	int i;
	G = (Graph*)malloc(sizeof(Graph));
	G->V = nodes;
	G->arr = (AdjList *)malloc((nodes+1)*sizeof(AdjList));
	for (i=1; i<=nodes; i++) {
		G->arr[i].head = NULL;
	}
	return G;
}

void print_graph(Graph *G){
	int i;
	printf("The Adjacency List implementation of the input Graph:\n");
	for (i = 1; i <= G->V; i++)
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

/*
void dfs_check(Graph *G){
	int i;
	for(i = 1; i <= G->V; i++)
	{
		printf("\n For %d :\tDFN:%d\tParent:%d\tVisited:%d", i, G->arr[i].DFN,
			   G->arr[i].p, G->arr[i].visited);
	}
}
*/

void DFS( Graph *G, int n){
	int i;
	Stack* S = init_Stack();

	int count;
	for ( i = 1; i <= G->V; i++) {
		G->arr[i].DFN = 0;
		G->arr[i].visited = 0;
		G->arr[i].p = NIL;
	}

	count = 1;
	push(S, n);
	G->arr[n].visited = 1;
	G->arr[n].DFN = count++;
	G->arr[n].p = NIL;
	int x, y;
	vertex *temp;
	while(!is_empty(S)) {
		x = pop(S);
		temp = G->arr[x].head;
		while(temp!=NULL) {
			if (G->arr[temp->key].visited==0) {
				G->arr[temp->key].DFN = count++;
				G->arr[temp->key].visited = 1;
				G->arr[temp->key].p = x;
				push(S, temp->key);
			}
			temp = temp->next;
		}
	}
	print_graph(G);
}

int is_connected(Graph *G, int n){
	int i;
	DFS(G, n);
	for(i=1; i<=G->V; i++)
	{
		if(G->arr[i].visited == 0)
		{
			printf("The graph is NOT connected\n");
			return 0;
		}
	}
	printf("The graph is connected\n");
	return 1;
}
int main () {
	
	int nodes,i; 
	printf("Enter the number of nodes : \n");
	scanf("%d", &nodes);
	
	struct Graph* G;
	G = init_Graph(G, nodes);
	
	printf("Enter '1 2' for an edge between nodes 1 and 2\n");
	printf("Enter '0 0' to exit\n");
	for(;;)
	{
		printf("Enter the edges\n");
		int n1, n2;
		scanf ("%d %d", &n1, &n2);
		if((n1 <= (G->V) && n1 > 0) && (n2 <= (G->V) && n2 > 0))
			G = addEdge(G, n1, n2);
		else
		{	printf("Input Stop\n");
			break;
		}
	}
	print_graph(G);
	int n;
	printf("Enter node:");
	scanf("%d", &n);
	is_connected(G, n);
	return 0;
}