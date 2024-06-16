#pragma once

typedef enum {
	START,
	MENAGE_USER,
	RULES,
	HIGHSCORE,
	EXIT
}MENU_MAIN_OPTION;

typedef enum {
	EXISTING,
	NEW,
	BACK_MAIN_MENU
}MENU_START_OPTION;

typedef enum {
	ALL,
	BACK_START
}MENU_EXISTING_OPTION;

typedef enum {
	ALL_USER,
	ADD,
	RENAME,
	DEL,
	DEL_ALL,
	BACK_MAIN
}MENU_USER_OPTION;

typedef enum {
	ASCENDING,
	DESCENDING,
	SEARCH,
	BACK_MENU
}MENU_HIGHSCORE_OPTION;

void mainMenu();

void displayMainMenu();
void displayStartGameMenu();
void displayExistingMenu();
void displayUserMenu();
void displayHighscoreMenu();

int getMenuChoice(int maxOption);
MENU_MAIN_OPTION getMainMenuOption();
MENU_START_OPTION getStartMenuOption();
MENU_EXISTING_OPTION getExistingMenuOption();
MENU_USER_OPTION getUserMenuOption();
MENU_HIGHSCORE_OPTION getHighscoreMenuOption();

void displayRules();
int sizeOfFile(const char* prompt);
void setConsoleSize(int width, int height);

