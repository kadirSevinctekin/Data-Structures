#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 80

typedef struct node{
	int vertex;
	struct node* next;
}NODE;

typedef struct graph{
	int numOfVertices;
	NODE* list[MAX];
}GRAPH;

int** createAdjMatrix(int *N){
	int i, j, n, prereq, temp;
	printf("Enter the number of Courses: "); scanf("%d", N); n=*N;
	int **adjacencyMatrix = (int**)malloc(n*sizeof(int*));
	if(adjacencyMatrix==NULL) printf("not allocated\n");
	for(i=0;i<n;i++){
		adjacencyMatrix[i]=(int*)malloc(n*sizeof(int));
		if(adjacencyMatrix[i]==NULL) printf("not allocated\n");
	}
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			adjacencyMatrix[i][j]=0;
	for(i=0;i<n;i++){
		printf("Enter the number of prerequisites of %d. course: ", i+1);
		scanf("%d", &prereq);
		if(prereq>0){
			for(j=0;j<prereq;j++){
				printf("Enter the %d. prerequisite course of the %d. course: ", j+1, i+1);
				scanf("%d", &temp);
				adjacencyMatrix[temp-1][i]=1;
			}
		}
	}
	printf("\n\n");
	printf("Adjacency Matrix: ");
	printf("\n\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			printf("%d   ", adjacencyMatrix[i][j]);
		printf("\n");
	}
	return adjacencyMatrix;
}

NODE* createNode(int key){
	NODE* newNode=(NODE*)malloc(sizeof(NODE));
	newNode->vertex=key;
	newNode->next=NULL;
	return newNode;
}

GRAPH* constructGraph(int N){
	int i;
	GRAPH* graph=(GRAPH*)malloc(sizeof(GRAPH));
	graph->numOfVertices=N;
	for(i=0;i<N;i++)
		graph->list[i]=NULL;
	return graph;
}

void connect(GRAPH* graph, int** adjMatrix, int N){
	int i, j;
	NODE* temp;
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			if(adjMatrix[i][j]==1){
				NODE* node=createNode(i+1);
				if(graph->list[j]==NULL)
					graph->list[j]=node;
				else{
					temp=graph->list[j];
					while(temp->next!=NULL)
						temp=temp->next;
					temp->next=node;
				}
			}
}

void calculatePrerequisites(GRAPH* graph){
	int i, j, count;
	NODE* t;
	printf("\nThe number of prerequisites for each lesson for this graph is: \n");
	for(i=0;i<graph->numOfVertices;i++){
		count=0;
		t=graph->list[i];
		while(t){
			count++;
			t=t->next;
		}
		printf("Course-%d: %d    ", i+1, count);
	}
	printf("\n\n");	
}

void printGraph(GRAPH* graph){
    int i;
    for(i=0;i<graph->numOfVertices;i++){
        NODE* t=graph->list[i];
        printf("\n Prerequisite courses of the %d. course: \n", i+1);
        while(t){
            printf("Course-%d  ", t->vertex);
            t=t->next;
        }
        printf("\n");
    }
    printf("\n------------------------------------------\n");
}

int control(int i, int* blackList, int blCount){
	if(blCount==0)
		return 1;
	else{
		int j;
		for(j=0;j<blCount;j++)
			if(i==blackList[j])
				return 0;
		return 1;
	}
}

GRAPH* deleteNode(GRAPH* graph, int *array, int arrCount){
	int i, j;
	NODE* temp, *cur;
	for(i=0;i<arrCount;i++){
		for(j=0;j<graph->numOfVertices;j++){
			temp=graph->list[j];
			if(temp!=NULL){
				if(graph->list[j]->vertex==array[i]+1){
					graph->list[j]=graph->list[j]->next;
					free(temp);
				}
				else{
					while(temp->next!=NULL && temp->next->vertex!=array[i]+1)
						temp=temp->next;
					if(temp->next!=NULL){
						cur=temp->next;
						temp->next=temp->next->next;
						free(cur);
					}	
				}
			}
		}
	}
	return graph;
}

void output(GRAPH* graph){
	int i, j, count=1, blackList[MAX], blCount=0, array[MAX], arrCount;
	printf("Courses taken by the student each term:\n\n");
	while(blCount<graph->numOfVertices){
		printf("Term-%d: ", count);
		arrCount=0;
		for(i=0;i<graph->numOfVertices;i++){
			if(graph->list[i]==NULL && control(i, blackList, blCount)){
				printf("Course-%d ", i+1);
				blackList[blCount]=i;
				blCount++;
				array[arrCount]=i;
				arrCount++;
			}
		}
		graph=deleteNode(graph, array, arrCount);
		count++;
		printf("\n");
	}
	printf("\nAccordingly, student completes the department in %d terms.", count-1);
}

int main(){
	int i, j, N;
	int** adjMatrix=createAdjMatrix(&N);
	GRAPH *graph=constructGraph(N); 
	connect(graph, adjMatrix, N);
	calculatePrerequisites(graph);
	printGraph(graph);
	output(graph);
	free(graph);
	return 0;
}
