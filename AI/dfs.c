#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100
int flag = 0;

int visited[MAX];
int adjacencyMatrix[MAX][MAX];

bool isGoal(int node, int goal) {
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

void dfs(int startNode, int goal, int nodes) {
    visited[startNode] = 1;

   printf("\nDoing goal test on %d", startNode);
    if (isGoal(startNode, goal)) {
        printf("\nGoal node %d found!\n", startNode);
        flag = 1;
        return;
    }

    for (int i = 0; i < nodes; i++) {
        if (adjacencyMatrix[startNode][i] == 1 && visited[i] == 0 && flag == 0) {
            dfs(i, goal, nodes);
        }
    }
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
    
    printf("Enter the starting node for DFS: ");
    scanf("%d", &startNode);
    
    printf("Enter the goal node for DFS: ");
    scanf("%d", &goalNode);
    
    printf("DFS starting from node %d: ", startNode);
    dfs(startNode, goalNode, nodes);
    
    return 0;
}
