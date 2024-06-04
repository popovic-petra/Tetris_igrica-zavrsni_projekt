#pragma once

typedef enum {
	START,
	RULES,
	HIGHSCORE,
	EXIT,
	RETURN
}MENU_OPTION;

void menuDisplay();
MENU_OPTION getMenuChoice();
void game();
void menuReturn(void);