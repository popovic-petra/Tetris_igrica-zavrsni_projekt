#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include "tetris.h"
//#include "menu.h"
#include "user.h"

TETROMINO blocks[] = {
	{{"##",
	  "##"},
	2, 2},

	{{" $ ",
	  "$$$"},
	3, 2},

	{{"%% ",
	  " %%",},
	3, 2},

	{{" @@",
	  "@@ ",},
	3, 2},

	{{"&&&&"},
	4, 1},

	{{"00",
	  "0 ",
	  "0 "},
	2, 3},

	{{"ZZ",
	  " Z",
	  " Z"},
	2, 3},
};

LEVEL levels[] = {
	{0,
		800000000},
	{2500,
		716666667},
	{5000,
		633333333},
	{10000,
		550000000},
	{15000,
		466666667},
	{20000,
		383333333},
	{30000,
		300000000},
	{40000,
		216666667},
	{50000,
		133333333},
	{70000,
		100000000},
};

void tetrisInitialization(TETRIS* tetris, const int boardWidth, const int boardHeight) {
    tetris->level = 1;
    tetris->score = 0;
    tetris->gameover = 0;
    tetris->paused = 0;
    tetris->width = boardWidth;
    tetris->height = boardHeight;

    tetris->board = (char**)malloc(boardWidth * sizeof(char*));
    if (tetris->board == NULL) {
        fprintf(stderr, "Memory allocation failed for board columns\n");
        exit(EXIT_FAILURE);
    }

    for (int x = 0; x < boardWidth; x++) {
        tetris->board[x] = (char*)malloc(boardHeight * sizeof(char));
        if (tetris->board[x] == NULL) {
            fprintf(stderr, "Memory allocation failed for board row %d\n", x);
            for (int i = 0; i < x; i++) {
                free(tetris->board[i]);
            }
            free(tetris->board);
            exit(EXIT_FAILURE);
        }
        for (int y = 0; y < boardHeight; y++) {
            tetris->board[x][y] = ' ';
        }
    }
}

void tetrisFree(TETRIS* tetris) {
    for (int x = 0; x < tetris->width; x++) {
        free(tetris->board[x]);
    }
    free(tetris->board);
}

void tetrisPrint(TETRIS* tetris) {
    system("cls");
    printf("\n");
    if (tetris->paused) {
        printf("\t\t    *** [ PAUSE ] ***");
    }
    //printf("\n");
    printf("\n\t\t");
    for (int x = 0; x < 2 * tetris->width + 4; x++) {
        printf("=");
    }
    printf("\n");

    for (int y = 0; y < tetris->height; y++) {
        printf("\t\t<!");
        for (int x = 0; x < tetris->width; x++) {
            if (x >= tetris->blockX && y >= tetris->blockY &&
                x < (tetris->blockX + tetris->current.width) && y < (tetris->blockY + tetris->current.height) &&
                tetris->current.data[y - tetris->blockY][x - tetris->blockX] != ' ') {
                printf("%c ", tetris->current.data[y - tetris->blockY][x - tetris->blockX]);
            }
            else {
                printf("%c ", tetris->board[x][y]);
            }
        }
        printf("!>\n");
    }
    printf("\t\t");
    for (int x = 0; x < 2 * tetris->width + 4; x++) {
        printf("=");
    }
    printf("\n");
    printf("\t\tLEVEL: %d\n\t\tSCORE: %d\n", tetris->level, tetris->score);
    
    /*if (tetris->exitRequested) {
        printf("Are you sure you want to exit? (y/n)\n");
    }*/
}

