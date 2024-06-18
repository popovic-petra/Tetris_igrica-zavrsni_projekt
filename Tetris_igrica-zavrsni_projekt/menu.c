#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include "menu.h"
#include "score.h"
#include "tetris.h"

/*4. Imenovanje identifikatora (varijabli, konstanti, polja, funkcija, pokazivača…)*/
/*5. Primjena ključne riječi static za globalne i lokalne varijable*/

static void printStars(int count) {
    for (int i = 0; i < count; i++) {
        printf("*");
    }
    printf("\n");
}

static void mainMenu() {
    printStars(51);
    printf("*                TETRIS Version 1.0               *\n");
    printStars(51);
    printf("\n\tCreated By: P. Popovic, SR-1.god");
    printf("\n\n");

    printf("\n\t\t0. Start new game\n");
    printf("\n\t\t1. Tetris rules\n");
    printf("\n\t\t2. View highscores\n");
    printf("\n\t\t3. Exit\n");

    printf("\n\n");
    printStars(51);
}

static void highscoreMenu() {
    printStars(51);
    printf("*                TETRIS Version 1.0               *\n");
    printStars(51);
    printf("\n\tCreated By: P. Popovic, SR-1.god");
    printf("\n\n");

    printf("\n\t0. View highscores\n");
    printf("\n\t1. Sort highscores in ascending order\n");
    printf("\n\t2. Sort highscores in descending order\n");
    printf("\n\t3. Search highscores\n");
    printf("\n\t4. Delete all highscores\n");
    printf("\n\t5. Back to main menu\n");

    printf("\n\n");
    printStars(51);
}

/*1. Odabir konkretnih primitivnih tipova podataka za rad s cjelobrojnim i realnim konstantama*/
/*9. Izbornik/podizbornici*/

void displayMainMenu() {
    
    int showMainMenu = 1;
    
    while (showMainMenu) {
        system("cls");
        mainMenu();

        int choice = getMainMenuOption(EXIT);

        switch (choice) {
        case START:
            system("cls");
            tetrisRun(BOARD_WIDTH, BOARD_HEIGHT, 0);
            break;
        case RULES:
            system("cls");
            displayRules("rules.txt");
            break;
        case HIGHSCORE:
            system("cls");
            displayHighscoreMenu();
            break;
        case EXIT:
            showMainMenu = 0;
            break;
        }
    }
}

