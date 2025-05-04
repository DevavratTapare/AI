#include <stdio.h>
#include <string.h>

struct WordPOS {
    char word[20];
    char pos[20];
};

int main() {
    // Define a very small dictionary
    struct WordPOS dictionary[] = {
        {"cat", "noun"},
        {"dog", "noun"},
        {"run", "verb"},
        {"beautiful", "adjective"},
        {"quickly", "adverb"},
        {"is", "verb"},
        {"happy", "adjective"},
        {"eat", "verb"},
        {"apple", "noun"},
        {"blue", "adjective"}
    };

    int dict_size = sizeof(dictionary) / sizeof(dictionary[0]);
    char input[100];

    printf("Enter a sentence: ");
    fgets(input, sizeof(input), stdin);

    // Tokenize input into words
    char *token = strtok(input, " ,.\n");

    while (token != NULL) {
        int found = 0;

        // Search the dictionary
        for (int i = 0; i < dict_size; i++) {
            if (strcmp(token, dictionary[i].word) == 0) {
                printf("Word: %-10s -> POS: %s\n", token, dictionary[i].pos);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Word: %-10s -> POS: Unknown\n", token);
        }

        token = strtok(NULL, " ,.\n");
    }

    return 0;
}
