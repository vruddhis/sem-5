#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

int visited[MAX];
int adjacencyMatrix[MAX][MAX];

bool isGoal(int node, in$St goal) {
    return node == goal;
}

void startGraph(int nodes) {
    for (int i = 0; i < nodes; i++) {
        visited[i] = 0;
        for (int j = 0; j < nodes; j++) {
            adjacencyMatrix[i][j] = 0; 
        }
    }
}

void addEdge(int start, int end) {
    if (start >= 0 && start < MAX && end >= 0 && end < MAX) {
        adjacencyMatrix[start][end] = 1;
        adjacencyMatrix[end][start] = 1; // Comment this out for directed graph
    }
}

void bfs(int startNode, int goal, int nodes) {
    int queue[MAX];
    int front = 0, rear = 0;
    int explored[MAX] = {0};
    int now;
    int flag = 0;

    queue[rear++] = startNode;
    visited[startNode] = 1;

    while (front < rear && flag==0) {
        
        now = queue[front++];

       printf("Doing goal test on %d\n", now);
        if (isGoal(now, goal)) {
            printf("\nGoal node %d found!\n", now);
            flag = 1;
            break;
        }
        if (flag==0){
        explored[now] = 1;

        for (int i = 0; i < nodes; i++) {
            if (adjacencyMatrix[now][i] == 1 && !visited[i] && !explored[i]) {
                printf("Added to queue %d\n", i);
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }}
    if(flag==0){
    printf("\nGoal node %d not found.\n", goal);}

    
    printf("Explored nodes: ");
    for (int i = 0; i < nodes; i++) {
        if (explored[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");

       printf("\nCurrent queue: ");
    for (int i = front; i < rear; i++) {
        printf("%d ", queue[i]);
    }
    printf("\n");
}

int main() {
    int start, end, startNode, goalNode, nodes, edges;
    printf("Enter the number of nodes: ");
    scanf("%d", &nodes);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    
    startGraph(nodes);
    
    printf("Enter the edges (start end):\n");
    for (int i = 0; i < edges; i++) {
        printf("Edge %d: ", i + 1);
        scanf("%d %d", &start, &end);
        addEdge(start, end);
    }
    
    printf("Enter the starting node for BFS: ");
    scanf("%d", &startNode);
    
    printf("Enter the goal node for BFS: ");
    scanf("%d", &goalNode);
    
    printf("BFS starting from node %d: ", startNode);
    bfs(startNode, goalNode, nodes);
    
    return 0;
}