#pragma once

typedef enum {
	START,
	RULES,
	HIGHSCORE,
	EXIT
}MENU_MAIN_OPTION;

typedef enum {
	VIEW,
	ASCENDING,
	DESCENDING,
	SEARCH,
	DEL,
	BACK
}MENU_HIGHSCORE_OPTION;

static void printStars(int count);

void mainMenu();
void displayMainMenu();
void displayHighscoreMenu();

int getMenuChoice(int maxOption);
MENU_MAIN_OPTION getMainMenuOption();
MENU_HIGHSCORE_OPTION getHighscoreMenuOption();

void displayRules();
int sizeOfFile(const char* prompt);
void setConsoleSize(int width, int height);

