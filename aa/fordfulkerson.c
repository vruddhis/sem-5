#include <stdio.h>
#include <stdlib.h>

typedef struct graph {
    int n;
    int flows[10][10];
    int residual[10][10];
    int reverse[10][10];
    struct graph* next;
} graph;

typedef struct path {
    int len;
    int order[10];
    int min_value;
} path;

typedef struct iteration {
    graph* g;
    path* p;
} it;

graph* initialize() {
    graph* new = (graph*)malloc(sizeof(graph));
    printf("How many vertices? ");
    int n, c;
    scanf("%d", &n);
    new->n = n;
    
    printf("Vertex 0 is s, vertex %d is t.\n", n - 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                new->residual[i][j] = 0;
                new->flows[i][j] = 0;
                new->reverse[i][j] = 0;
            }
            printf("What is the capacity from vertex %d to %d? ", i, j);
            scanf("%d", &c);
            new->residual[i][j] = c;
            new->flows[i][j] = 0;
            new->reverse[i][j] = 0;
        }
    }
    new->next = NULL;
    return new;
}

it* augmented_path(graph* curr_g) {
    int n = curr_g->n;
    int visited[10] = {0}; 
    int parent[10] = {-1}; 
    int queue[10];
    int front = 0, rear = 0;
    int flag;

    queue[rear++] = 0; 
    visited[0] = 1;

    
    while (front < rear && visited[n-1] == 0) { 
        int u = queue[front++];
        for (int v = 0; v < n; v++) {
            
            if (visited[v] == 0 && curr_g->residual[u][v] > 0) {
                queue[rear++] = v;
                visited[v] = 1;
                parent[v] = u;
            }
            
            else if (visited[v] == 0 && curr_g->reverse[u][v] > 0) {
                queue[rear++] = v;
                visited[v] = 1;
                parent[v] = u;
            }
        }
    }

    
    if (visited[n-1] == 0) {
        return NULL;
    }


    path* p = (path*)malloc(sizeof(path));
    p->len = 0;
    p->min_value = __INT_MAX__; 

    int v = n-1;
    while (v != 0) { 
        p->order[p->len++] = v;
        int u = parent[v];
        if (curr_g->residual[u][v] > 0) {
            p->min_value = (curr_g->residual[u][v] < p->min_value) ? curr_g->residual[u][v] : p->min_value;
        } else {
            p->min_value = (curr_g->reverse[u][v] < p->min_value) ? curr_g->reverse[u][v] : p->min_value;
        }
        v = u;
    }
    p->order[p->len++] = 0; 

   
    for (int i = 0; i < p->len / 2; i++) {
        int temp = p->order[i];
        p->order[i] = p->order[p->len - i - 1];
        p->order[p->len - i - 1] = temp;
    }

    it* new_it = (it*)malloc(sizeof(it));
    new_it->g = curr_g;
    new_it->p = p;
    return new_it;
}

void update_graph(graph* g, path* p) {
    for (int i = 0; i < p->len - 1; i++) {
        int u = p->order[i];
        int v = p->order[i + 1];

        
        g->flows[u][v] += p->min_value;
        g->residual[u][v] -= p->min_value;
        g->reverse[v][u] += p->min_value;
    }
}

int ford_fulkerson(graph* g) {
    int max_flow = 0;
    it* iterations[100]; 
    int iteration_count = 0;

    while (1) {
        
        it* current_it = augmented_path(g);
        if (current_it == NULL) {
            break; 
        }

        max_flow += current_it->p->min_value;
        update_graph(g, current_it->p);
        iterations[iteration_count++] = current_it;
    }

    

    return max_flow;
}

int main() {
    graph* g = initialize();
    int max_flow = ford_fulkerson(g);
    printf("\nThe maximum possible flow is %d\n", max_flow);
    return 0;
}
