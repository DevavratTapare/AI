#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100
#define MAX_LEN 50

// Function to convert a string to lowercase
void to_lowercase(char *str) {
    while (*str) {
        *str = tolower(*str);
        str++;
    }
}

// Split sentence into words and return word count
int split_into_words(char sentence[], char words[][MAX_LEN]) {
    int count = 0;
    char *token = strtok(sentence, " ,.\n");

    while (token != NULL && count < MAX_WORDS) {
        to_lowercase(token);
        strcpy(words[count], token);
        count++;
        token = strtok(NULL, " ,.\n");
    }

    return count;
}

// Check if a word is already in the list
int is_in_list(char word[], char list[][MAX_LEN], int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(word, list[i]) == 0)
            return 1;
    }
    return 0;
}

// Calculate Jaccard Similarity
float calculate_similarity(char words1[][MAX_LEN], int count1, char words2[][MAX_LEN], int count2) {
    int common = 0;
    char unionSet[MAX_WORDS * 2][MAX_LEN];
    int unionCount = 0;

    // Count common and build union set
    for (int i = 0; i < count1; i++) {
        if (!is_in_list(words1[i], unionSet, unionCount)) {
            strcpy(unionSet[unionCount++], words1[i]);
        }
    }

    for (int i = 0; i < count2; i++) {
        if (!is_in_list(words2[i], unionSet, unionCount)) {
            strcpy(unionSet[unionCount++], words2[i]);
        }
    }

    // Count common words
    for (int i = 0; i < count1; i++) {
        for (int j = 0; j < count2; j++) {
            if (strcmp(words1[i], words2[j]) == 0) {
                common++;
                break;
            }
        }
    }

    if (unionCount == 0)
        return 0.0;

    return (float)common / unionCount;
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

    printf("\nSimilarity Score : %.2f\n", similarity);

    return 0;
}
