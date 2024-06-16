#include "menu.h"
#include <time.h>

int main(void) {
	srand((unsigned)time(NULL));
	setConsoleSize(51, 30);
	displayMainMenu();
	return 0;
}