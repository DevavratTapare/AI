#include <stdio.h>

#define MAX_VERTICES 100

int graph[MAX_VERTICES][MAX_VERTICES];
int colors[MAX_VERTICES];

// Function to check if it's valid to color a vertex with a given color
int is_valid(int node, int color, int N) {
    for (int i = 0; i < N; i++) {
        if (graph[node][i] && colors[i] == color)
            return 0;
    }
    return 1;
}

// Function to solve the graph coloring problem using backtracking
int solve(int node, int m, int N) {
    if (node == N)
        return 1;

    for (int c = 1; c <= m; c++) {
        if (is_valid(node, c, N)) {
            colors[node] = c;
            if (solve(node + 1, m, N))
                return 1;
            colors[node] = 0;
        }
    }
    return 0;
}

int main() {
    int N, E;

    // Get the number of vertices and edges from the user
    printf("Enter the number of vertices: ");
    scanf("%d", &N);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    // Initialize the graph
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            graph[i][j] = 0;
        }
    }

    // Get the edges from the user
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;  // Since the graph is undirected
    }

    // The maximum number of colors is the number of vertices
    int m = N;

    // Try to solve the graph coloring problem with N colors
    if (solve(0, m, N)) {
        printf("Solution found! Coloring of vertices:\n");
        for (int i = 0; i < N; i++) {
            printf("Vertex %d --> Color %d\n", i, colors[i]);
        }
    } else {
        printf("No solution found.\n");
    }

    return 0;
}
