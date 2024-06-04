#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

void enterUsername(PLAYER* p) {
    printf("Enter your username:\n\t\t>>> ");
    if (scanf("%99s", p->username) != 1) {
        printf("Failed to read username\n");
        exit(EXIT_FAILURE);
    }
}


void rules() {
    
    FILE* fp = NULL;
    fp = fopen("rules.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    /*int d = sizeOfFile("rules.txt");
    printf("%d", d);*/

    char r[1000] = { '\0' };
    
    while (fgets(r, 1000, fp)) {
        printf("%s", r);
    }
    fclose(fp);
}

int sizeOfFile(const char* prompt) {
    FILE* f = fopen(prompt, "r");

    if (f == NULL) {
        fprintf(stderr, "Failed to open file\n");
        exit(EXIT_FAILURE);
    }

    fseek(f, 0, SEEK_END);
    //printf("%ld", ftell(f));

    int d = ftell(f);

    fclose(f);
    f = NULL;

    return d;
}