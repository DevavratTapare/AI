#include <stdio.h>
#include <stdlib.h>

#define SIZE 5
#define INF 999

char grid[SIZE][SIZE] = {
    {'S', '.', '.', '.', '.'},
    {'.', '#', '#', '.', '.'},
    {'.', '.', '.', '#', '.'},
    {'.', '#', '.', '.', 'G'},
    {'.', '.', '.', '.', '.'}
};

int goal_x = 3, goal_y = 4; // Goal position (G)
int visited[SIZE][SIZE] = {0};

typedef struct {
    int x, y;
    int priority; // heuristic for Best First
} Node;

Node openList[SIZE * SIZE];
int openCount = 0;

int heuristic(int x, int y) {
    return abs(goal_x - x) + abs(goal_y - y);
}

void insertOpenList(int x, int y, int priority) {
    Node n;
    n.x = x;
    n.y = y;
    n.priority = priority;

    int i = openCount - 1;
    while (i >= 0 && openList[i].priority > n.priority) {
        openList[i + 1] = openList[i];
        i--;
    }
    openList[i + 1] = n;
    openCount++;
}

void BestFirstSearch(int sx, int sy) {
    insertOpenList(sx, sy, heuristic(sx, sy));

    while (openCount > 0) {
        Node current = openList[0];
        for (int i = 0; i < openCount - 1; i++)
            openList[i] = openList[i + 1];
        openCount--;

        if (visited[current.x][current.y])
            continue;

        visited[current.x][current.y] = 1;
        printf("(%d,%d) ", current.x, current.y);

        if (current.x == goal_x && current.y == goal_y)
            return;

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int k = 0; k < 4; k++) {
            int nx = current.x + dx[k];
            int ny = current.y + dy[k];

            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE &&
                grid[nx][ny] != '#' && !visited[nx][ny]) {
                insertOpenList(nx, ny, heuristic(nx, ny));
            }
        }
    }
}

int main() {
    printf("Best First Search Path:\n");
    BestFirstSearch(0, 0);
    return 0;
}
