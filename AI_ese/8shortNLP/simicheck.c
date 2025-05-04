#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_LEN 50

// Split sentence into words (returns count)
int split_into_words(char sentence[], char words[][MAX_LEN]) {
    int count = 0;
    char *token = strtok(sentence, " ,.\n");

    while (token != NULL) {
        strcpy(words[count], token);
        count++;
        token = strtok(NULL, " ,.\n");
    }

    return count;
}

// Calculate similarity
float calculate_similarity(char words1[][MAX_LEN], int count1, char words2[][MAX_LEN], int count2) {
    int common = 0;

    for (int i = 0; i < count1; i++) {
        for (int j = 0; j < count2; j++) {
            if (strcmp(words1[i], words2[j]) == 0) {
                common++;
                break;  // Count only once
            }
        }
    }

    int total = count1 + count2 - common;

    if (total == 0)
        return 0.0;

    return (float)common / total;
}

int main() {
    char sentence1[200];
    char sentence2[200];
    char words1[MAX_WORDS][MAX_LEN];
    char words2[MAX_WORDS][MAX_LEN];

    printf("Enter first sentence: ");
    fgets(sentence1, sizeof(sentence1), stdin);

    printf("Enter second sentence: ");
    fgets(sentence2, sizeof(sentence2), stdin);

    int count1 = split_into_words(sentence1, words1);
    int count2 = split_into_words(sentence2, words2);

    float similarity = calculate_similarity(words1, count1, words2, count2);

    printf("\nSimilarity Score: %.2f\n", similarity);

    return 0;
}
