#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct s_node {
	int number;
	int index; // index of maximum following node
	int *weight;
	struct s_node **next;
} Node;

typedef struct s_graph {
	Node **nodes;
	int size;
} t_graph;

void init_map(t_graph *graph, int size);
Node *newTreeHouse(int number, int weight[], int w_size);
void addPath(Node *node, Node *next);
void printMap(t_graph *graph);
void solve_puzzle(t_graph *graph, int start, int end);

int main(){
	t_graph graph;

	init_map(&graph, 7);

	printMap(&graph);
	solve_puzzle(&graph, 0, 5);
}

void solve_puzzle(t_graph *graph, int start, int end){
	Node *current = graph->nodes[start];
	int health = 100;

	printf("A path from Tree House %d to Tree House %d is\n", start+1, end+1);
	printf("Path: %d ", current->number);

	srand(time(NULL));
	while(current->number != graph->nodes[end]->number){
		int next = rand() % current->index;
		health -= current->weight[next];
		current = current->next[next];
		printf("--> %d ", current->number);
	}
	printf("\nHealth: %d\n", health);
}

void printMap(t_graph *graph){
	printf("<--- Printing Forest Map --->\n");
	for(int i = 0; i < graph->size; i++){
		printf("TreeHouse %d", graph->nodes[i]->number);
		printf("\nhead");
		for(int j = 0; j < graph->nodes[i]->index; j++){
			printf(" -> %d(%d)", graph->nodes[i]->next[j]->number, graph->nodes[i]->weight[j]);
		}
		printf("\n");
	}
}


Node *newTreeHouse(int number, int *weight, int w_size){
	Node *node = (Node *)malloc(sizeof(Node));
	node->number = number;
	node->weight = (int *)malloc(sizeof(int) * w_size);
	node->next = (Node **)malloc(sizeof(Node *) * w_size);
	node->index = 0;
	for(int i = 0; i < w_size; i++){
		node->weight[i] = weight[i];
		node->next[i] = NULL;
	}
	return node;
}

void addPath(Node *node, Node *next){
	node->next[node->index] = next;
	node->index++;
}

void init_map(t_graph *graph, int size){
	graph->size = size;
	graph->nodes = (Node **)malloc(sizeof(Node *) * size);
	graph->nodes[0] = newTreeHouse(1, (int[]){20,30}, 2);
	graph->nodes[1] = newTreeHouse(2, (int[]){30,50}, 2);
	graph->nodes[2] = newTreeHouse(3, (int[]){5,30}, 2);
	graph->nodes[3] = newTreeHouse(4, (int[]){10}, 1);
	graph->nodes[4] = newTreeHouse(5, (int[]){5,10}, 2);
	graph->nodes[5] = newTreeHouse(6, (int[]){}, 0);
	graph->nodes[6] = newTreeHouse(7, (int[]){10,5}, 2);

	addPath(graph->nodes[0], graph->nodes[1]);
	addPath(graph->nodes[0], graph->nodes[2]);
	addPath(graph->nodes[1], graph->nodes[3]);
	addPath(graph->nodes[1], graph->nodes[4]);
	addPath(graph->nodes[2], graph->nodes[4]);
	addPath(graph->nodes[2], graph->nodes[6]);
	addPath(graph->nodes[3], graph->nodes[5]);
	addPath(graph->nodes[4], graph->nodes[5]);
	addPath(graph->nodes[4], graph->nodes[3]);
	addPath(graph->nodes[6], graph->nodes[5]);
	addPath(graph->nodes[6], graph->nodes[4]);
}
