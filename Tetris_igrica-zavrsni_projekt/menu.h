#pragma once

typedef enum {
	START,
	RULES,
	HIGHSCORE,
	EXIT
}MENU_MAIN_OPTION;

typedef enum {
	ASCENDING,
	DESCENDING,
	SEARCH,
	DEL,
	BACK
}MENU_HIGHSCORE_OPTION;

void mainMenu();
void displayMainMenu();
void displayHighscoreMenu();

int getMenuChoice(int maxOption);
MENU_MAIN_OPTION getMainMenuOption();
MENU_HIGHSCORE_OPTION getHighscoreMenuOption();

void displayRules();
int sizeOfFile(const char* prompt);
void setConsoleSize(int width, int height);

