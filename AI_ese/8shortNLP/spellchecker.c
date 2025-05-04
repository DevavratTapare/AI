#include <stdio.h>
#include <string.h>

struct Dictionary {
    char word[20];
};

int main() {
    // Small predefined dictionary
    struct Dictionary dictionary[] = {
        {"cat"}, {"dog"}, {"run"}, {"beautiful"},
        {"quickly"}, {"happy"}, {"eat"}, {"apple"},
        {"blue"}, {"green"}, {"car"}, {"tree"}
    };

    int dict_size = sizeof(dictionary) / sizeof(dictionary[0]);
    char input[200];

    printf("Enter a sentence: ");
    fgets(input, sizeof(input), stdin);

    // Split input into words
    char *token = strtok(input, " ,.\n");

    while (token != NULL) {
        int found = 0;

        // Search the dictionary
        for (int i = 0; i < dict_size; i++) {
            if (strcmp(token, dictionary[i].word) == 0) {
                found = 1;
                break;
            }
        }

        if (found) {
            printf("Word: %-10s -> Correct\n", token);
        } else {
            printf("Word: %-10s -> Misspelled\n", token);
        }

        token = strtok(NULL, " ,.\n");
    }

    return 0;
}
