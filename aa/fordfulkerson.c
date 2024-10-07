#include <stdio.h>
#include <stdlib.h>
typedef struct graph{
    int n;
    int flows[10][10];
    int residual[10][10];
    int reverse[10][10];
    graph* next;
}graph;

typedef struct path{
    int len;
    int order[10];
    int min_value;

}path;

typedef struct iteration{
    graph* g;
    path* p;
}it;

graph* initialize(){
    graph* new = (graph*)malloc(sizeof(graph));
    printf("How many vertices?");
    int n, c;
    scanf("%d", &n);
    new -> n = n;
    
    printf("Vertex 0 is s, vertex %d is t", n-1);
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (j == i){
                new -> residual[i][j] = 0;
            new -> flows[i][j] = 0;
            new -> reverse[i][j] = 0;
            }
            printf("What is the capacity from vertex %d and %d?", i, j);
            scanf("%d", &c);
            new -> residual[i][j] = c;
            new -> flows[i][j] = 0;
            new -> reverse[i][j] = 0;
        }
    }
    new -> next = NULL;
    return new;
}

it* augmented_path(graph* curr_g){
    int n = curr_g->n;
    int visited[n];
    int parent[n];
    int queue[n];
    int front = 0;
    int rear = 0;
    int flag;
    queue[0] = 0;
    visited[0] = 0;
    parent[0] = 0;
    while (visited[n-1] == 0){
        flag = 0;
        for (int i=0; i< n; i++){
            if (visited[i] == 0){
                if (curr_g -> residual[queue[front]][i] > 0){
                    flag = 1;
                    parent[i] = queue[front];
                    queue[++rear] = i;
                    visited[i] = 1;
                }
                elif (curr_g -> reverse[queue[front]][i] > 0){
                    parent[i] = queue[front];
                    queue[++rear] = i;
                    visited[i] = 1;
                    flag = 1;
                }
            }
        }
        front++;
        if (flag == 0){
            return NULL;
        }

    }
    int path[10];
    it* new = (it*)malloc(sizeof(it));
    path[0] = n-1;
    int i = 0;
    while (path[i] != 0){
        
    }



}