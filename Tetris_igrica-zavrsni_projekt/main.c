#include "menu.h"
#include "score.h"
#include <time.h>

int main(void) {
	srand((unsigned)time(NULL));
	createAndRenameFiles("scores.txt");
	setConsoleSize(51, 30);
	displayMainMenu();
	//cleanupFiles("scores.txt");
	return 0;
}