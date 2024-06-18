#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "score.h"

/*10. Generalno upotreba pokazivača tamo gdje su potrebni*/
/*14. Koristiti dinamičko zauzimanje memorije za bilo koji tip podatka, osobito za složene tipove podataka*/

USER* allocateUser() {
    USER* user = (USER*)calloc(1, sizeof(USER));
    if (user == NULL) {
        fprintf(stderr, "Error allocating memory\n");
        exit(EXIT_FAILURE);
    }
    return user;
}

void freeUser(USER* user) {
    free(user);
}

void enterUsername(USER* user) {
    getchar();
    printf("Enter username\n>>> ");
    if (fgets(user->username, MAX_USERNAME_LENGTH, stdin) == NULL) {
        printf("Failed to read username\n");
        exit(EXIT_FAILURE);
    }

    removeNewline(user->username);
}

void removeNewline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

/*19. Koristiti funkcije remove(), rename()*/

void createAndRenameFiles(const char* prompt) {
    if (prompt == NULL) {
        fprintf(stderr, "Invalid file name for creating and renaming files\n");
        return;
    }
    FILE* file = fopen(prompt, "r");
    if (file) {
        // If file exists, close it
        fclose(file);
    }
    else {
        // Create file if it doesn't exist
        file = fopen("generic.txt", "w");
        if (file == NULL) {
            perror("Error creating generic file");
            exit(EXIT_FAILURE);
        }
        fclose(file);

        if (rename("generic.txt", prompt) != 0) {
            perror("Error renaming file to target filename");
            exit(EXIT_FAILURE);
        }
    }
}

void cleanupFiles(const char* prompt) {
    if (prompt == NULL) {
        fprintf(stderr, "Invalid file name for cleanup\n");
        return;
    }
    if (remove(prompt) != 0) {
        perror("Error deleting %s", prompt);
    }
}

/*12. Zaštita parametara kod svih funkcija*/
/*17. Datoteke, koristiti tekstualnu ili binarnu, provjera pokazivača i zatvaranje datoteke*/
/*20. Upravljati s pogreškama, errno, perror(), strerror(), feof(), ferror()*/

void saveScore(const USER* user, const char* prompt) {
    FILE* file = fopen(prompt, "a");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s\t\t%d\n", user->username, user->score);
    fclose(file);
}

int loadScore(USER scores[], int maxUsers, const char* prompt) {
    if (scores == NULL || prompt == NULL || maxUsers <= 0) {
        fprintf(stderr, "Invalid parameters for loadScore\n");
        return -1;
    }
    
    FILE* fp = fopen(prompt, "r");
    if (fp == NULL) {
        perror("Error opening file for reading\n");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    while (count < maxUsers && fscanf(fp, "%s\t\t%d\n", scores[count].username, &scores[count].score) == 2) {
        count++;    
    }

    fclose(fp);
    return count;
}

int compareDesc(const void* a, const void* b) {
    const USER* scoreA = (const USER*)a;
    const USER* scoreB = (const USER*)b;

    if (scoreA->score > scoreB->score) return -1;
    if (scoreA->score < scoreB->score) return 1;
    return 0;
}

int compareAsc(const void* a, const void* b) {
    const USER* scoreA = (const USER*)a;
    const USER* scoreB = (const USER*)b;

    if (scoreA->score < scoreB->score) return -1;
    if (scoreA->score > scoreB->score) return 1;
    return 0;
}

static int partition(USER* users, int low, int high, int (*compare)(const void*, const void*)) {
    USER pivot = users[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (compare(&users[j], &pivot) < 0) {
            i++;
            USER temp = users[i];
            users[i] = users[j];
            users[j] = temp;
        }
    }

    USER temp = users[i + 1];
    users[i + 1] = users[high];
    users[high] = temp;

    return i + 1;
}

void quickSort(USER* users, int low, int high, int (*compare)(const void*, const void*)) {
    if (low < high) {
        int pi = partition(users, low, high, compare);
        quickSort(users, low, pi - 1, compare);
        quickSort(users, pi + 1, high, compare);
    }
}

int compareUsernames(const void* a, const void* b) {
    return strcmp(((USER*)a)->username, ((USER*)b)->username);
}

void deleteHighscores(const char* prompt) {
    if (prompt == NULL) {
        fprintf(stderr, "Invalid file name for deleting highscores\n");
        return;
    }
    FILE* file = fopen(prompt, "w");
    if (file) {
        fclose(file);
    }
    else {
        perror("Error opening file");
    }
}

char doubleCheck() {
    char check;
    printf("Do you really want to delete ALL saved usernames\nand highscores (y/n) ?\n>>> ");
    scanf(" %c", &check);       // Reads one char
    while (getchar() != '\n');  // Removes \n
    return check;
}

void displayRules(const char *prompt) {
    if (prompt == NULL) {
        fprintf(stderr, "Invalid file name for displaying rules\n");
        return;
    }
    FILE* fp = NULL;
    fp = fopen(prompt, "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char r[1000] = { '\0' };

    while (fgets(r, 1000, fp)) {
        printf("%s", r);
    }
    fclose(fp);

    int len = sizeOfFile(prompt);
    printf("Total size of rules.txt = %d bytes\n", len);

    printf("\nPress ENTER to return to previous menu...\n");
    getchar();
    getchar();

}

/*18. Koristiti funkcije fseek(), ftell(), rewind()*/

int sizeOfFile(const char* prompt) {
    if (prompt == NULL) {
        fprintf(stderr, "Invalid file name for size calculation\n");
        return -1;
    }
    
    FILE* fp = NULL;
    int len = 0;

    fp = fopen(prompt, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open file\n");
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0, SEEK_END);
    len = ftell(fp);
    fclose(fp);
    fp = NULL;

    return len;
}