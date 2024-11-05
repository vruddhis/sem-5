#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1000
#define MAX_ITERATIONS 100

typedef struct {
    int vertices[MAX_NODES];
    int direction[MAX_NODES];
    int length;
} Path;

typedef struct {
    int capacity[MAX_NODES][MAX_NODES];
    int flow[MAX_NODES][MAX_NODES];
    int n;
} Graph;

typedef struct {
    Graph curr_graph;
    Path chosen_path;
} Iteration;

int min(int x, int y) {
    return x < y ? x : y;
}

Path createPath() {
    Path path;
    path.length = 0;
    return path;
}

void enqueue(int *q, int *tail, int x) {
    q[(*tail)++] = x;
}

int dequeue(int *q, int *head) {
    return q[(*head)++];
}

Path bfs(Graph *g, int start, int target) {
    int head = 0, tail = 0;
    int queue[MAX_NODES];
    int pred[MAX_NODES];
    int direction[MAX_NODES];
    int color[MAX_NODES];

    for (int i = 0; i < g->n; i++) {
        color[i] = -1;
        pred[i] = -1;
    }

    enqueue(queue, &tail, start);
    color[start] = 0;

    while (head < tail) {
        int u = dequeue(queue, &head);
        for (int v = 0; v < g->n; v++) {
            if (color[v] == -1) {
                if (g->capacity[u][v] - g->flow[u][v] > 0) {
                    enqueue(queue, &tail, v);
                    color[v] = 0;
                    pred[v] = u;
                    direction[v] = 0;
                } else if (g->flow[v][u] > 0) {
                    enqueue(queue, &tail, v);
                    color[v] = 0;
                    pred[v] = u;
                    direction[v] = 1;
                }
            }
        }
    }

    Path path = createPath();
    if (color[target] == 0) {
        for (int v = target; v != -1; v = pred[v]) {
            path.vertices[path.length] = v;
            path.direction[path.length] = direction[v];
            path.length++;
        }
        for (int i = 0; i < path.length / 2; i++) {
            int temp = path.vertices[i];
            path.vertices[i] = path.vertices[path.length - 1 - i];
            path.vertices[path.length - 1 - i] = temp;

            temp = path.direction[i];
            path.direction[i] = path.direction[path.length - 1 - i];
            path.direction[path.length - 1 - i] = temp;
        }
    }
    return path;
}

Graph updateGraph(Graph *g, Path *path) {
    Graph new_graph = *g;
    int increment = 1000000000;

    for (int i = 0; i < path->length - 1; i++) {
        int u = path->vertices[i];
        int v = path->vertices[i + 1];
        if (path->direction[i + 1] == 0) {
            increment = min(increment, g->capacity[u][v] - g->flow[u][v]);
        } else {
            increment = min(increment, g->flow[v][u]);
        }
    }

    for (int i = 0; i < path->length - 1; i++) {
        int u = path->vertices[i];
        int v = path->vertices[i + 1];
        if (path->direction[i + 1] == 0) {
            new_graph.flow[u][v] += increment;
            new_graph.flow[v][u] -= increment;
        } else {
            new_graph.flow[v][u] += increment;
            new_graph.flow[u][v] -= increment;
        }
    }
    return new_graph;
}

int main() {
    Graph g;
    printf("Enter the number of nodes: ");
    scanf("%d", &g.n);

    for (int i = 0; i < g.n; i++) {
        for (int j = 0; j < g.n; j++) {
            g.capacity[i][j] = 0;
            g.flow[i][j] = 0;
        }
    }

    int edges;
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges in format <from> <to> <capacity>:\n");
    for (int i = 0; i < edges; i++) {
        int from, to, capacity;
        scanf("%d %d %d", &from, &to, &capacity);
        g.capacity[from][to] = capacity;
    }

    int source, sink;
    printf("Enter source and sink: ");
    scanf("%d %d", &source, &sink);

    int max_flow = 0;
    Iteration iterations[MAX_ITERATIONS];
    int iteration_count = 0;

    while (1) {
        Path path = bfs(&g, source, sink);
        if (path.length == 0) {
            break;
        }
        iterations[iteration_count].curr_graph = g;
        iterations[iteration_count].chosen_path = path;
        iteration_count++;
        g = updateGraph(&g, &path);
        max_flow += 1000000000; 
    }

    printf("Max Flow: %d\n", max_flow);
    printf("Iterations:\n");
    for (int i = 0; i < iteration_count; i++) {
        printf("Iteration %d:\n", i + 1);
        printf("Current Flow Matrix:\n");
        for (int j = 0; j < g.n; j++) {
            for (int k = 0; k < g.n; k++) {
                printf("%d ", iterations[i].curr_graph.flow[j][k]);
            }
            printf("\n");
        }
        printf("Chosen Path: ");
        for (int j = 0; j < iterations[i].chosen_path.length; j++) {
            printf("%d(%d) ", iterations[i].chosen_path.vertices[j], iterations[i].chosen_path.direction[j]);
        }
        printf("\n");
    }

    return 0;
}
