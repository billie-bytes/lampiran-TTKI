#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 2
#define MAX_USERNAME_LENGTH 100

typedef struct {
    char **usernames;
    int size;
    int capacity;
} UsernameArray;

void initArray(UsernameArray *arr) {
    arr->usernames = malloc(sizeof(char *) * INITIAL_CAPACITY);
    arr->size = 0;
    arr->capacity = INITIAL_CAPACITY;
}

void resizeArray(UsernameArray *arr) {
    arr->capacity *= 2;
    arr->usernames = realloc(arr->usernames, sizeof(char *) * arr->capacity);
    if (!arr->usernames) {
        perror("Failed to realloc");
        exit(1);
    }
}

void addUsername(UsernameArray *arr, const char *username) {
    if (arr->size == arr->capacity) {
        resizeArray(arr);
    }

    arr->usernames[arr->size] = malloc(strlen(username) + 1);
    if (!arr->usernames[arr->size]) {
        perror("Failed to malloc for username");
        exit(1);
    }

    strcpy(arr->usernames[arr->size], username);
    arr->size++;
}

void printUsernameAtIndex(UsernameArray *arr, int index) {
    if (index >= 0 && index < arr->size) {
        printf("Username at index %d: %s\n", index, arr->usernames[index]);
    } else {
        printf("Index out of bounds!\n");
    }
}

void freeArray(UsernameArray *arr) {
    for (int i = 0; i < arr->size; i++) {
        free(arr->usernames[i]);
    }
    free(arr->usernames);
}

// Flush remaining input
void flushInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    UsernameArray arr;
    initArray(&arr);

    int choice;
    char username[MAX_USERNAME_LENGTH];

    while (1) {
        printf("\n1. Add Username\n2. Get Username by Index\n3. Exit\nChoose: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }
        flushInput();

        if (choice == 1) {
            printf("Enter username: ");
            if (fgets(username, MAX_USERNAME_LENGTH, stdin) == NULL) {
                printf("Error reading input.\n");
                continue;
            }

            // Remove newline if present
            username[strcspn(username, "\n")] = '\0';
            addUsername(&arr, username);

        } else if (choice == 2) {
            printf("Enter index: ");
            if (scanf("%d", &choice) != 1) {
                printf("Invalid input.\n");
                flushInput();
                continue;
            }
            flushInput();
            printUsernameAtIndex(&arr, choice);

        } else if (choice == 3) {
            break;
        } else {
            printf("Invalid option!\n");
        }
    }

    freeArray(&arr);
    return 0;
}
