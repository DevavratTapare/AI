#include <stdio.h>

void generateMagicSquare(int n) {
    if (n % 2 == 0) {
        printf("Only odd-order magic squares supported.\n");
        return;
    }

    int magic[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            magic[i][j] = 0;

    int num = 1, i = 0, j = n / 2;
    while (num <= n * n) 
    {
        magic[i][j] = num++;
        int newi = (i - 1 + n) % n;
        int newj = (j + 1) % n;
        
        if (magic[newi][newj])
            i = (i + 1) % n;
        else {
            i = newi;
            j = newj;
        }
    }

    printf("Magic Square of size %d:\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%3d ", magic[i][j]);
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter an odd number (e.g., 3, 5, 7): ");
    scanf("%d", &n);
    generateMagicSquare(n);
    return 0;
}
