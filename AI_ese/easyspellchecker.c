#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000
#define LEN 50

// Structure to store vocabulary word and its frequency
typedef struct {
    char word[LEN];
    int freq;
} Vocab;

Vocab vocab[MAX];
int vocabSize = 0;

// Function to add a word to vocabulary
void add_vocab(char word[]) {
    // Check if word already exists
    for (int i = 0; i < vocabSize; i++) {
        if (strcmp(vocab[i].word, word) == 0) {
            vocab[i].freq++; // Increase frequency if found
            return;
        }
    }

    // If word not found, add new word
    int j = 0;
    while (word[j]) {
        vocab[vocabSize].word[j] = word[j];
        j++;
    }
    vocab[vocabSize].word[j] = '\0';  // Null terminate
    vocab[vocabSize].freq = 1;        // Set frequency to 1
    vocabSize++;                      // Increase vocab size
}

// Function to check if a word is in vocabulary and return its frequency
int in_vocab(char word[]) {
    for (int i = 0; i < vocabSize; i++) {
        if (strcmp(vocab[i].word, word) == 0)
            return vocab[i].freq;
    }
    return 0;  // Not found
}

// Function to suggest correction using substitution method
void suggest(char word[]) {
    // If word already correct
    if (in_vocab(word)) {
        printf("Word '%s' is correct.\n", word);
        return;
    }

    char suggestion[LEN] = "";
    int maxFreq = 0;

    // Try substituting each character
    for (int i = 0; word[i]; i++) {

        // Make a copy of word into modified
        char modified[LEN];
        int j = 0;
        while (word[j]) {
            modified[j] = word[j];
            j++;
        }
        modified[j] = '\0';

        // Substitute current character with 'a' to 'z'
        for (char c = 'a'; c <= 'z'; c++) {
            modified[i] = c;

            int freq = in_vocab(modified);

            // If valid word and better frequency, update suggestion
            if (freq > maxFreq || (freq == maxFreq && strcmp(modified, suggestion) < 0)) {
                maxFreq = freq;
                
                int k = 0;
                while (modified[k]) {
                    suggestion[k] = modified[k];
                    k++;
                }
                suggestion[k] = '\0';
            }
        }
    }

    // Print result
    if (maxFreq)
        printf("Suggested Correction: %s\n", suggestion);
    else
        printf("No suggestion found.\n");
}

int main() {
    int n;
    char word[LEN];

    // Input vocabulary
    printf("Enter number of words: ");
    scanf("%d", &n);

    printf("Enter words:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", word);
        add_vocab(word);
    }

    // Input word to check
    printf("Enter word to check: ");
    scanf("%s", word);

    // Suggest correction
    suggest(word);
    return 0;
}


// 3
//cat,hello,bye
//nat