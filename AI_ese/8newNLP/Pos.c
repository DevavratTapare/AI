#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 20

// Structure to store word and its Part of Speech
struct WordPOS {
    char word[MAX_WORD_LENGTH];
    char pos[MAX_WORD_LENGTH];
};

// Function to check suffix-based heuristic
const char* guessPOS(const char* word) {
    int len = strlen(word);
    if (len >= 2 && strcmp(&word[len-2], "ly") == 0) return "adverb";
    if (len >= 3 && strcmp(&word[len-3], "ing") == 0) return "verb";
    if (len >= 2 && strcmp(&word[len-2], "ed") == 0) return "verb";
    if (len >= 3 && strcmp(&word[len-3], "ous") == 0) return "adjective";
    if (len >= 3 && strcmp(&word[len-3], "ful") == 0) return "adjective";
    if (len >= 4 && strcmp(&word[len-4], "ness") == 0) return "noun";
    return "Unknown";
}

int main() {
    // Define a basic POS dictionary
    struct WordPOS dictionary[] = {
        {"cat", "noun"},
        {"dog", "noun"},
        {"run", "verb"},
        {"is", "verb"},
        {"eat", "verb"},
        {"beautiful", "adjective"},
        {"happy", "adjective"},
        {"blue", "adjective"},
        {"quickly", "adverb"},
        {"apple", "noun"},
        {"and", "conjunction"},
        {"the", "article"},
        {"a", "article"}
    };

    int dict_size = sizeof(dictionary) / sizeof(dictionary[0]);

    // Take user input
    char input[256];
    printf("Enter a sentence: ");
    fgets(input, sizeof(input), stdin);

    // Tokenize the input
    char *token = strtok(input, " ,.-!\n");

    printf("\n--- POS Tagging Output ---\n");
    while (token != NULL) {
        int found = 0;

        // Search dictionary for the word
        for (int i = 0; i < dict_size; i++) {
            if (strcmp(token, dictionary[i].word) == 0) {
                printf("Word: %-12s -> POS: %s (dictionary)\n", token, dictionary[i].pos);
                found = 1;
                break;
            }
        }

        if (!found) {
            const char* guessed_pos = guessPOS(token);
            printf("Word: %-12s -> POS: %s (guessed)\n", token, guessed_pos);
        }

        // Move to next token
        token = strtok(NULL, " ,.-!\n");
    }

    return 0;
}