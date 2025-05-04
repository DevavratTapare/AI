#include<iostream>
#include<vector>

using namespace std;

int SIZE;

typedef struct {
    vector<vector<int>> mat;
    int x, y;
    int g;
    int h;
    int f;
} Node;

vector<vector<int>> goalState;

void goalStateDetector() {
    goalState.resize(SIZE, vector<int>(SIZE));
    int counter = 1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == SIZE - 1 && j == SIZE - 1) {
                goalState[i][j] = 0;
            } else {
                goalState[i][j] = counter;
                counter++;
            }
        }
    }
}

void printMatrix(const vector<vector<int>>& mat) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
    printf("--------\n");
}

int isGoal(const vector<vector<int>>& mat) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (mat[i][j] != goalState[i][j])
                return 0;
    return 1;
}

int calculateHeuristic(const vector<vector<int>>& mat) {
    int h = 0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (mat[i][j] != 0 && mat[i][j] != goalState[i][j])
                h++;
    return h;
}

void copyMatrix(const vector<vector<int>>& src, vector<vector<int>>& dest) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            dest[i][j] = src[i][j];
}

void aStarSearch(Node start) {
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    Node queue[100];
    int front = 0, rear = 0;
    queue[rear++] = start;

    while (front < rear) {
        Node current = queue[front++];
        printMatrix(current.mat);

        if (isGoal(current.mat)) {
            printf("Goal reached with total cost: %d\n", current.f);
            return;
        }

        for (int k = 0; k < 4; k++) {
            int nx = current.x + dx[k];
            int ny = current.y + dy[k];

            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
                Node temp;
                temp.mat.resize(SIZE, vector<int>(SIZE)); // ✅ resize matrix
                copyMatrix(current.mat, temp.mat);
                temp.mat[current.x][current.y] = temp.mat[nx][ny];
                temp.mat[nx][ny] = 0;
                temp.x = nx;
                temp.y = ny;

                temp.g = current.g + 1;
                temp.h = calculateHeuristic(temp.mat);
                temp.f = temp.g + temp.h;

                int pos = rear;
                while (pos > front && queue[pos - 1].f > temp.f) {
                    queue[pos] = queue[pos - 1];
                    pos--;
                }
                queue[pos] = temp;
                rear++;
            }
        }
    }

    printf("Solution not found.\n");
}

int main() {
    cout << "Enter the size of the matrix - ";
    cin >> SIZE;

    goalStateDetector();

    Node start;
    start.mat.resize(SIZE, vector<int>(SIZE)); // ✅ resize matrix

    printf("Enter the %dx%d puzzle (use 0 for the blank tile):\n", SIZE, SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf("%d", &start.mat[i][j]);
            if (start.mat[i][j] == 0) {
                start.x = i;
                start.y = j;
            }
        }
    }

    start.g = 0;
    start.h = calculateHeuristic(start.mat);
    start.f = start.g + start.h;

    aStarSearch(start);
    return 0;
}
