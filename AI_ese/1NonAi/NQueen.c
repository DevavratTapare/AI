#include <stdio.h>
#define N 4
int board[N];

int isSafe(int row, int col) {
    for (int i = 0; i < row; i++)
        if (board[i] == col || abs(board[i] - col) == row - i)
            return 0;
    return 1;
}

void printBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%c ", (board[i] == j) ? 'Q' : '.');
        printf("\n");
    }
    printf("\n");
}

void solve(int row) {
    if (row == N) {
        printBoard();
        return;
    }
    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row] = col;
            solve(row + 1);
        }
    }
}

int main() {
    printf("N-Queens solutions for N = %d:\n\n", N);
    solve(0);
    return 0;
}
