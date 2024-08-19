#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define GOAL 5
int visited[MAX];
int adjacencyMatrix[MAX][MAX];
void startGraph(int nodes) {
   for (int i = 0; i < nodes; i++) {
       visited[i] = 0;
        }
}
void addEdge(int start, int end) {
   adjacencyMatrix[start][end] = 1;
   adjacencyMatrix[end][start] = 1; //comment this out for directed graph
}
int is_goal_state(int node){
    if (node == GOAL){
        return 1;
    }
    return 0;
}
void bfs(int startNode, int nodes) {
    int queue[MAX];
    int front = -1, rear = -1;
    int now;

    queue[rear + 1] = startNode;
    rear++;
    visited[startNode] = 1;

    while (front != rear) {
        now = queue[front + 1];
        front++;

        printf("Processing: %d\n ", now);
        if(is_goal_state(now) == 1){
            printf("Found goal state at %d", now);
            return;
        }

        for (int i = 0; i < nodes; i++) {
            if (adjacencyMatrix[now][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                queue[rear + 1] = i;
                printf("Adding to queue: %d\n", i);
 rear = rear + 1;

            }
        }
    }

    printf("\n");
}

int main() {
   int start, end, startNode, nodes, edges;
   printf("Enter the number of nodes: ");
   scanf("%d", &nodes);
   printf("Enter the number of edges: ");
   scanf("%d", &edges);
   startGraph(nodes);
   printf("Enter the edges:\n");
   for (int i = 0; i < edges; i++) {
       printf("what is start?");
       scanf("%d", &start);
       printf("what is end?");
       scanf("%d", &end);
      addEdge(start, end);
   }
   printf("Enter the starting node for BFS: ");
   scanf("%d", &startNode);
   printf("BFS starting from node %d: ", startNode);
   bfs(startNode, nodes);
   return 0;
}

