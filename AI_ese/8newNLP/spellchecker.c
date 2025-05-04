#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 10000
#define MAX_LEN 50

// Vocabulary structure
typedef struct {
    char word[MAX_LEN];
    int frequency;
} VocabularyItem;

VocabularyItem vocab[MAX_WORDS];
int vocabSize = 0;

// Convert word to lowercase
void to_lowercase(char *word) {
    for (int i = 0; word[i]; i++)
        word[i] = tolower(word[i]);
}

// Add word to vocabulary
void add_to_vocab(char *word) {
    to_lowercase(word);
    for (int i = 0; i < vocabSize; i++) {
        if (strcmp(vocab[i].word, word) == 0) {
            vocab[i].frequency++;
            return;
        }
    }
    strcpy(vocab[vocabSize].word, word);
    vocab[vocabSize].frequency = 1;
    vocabSize++;
}

// Get frequency
int get_frequency(const char *word) {
    for (int i = 0; i < vocabSize; i++) {
        if (strcmp(vocab[i].word, word) == 0)
            return vocab[i].frequency;
    }
    return 0;
}

// Check existence
int is_in_vocab(const char *word) {
    return get_frequency(word) > 0;
}

// Add candidate if valid
int add_candidate(char candidates[][MAX_LEN], int count, const char *word) {
    if (is_in_vocab(word)) {
        for (int i = 0; i < count; i++) {
            if (strcmp(candidates[i], word) == 0)
                return count;
        }
        strcpy(candidates[count++], word);
    }
    return count;
}

// Generate candidates (Substitute, Delete, Swap)
int generate_candidates(char word[], char candidates[][MAX_LEN]) {
    int count = 0;
    int len = strlen(word);

    // Substitution
    for (int i = 0; i < len; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            char temp[MAX_LEN];
            strcpy(temp, word);
            temp[i] = c;
            count = add_candidate(candidates, count, temp);
        }
    }

    // Deletion
    for (int i = 0; i < len; i++) {
        char temp[MAX_LEN];
        strncpy(temp, word, i);
        strcpy(temp + i, word + i + 1);
        count = add_candidate(candidates, count, temp);
    }

    // Swap
    for (int i = 1; i < len; i++) {
        char temp[MAX_LEN];
        strcpy(temp, word);
        char t = temp[i];
        temp[i] = temp[i - 1];
        temp[i - 1] = t;
        count = add_candidate(candidates, count, temp);
    }

    return count;
}

// Suggest correction
void suggest_word(char word[]) {
    if (is_in_vocab(word)) {
        printf("Word: %s -> Correct (no correction needed)\n", word);
        return;
    }

    char candidates[500][MAX_LEN];
    int count = generate_candidates(word, candidates);

    if (count == 0) {
        printf("Word: %s -> No suggestions\n", word);
        return;
    }

    int maxFreq = 0;
    char suggestion[MAX_LEN];
    for (int i = 0; i < count; i++) {
        int freq = get_frequency(candidates[i]);
        if (freq > maxFreq || (freq == maxFreq && strcmp(candidates[i], suggestion) < 0)) {
            maxFreq = freq;
            strcpy(suggestion, candidates[i]);
        }
    }

    printf("Word: %s -> Suggested Correction: %s\n", word, suggestion);
}

int main() {
    char word[MAX_LEN];
    int numWords;

    printf("Enter number of words in vocabulary: ");
    scanf("%d", &numWords);

    printf("Enter words:\n");
    for (int i = 0; i < numWords; i++) {
        scanf("%s", word);
        add_to_vocab(word);
    }

    printf("\nEnter word to check: ");
    scanf("%s", word);

    to_lowercase(word);
    suggest_word(word);

    return 0;
}
