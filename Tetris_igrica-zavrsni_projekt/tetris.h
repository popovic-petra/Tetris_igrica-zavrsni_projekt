#pragma once

/*8. Ako su funkcije jednostavne koristiti makro funkcije ili inline funkcije*/

#define TETRIS_PIECES (sizeof(blocks)/sizeof(TETROMINO))
#define TETRIS_LEVELS (sizeof(levels)/sizeof(LEVEL))
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

/*2. Odabir konkretnih složenih tipova podataka za rad sa specifi?nim objektima*/
/*3. Primjena typedef sa strukturama i unijama, po potrebi s enum tipovima podataka tamo gdje treba*/

typedef struct tetrisBlock {
	char data[5][5];
	int width;
	int height;
}TETROMINO;

typedef struct tetrisLevel {
	int score;
	unsigned long nsec;
}LEVEL;

typedef struct tetrisGame {
	char** board;		// game board
	int width;			// game width
	int height;			// game hight
	int level;			// current level
	int score;			// current score
	int gameover;		// game over flag
	int paused;
	int exitRequested;
	TETROMINO current;	// current falling block
	int blockX;			// current block's x and y position
	int blockY;
}TETRIS;

/*7. Primjena extern klju?ne rije?i za globalne varijable*/

extern TETROMINO blocks[];
extern LEVEL levels[];

#include "score.h"

void tetrisInitialization(TETRIS* tetris, const int boardWidth, const int boardHeight);
void tetrisPrint(TETRIS* tetris);
int tetrisHittest(TETRIS* tetris);
void tetrisNewBlock(TETRIS* tetris);
void tetrisPrintBlock(TETRIS* tetris);
void tetrisRotate(TETRIS* tetris);
void tetrisGravity(TETRIS* tetris);
void tetrisFall(TETRIS* tetris, int l);
void tetrisCheckLines(TETRIS* tetris);
int tetrisLevel(TETRIS* tetris);
void tetrisFree(TETRIS* tetris);
void tetrisRun(const int boardWidth, const int boardHeight, int hs);