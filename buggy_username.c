#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 2
#define MAX_USERNAME_LENGTH 100

// Struct to represent a dynamic array of usernames
typedef struct {
    char **usernames;
    int size;
    int capacity;
} UsernameArray;

// Initialize the dynamic array
void initArray(UsernameArray *arr) {
    arr->usernames = (char**)malloc(sizeof(char *) * INITIAL_CAPACITY);
    arr->size = 0;
    arr->capacity = INITIAL_CAPACITY;
}

// Resize the array when full
void resizeArray(UsernameArray *arr) {
    arr->capacity *= 2;
    arr->usernames = (char**)realloc(arr->usernames, sizeof(char *) * arr->capacity);
}

// Add a username
void addUsername(UsernameArray *arr, const char *username) {
    if (arr->size == arr->capacity) {
        resizeArray(arr);
    }

    arr->usernames[arr->size] = (char*)malloc(strlen(username) + 1);
    strcpy(arr->usernames[arr->size], username);
    arr->size++;
}

// Access username by index
void printUsernameAtIndex(UsernameArray *arr, int index) {
    if (index >= 0 && index < arr->size) {
        printf("Username at index %d: %s\n", index, arr->usernames[index]);
    } else {
        printf("Index out of bounds!\n");
    }
}

// Free memory
void freeArray(UsernameArray *arr) {
    for (int i = 0; i < arr->size; i++) {
        free(arr->usernames[i]);
    }
    free(arr->usernames);
}

// Demo / Main function
int main() {
    UsernameArray arr;
    initArray(&arr);

    int choice;
    char username[MAX_USERNAME_LENGTH+1];
    int index;

    while (1) {
        printf("\n1. Add Username\n2. Get Username by Index\n3. Exit\nChoose: ");
        scanf("%d", &choice);
        getchar(); // clear newline from buffer

        switch (choice) {
            case 1:
                printf("Enter username: ");
                fgets(username, MAX_USERNAME_LENGTH, stdin);
                username[strcspn(username, "\n")] = 0; // remove newline
                addUsername(&arr, username);
                break;
            case 2:
                printf("Enter index: ");
                scanf("%d", &index);
                printUsernameAtIndex(&arr, index);
                break;
            case 3:
                freeArray(&arr);
                return 0;
            default:
                printf("Invalid option!\n");
        }
    }
}
