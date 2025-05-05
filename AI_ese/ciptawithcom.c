#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char word1[10], word2[10], result[10];
char letters[10];
int used[10], mapping[26];
int total_unique = 0;

// Collect unique letters from a word
void collect_unique_letters(char *s) {
    for (int i = 0; s[i]; i++) {
        char ch = s[i];
        int found = 0;

        // Check if the letter is already added
        for (int j = 0; j < total_unique; j++) {
            if (letters[j] == ch) {
                found = 1;
                break;
            }
        }

        // If not added, add the letter
        if (!found) {
            letters[total_unique++] = ch;
        }
    }
}

// Convert word to number using current mapping
int get_value(char *s) {
    int val = 0;

    for (int i = 0; s[i]; i++) {
        int d = mapping[s[i] - 'A'];

        // If number starts with 0, invalid
        if (i == 0 && d == 0) return -1;

        val = val * 10 + d;
    }

    return val;
}

// Try all digit assignments using recursion
bool solve(int idx) {

    // All letters assigned, check solution
    if (idx == total_unique) {
        int w1 = get_value(word1);
        int w2 = get_value(word2);
        int res = get_value(result);

        // If any number invalid, skip
        if (w1 == -1 || w2 == -1 || res == -1) return false;

        // If valid solution found, print it
        if (w1 + w2 == res) {
            printf("✅ Solution Found:\n");

            for (int i = 0; i < total_unique; i++)
                printf("%c = %d\n", letters[i], mapping[letters[i] - 'A']);

            printf("%s = %d\n", word1, w1);
            printf("%s = %d\n", word2, w2);
            printf("%s = %d\n", result, res);

            return true;
        }

        return false;
    }

    // Try all digits for current letter
    for (int d = 0; d <= 9; d++) {

        if (!used[d]) {
            used[d] = 1;
            mapping[letters[idx] - 'A'] = d;

            if (solve(idx + 1)) return true;

            // Backtrack if not valid
            used[d] = 0;
        }
    }

    return false;
}

int main() {
    // Input words
    printf("Enter word1 (e.g., SEND): ");
    scanf("%s", word1);

    printf("Enter word2 (e.g., MORE): ");
    scanf("%s", word2);

    printf("Enter result (e.g., MONEY): ");
    scanf("%s", result);

    // Collect unique letters
    collect_unique_letters(word1);
    collect_unique_letters(word2);
    collect_unique_letters(result);

    // Check if too many unique letters
    if (total_unique > 10) {
        printf("Too many unique letters! Cannot solve.\n");
        return 1;
    }

    // Start solving
    if (!solve(0)) {
        printf("No solution found.\n");
    }

    return 0;
}
