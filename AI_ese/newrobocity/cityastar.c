#include <stdio.h>

#define MAX 5
#define INF 999

char cities[MAX] = {'A', 'B', 'C', 'D', 'E'};
int graph[MAX][MAX] = {
    {0, 1, 4, INF, INF},
    {1, 0, INF, 3, INF},
    {4, INF, 0, 1, INF},
    {INF, 3, 1, 0, 2},
    {INF, INF, INF, 2, 0}
};

int heuristic[MAX] = {7, 6, 2, 1, 0};
int visited[MAX] = {0};

typedef struct {
    int city;
    int priority; // here priority = g + h (cost so far + heuristic) -> for A*
    int cost_so_far;
} Node;

Node openList[MAX];
int openCount = 0;

void insertOpenList(int city, int cost_so_far, int priority) {
    Node n;
    n.city = city;
    n.cost_so_far = cost_so_far;
    n.priority = priority;

    int i = openCount - 1;
    while (i >= 0 && openList[i].priority > n.priority) {
        openList[i + 1] = openList[i];
        i--;
    }
    openList[i + 1] = n;
    openCount++;
}

void AStar(int start, int goal) {
    insertOpenList(start, 0, heuristic[start]);

    while (openCount > 0) {
        Node current = openList[0];
        for (int i = 0; i < openCount - 1; i++)
            openList[i] = openList[i + 1];
        openCount--;

        if (visited[current.city])
            continue;

        visited[current.city] = 1;
        printf("%c ", cities[current.city]);

        if (current.city == goal)
            return;

        for (int i = 0; i < MAX; i++) {
            if (graph[current.city][i] != INF && !visited[i]) {
                int new_cost = current.cost_so_far + graph[current.city][i];
                insertOpenList(i, new_cost, new_cost + heuristic[i]);
            }
        }
    }
}

int main() {
    printf("A* Search Path:\n");
    AStar(0, 4);
    return 0;
}
