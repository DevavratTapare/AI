#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 10

char grid[SIZE][SIZE];
int blocked[][2] = {
    {1,1},{1,2},{1,3},{3,5},{4,5},{5,5},
    {7,0},{7,1},{7,2},{8,8},{8,9},{9,8}
};
int blocked_count = sizeof(blocked) / sizeof(blocked[0]);

void initGrid() {
    for(int i=0; i<SIZE; i++)
        for(int j=0; j<SIZE; j++)
            grid[i][j] = '-';

    for(int i=0; i<blocked_count; i++)
        grid[blocked[i][0]][blocked[i][1]] = '+';
}

void printGrid() {
    for(int i=0; i<SIZE; i++) {
        for(int j=0; j<SIZE; j++) {
            if(grid[i][j] == '+')
                printf("# ");
            else if(grid[i][j] == '-')
                printf(". ");
            else
                printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}

int canPlace(int row, int col, char word[], char dir) {
    int len = strlen(word);
    for(int k=0; k<len; k++) {
        int x = row + (dir=='V' ? k : 0);
        int y = col + (dir=='H' ? k : 0);
        if(x >= SIZE || y >= SIZE) return 0;
        if(grid[x][y] != '-' && grid[x][y] != word[k]) return 0;
        if(grid[x][y] == '+') return 0;
    }
    return 1;
}

void place(int row, int col, char word[], char dir) {
    for(int k=0; k<strlen(word); k++) {
        int x = row + (dir=='V' ? k : 0);
        int y = col + (dir=='H' ? k : 0);
        grid[x][y] = word[k];
    }
}

int tryPlace(char word[]) {
    for(int i=0; i<SIZE; i++)
        for(int j=0; j<SIZE; j++)
            if(grid[i][j]==word[0] && (canPlace(i,j,word,'H') || canPlace(i,j,word,'V'))) {
                if(canPlace(i,j,word,'H')) place(i,j,word,'H');
                else place(i,j,word,'V');
                return 1;
            }

    for(int i=0; i<SIZE; i++)
        for(int j=0; j<SIZE; j++)
            if(canPlace(i,j,word,'H') || canPlace(i,j,word,'V')) {
                if(canPlace(i,j,word,'H')) place(i,j,word,'H');
                else place(i,j,word,'V');
                return 1;
            }

    return 0;
}

int main() {
    initGrid();
    printGrid();

    printf("\nEnter words (type DONE to finish):\n");

    char word[SIZE+1];
    while(1) {
        printf("\nWord: ");
        scanf("%s", word);
        for(int i=0; word[i]; i++) word[i] = toupper(word[i]);
        if(strcmp(word,"DONE")==0) break;

        if(tryPlace(word)) printf("Word placed.\n");
        else printf("Cannot place word.\n");

        printGrid();
    }

    printf("\nFinal Crossword:\n");
    printGrid();
    return 0;
}
