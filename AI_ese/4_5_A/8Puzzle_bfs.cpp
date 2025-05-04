#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 3
#define INF 999

typedef struct {
    int mat[SIZE][SIZE];
    int x, y;  // blank tile position
    int priority; // heuristic
} Node;

Node openList[100];
int openCount = 0;

int goal[SIZE][SIZE] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

int heuristic(int mat[SIZE][SIZE]) {
    int h = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (mat[i][j] != 0) {
                int target_x = (mat[i][j] - 1) / SIZE;
                int target_y = (mat[i][j] - 1) % SIZE;
                h += abs(target_x - i) + abs(target_y - j);
            }
        }
    }
    return h;
}

int isGoal(int mat[SIZE][SIZE]) {
    return memcmp(mat, goal, sizeof(goal)) == 0;
}

void copyMatrix(int src[SIZE][SIZE], int dest[SIZE][SIZE]) {
    memcpy(dest, src, sizeof(int) * SIZE * SIZE);
}

void insertOpenList(int mat[SIZE][SIZE], int x, int y, int priority) {
    Node n;
    copyMatrix(mat, n.mat);
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

void BestFirstSearch(int mat[SIZE][SIZE], int x, int y) {
    insertOpenList(mat, x, y, heuristic(mat));

    while (openCount > 0) {
        Node current = openList[0];
        for (int i = 0; i < openCount - 1; i++)
            openList[i] = openList[i + 1];
        openCount--;

        printf("Step:\n");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++)
                printf("%d ", current.mat[i][j]);
            printf("\n");
        }
        printf("\n");

        if (isGoal(current.mat)) {
            printf("Goal Reached!\n");
            return;
        }

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int k = 0; k < 4; k++) {
            int nx = current.x + dx[k];
            int ny = current.y + dy[k];

            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
                Node next;
                copyMatrix(current.mat, next.mat);
                next.mat[current.x][current.y] = next.mat[nx][ny];
                next.mat[nx][ny] = 0;

                insertOpenList(next.mat, nx, ny, heuristic(next.mat));
            }
        }
    }
}

int main() {
    int puzzle[SIZE][SIZE] = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8}
    };
    printf("Best First Search (8 Puzzle):\n");
    BestFirstSearch(puzzle, 1, 1);
    return 0;
}