void displayHighscoreMenu() {
    
    int showHighscoreMenu = 1;

    while (showHighscoreMenu) {
        system("cls");
        highscoreMenu();
        int choice = getHighscoreMenuOption(BACK);

        USER users[MAX_PLAYERS] = { '\0' };
        int count = loadScore(users, MAX_PLAYERS, "scores.txt");

        char check;

        switch (choice) {
        case VIEW:
            system("cls");
            printStars(51);
            printf("*                   HIGH SCORES                   *\n");
            printStars(51);
            printf("\tUSERNAME\t\t\SCORE\n\n");
            
            for (int i = 0; i < count; i++) {
               printf("\t%-16s\t%d\n", users[i].username, users[i].score);
            }
            printf("\nPress ENTER to return to previous menu...\n");
            getchar();
            getchar();
            break;

        case ASCENDING:
            
            system("cls");
            printStars(51);
            printf("*                 SORTED ASCENDING                *\n");
            printStars(51);
            
            /*24. Pokazivače na funkcije je najlakše koristiti upotrebom funkcije qsort() ili bsearch()*/
            
            //qsort(users, count, sizeof(USER), compareAsc);
            quickSort(users, 0, count - 1, compareAsc);

            printf("\tUSERNAME\t\t\SCORE\n\n");
            for (int i = 0; i < count; i++) {
                printf("\t%-16s\t%d\n", users[i].username, users[i].score);
            }
            printf("\nPress ENTER to return to previous menu...\n");
            getchar();
            getchar();
            break;

        case DESCENDING:
            
            system("cls");
            printStars(51);
            printf("*                 SORTED DESCENDING               *\n");
            printStars(51);
            //qsort(users, count, sizeof(USER), compareDesc);
            quickSort(users, 0, count - 1, compareDesc);
            printf("\tUSERNAME\t\t\SCORE\n\n");
            for (int i = 0; i < count; i++) {
                printf("\t%-16s\t%d\n", users[i].username, users[i].score);
            }
            printf("\nPress ENTER to return to previous menu...\n");
            getchar();
            getchar();
            break;

        case SEARCH:
            system("cls");

            /*Sortiranje niza korisnika pomoću qsort je neophodno za ispravno funkcioniranje bsearch.*/

            // users - niz korisnika koji treba sortirati
            // count - broj korisnika u nizu
            // sizeof(USER) - velicina pojedinog elementa u nizu
            qsort(users, count, sizeof(USER), compareUsernames);

            char searchName[MAX_USERNAME_LENGTH + 1];
            printf("Enter username to search\n>>> ");
            getchar();
            fgets(searchName, MAX_USERNAME_LENGTH, stdin);
            removeNewline(searchName);

            USER key;       // kljuc za pretragu
            strncpy(key.username, searchName, MAX_USERNAME_LENGTH);

            /*22. Pretraživanje – preporuka koristiti ugrađenu bsearch() funkciju*/

            /*bsearch zahtijeva sortirani niz jer koristi binarno pretraživanje, 
            što omogućuje brzu pretragu korisničkog imena.*/

            // &key - pokazivac na kljuc koji se trazi
            // users - niz korisnika unutar kojeg se trazi
            // count - broj korisnika u nizu
            // bsearch vraca pokazivac na pronadjenog korisnika ili NULL ako nije pronadjen 
            USER* found = bsearch(&key, users, count, sizeof(USER), compareUsernames);
            
            if (found) {
                system("cls");
                printStars(51);
                printf("*                 SEARCH RESULT                   *\n");
                printStars(51);
                printf("Found user: %s with score: %d\n", found->username, found->score);
                printf("\nPress ENTER to return to previous menu...\n");
                getchar();
            }
            else {
                printStars(51);
                printf("\nUser %s not found.\n", searchName);
                printStars(51);
                printf("\nPress ENTER to return to previous menu...\n");
                getchar();
            }

            break;
        case DEL:
            system("cls");
            check = doubleCheck();
            getchar();
            
            if (check == 'y' || check == 'Y') {
                deleteHighscores("scores.txt");
                printf("Scores were successfully deleted.\n");
            }
            else if (check == 'n' || check == 'N') {
                printf("Score clearing was successfully canceled.\n");
            }
            else {
                printf("Invalid input. Score clearing canceled.\n");
            }
            printf("\nPress ENTER to return to previous menu...\n");
            getchar();              
            break;
        case BACK:
            showHighscoreMenu = 0;
            break;
        }
    }
}

int getMenuChoice(int maxOption) {
    int choice;
    do {
        printf("Enter your choice\n>>> ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter an integer.\n");
            while (getchar() != '\n');
        }
        if (choice < 0 || choice > maxOption) {
            printf("Choice out of range. Try again.\n");
        }
    } while (choice < 0 || choice > maxOption);
    return choice;
}

// poziva getMenuChoice koja prihvaća korisnički unos i vraća cijeli broj (int) koji 
// predstavlja odabranu opciju.
// taj cijeli broj se zatim pretvara u MENU_MAIN_OPTION tip pomoću type castinga
MENU_MAIN_OPTION getMainMenuOption() {
    return (MENU_MAIN_OPTION)getMenuChoice(EXIT);
}

// poziva getMenuChoice koja prihvaća korisnički unos i vraća cijeli broj (int) koji 
// predstavlja odabranu opciju.
// taj cijeli broj se zatim pretvara u MENU_HIGHSCORE_OPTION tip pomoću type castinga
MENU_HIGHSCORE_OPTION getHighscoreMenuOption() {
    return (MENU_HIGHSCORE_OPTION)getMenuChoice(BACK);
}

void setConsoleSize(int width, int height) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Postavljanje veličine buffer-a konzole
    COORD bufferSize = { width, height };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    // Postavljanje veličine prozora konzole
    SMALL_RECT windowSize = { 0, 0, width - 1, height - 1 };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}