int tetrisHittest(TETRIS* tetris) {
    int absX, absY;
    TETROMINO block = tetris->current;
    for (int x = 0; x < block.width; x++) {
        for (int y = 0; y < block.height; y++) {
            absX = tetris->blockX + x;
            absY = tetris->blockY + y;
            if (!(absX >= 0 && absX < tetris->width)) {
                return 1;
            }
            if (block.data[y][x] != ' ') {
                if ((absY >= tetris->height) ||
                    (absX >= 0 && absX < tetris->width && absY >= 0 && tetris->board[absX][absY] != ' ')) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void tetrisNewBlock(TETRIS* tetris) {
    tetris->current = blocks[rand() % TETRIS_PIECES];
    tetris->blockX = (tetris->width / 2) - (tetris->current.width / 2);
    tetris->blockY = 0;
    if (tetrisHittest(tetris)) {
        tetris->gameover = 1;
    }
}

void tetrisPrintBlock(TETRIS* tetris) {
    TETROMINO block = tetris->current;
    for (int x = 0; x < block.width; x++) {
        for (int y = 0; y < block.height; y++) {
            if (block.data[y][x] != ' ') {
                tetris->board[tetris->blockX + x][tetris->blockY + y] = block.data[y][x];
            }
        }
    }
}

void tetrisRotate(TETRIS* tetris) {
    int x, y;
    TETROMINO block = tetris->current;
    TETROMINO original = block;
    block.width = original.height;
    block.height = original.width;
    for (x = 0; x < original.width; x++) {
        for (y = 0; y < original.height; y++) {
            block.data[x][y] = original.data[original.height - y - 1][x];
        }
    }
    x = tetris->blockX;
    y = tetris->blockY;
    tetris->blockX -= (block.width - original.width) / 2;
    tetris->blockY -= (block.height - original.height) / 2;
    tetris->current = block;
    if (tetrisHittest(tetris)) {
        tetris->current = original;
        tetris->blockX = x;
        tetris->blockY = y;
    }
}

void tetrisGravity(TETRIS* tetris) {
    tetris->blockY++;
    if (tetrisHittest(tetris)) {
        tetris->blockY--;
        tetrisPrintBlock(tetris);
        tetrisNewBlock(tetris);
    }
}

void tetrisFall(TETRIS* tetris, int l) {
    int x, y;
    for (y = l; y > 0; y--) {
        for (x = 0; x < tetris->width; x++) {
            tetris->board[x][y] = tetris->board[x][y - 1];
        }
    }
    for (x = 0; x < tetris->width; x++) {
        tetris->board[x][0] = ' ';
    }
}

void tetrisCheckLines(TETRIS* tetris) {
    int x, y, full;
    int linesCleared = 0;
    for (y = tetris->height - 1; y >= 0; y--) {
        full = 1;
        for (x = 0; x < tetris->width && full; x++) {
            if (tetris->board[x][y] == ' ') {
                full = 0;
            }
        }
        if (full) {
            linesCleared++;
            tetrisFall(tetris, y);
            y++;
        }
    }
    int score = 0;
    switch (linesCleared) {
    case 1:
        score = 100 * tetris->level;
        break;
    case 2:
        score = 300 * tetris->level;
        break;
    case 3:
        score = 500 * tetris->level;
        break;
    case 4:
        score = 800 * tetris->level;
        break;
    }
    tetris->score += score;
}

int tetrisLevel(TETRIS* tetris) {
    for (int i = 0; i < TETRIS_LEVELS; i++) {
        if (tetris->score >= levels[i].score) {
            tetris->level = i + 1;
        }
        else break;
    }
    return levels[tetris->level - 1].nsec;
}

void tetrisRun(USER* user, const int boardWidth, const int boardHeight, int hs) {
    TETRIS tetris;
    char cmd;
    int count = 0;

    user->score = 0;

    tetrisInitialization(&tetris, boardWidth, boardHeight);
    tetrisNewBlock(&tetris);

    while (!tetris.gameover) {
        count++;
        if (count % 100 == 0) {
            Sleep(100);
        }
        if (count % 50 == 0) {
            tetrisPrint(&tetris);
        }
        if (!tetris.paused && count % 350 == 0) {
            tetrisGravity(&tetris);
            tetrisCheckLines(&tetris);
        }
        while (_kbhit()) {
            cmd = _getch();
            
            if (cmd == 'p') {
                tetris.paused = !tetris.paused;
                if (tetris.paused) {
                    tetrisPrint(&tetris);
                }
            }
            
            else if (!tetris.paused) {
                switch (cmd) {
                case 'a':
                    tetris.blockX--;
                    if (tetrisHittest(&tetris))
                        tetris.blockX++;
                    break;
                case 'd':
                    tetris.blockX++;
                    if (tetrisHittest(&tetris))
                        tetris.blockX--;
                    break;
                case 's':
                    tetrisGravity(&tetris);
                    break;
                case ' ':
                    tetrisRotate(&tetris);
                    break;
                }
            }
        }
    }

    user->score = tetris.score;
    printf("GAME OVER %s ! Your score: %d !\n", user->username, user->score);
    if (user->score > hs) {
        hs = user->score;
        printf("CONGRATULATIONS %s ! New high score !\n", user->username);
        //saveScore();
    }
    else {
        printf("Better luck next time !\n");
    }

    tetrisFree(&tetris);
}

void runTetrisForUser(USER_MANAGER* um, int userIndex) {
    tetrisRun(&um->players[userIndex], 10, 20, um->players[userIndex].score);
}
