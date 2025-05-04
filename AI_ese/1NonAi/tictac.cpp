#include <stdio.h>

char board[3][3];

void initialize() {
    for (int i = 0, k = '1'; i < 3; i++)
        for (int j = 0; j < 3; j++, k++)
            board[i][j] = k;
}

void drawBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i < 2) printf("---|---|---\n");
    }
    printf("\n");
}

int checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return 1;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return 1;
    return 0;
}

int main() {
    int move, player = 0;
    char mark;
    initialize();

    for (int turn = 0; turn < 9; turn++) {
        drawBoard();
        player = turn % 2 + 1;
        if (player == 1)
            mark = 'X';
        else
            mark = 'O';

        printf("Player %d [%c], enter your move (1-9): ", player, mark);
        scanf("%d", &move);

        int row = (move - 1) / 3, col = (move - 1) % 3;
        if (board[row][col] == 'X' || board[row][col] == 'O') {
            printf("Invalid move! Try again.\n");
            turn--;
            continue;
        }
        board[row][col] = mark;

        if (checkWin()) {
            drawBoard();
            printf("Player %d [%c] wins!\n", player, mark);
            return 0;
        }
    }

    drawBoard();
    printf("It's a draw!\n");
    return 0;
}
