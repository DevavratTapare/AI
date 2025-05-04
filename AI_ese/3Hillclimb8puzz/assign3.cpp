#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 3

// Goal state
int goal[SIZE][SIZE] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

typedef struct {
    int state[SIZE][SIZE];
    int cost;
    int blankX, blankY;
} Node;

// Manhattan Distance Heuristic
int calculateHeuristic(int state[SIZE][SIZE]) {
    int h = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int val = state[i][j];
            if (val != 0) {
                int goalX = (val - 1) / SIZE;
                int goalY = (val - 1) % SIZE;
                h += abs(i - goalX) + abs(j - goalY);
            }
        }
    }
    return h;
}

// Copy matrix
void copyState(int dest[SIZE][SIZE], int src[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            dest[i][j] = src[i][j];
}

// Print state
void printState(int state[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            printf("%d ", state[i][j]);
        printf("\n");
    }
    printf("\n");
}

// Move directions: up, down, left, right
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Hill Climbing Search
void hillClimbing(Node start) {
    Node current = start;
    current.cost = calculateHeuristic(current.state);

    while (1) {
        printf("Current state (h=%d):\n", current.cost);
        printState(current.state);

        if (current.cost == 0) {
            printf("Goal reached!\n");
            return;
        }

        Node next = current;
        int foundBetter = 0;

        for (int dir = 0; dir < 4; dir++) {
            int newX = current.blankX + dx[dir];
            int newY = current.blankY + dy[dir];

            if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE) {
                Node temp;
                copyState(temp.state, current.state);

                // Swap blank with adjacent
                temp.state[current.blankX][current.blankY] = temp.state[newX][newY];
                temp.state[newX][newY] = 0;
                temp.blankX = newX;
                temp.blankY = newY;
                temp.cost = calculateHeuristic(temp.state);

                if (temp.cost < current.cost) {
                    next = temp;
                    foundBetter = 1;
                }
            }
        }

        if (!foundBetter) {
            printf("No better neighbor found. Stuck at local minimum.\n");
            return;
        }

        current = next;
    }
}

int main() {
    Node start;
    printf("Enter the initial state (3x3, use 0 for blank):\n");
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            scanf("%d", &start.state[i][j]);
            if (start.state[i][j] == 0) {
                start.blankX = i;
                start.blankY = j;
            }
        }

    hillClimbing(start);
    return 0;
}
