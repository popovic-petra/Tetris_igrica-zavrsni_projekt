#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include "tetris.h"
#include "score.h"

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

/*11. Generalno upotreba struktura i funkcija*/
/*15. Koristiti funkcije malloc(), calloc(), realloc(), free()*/

// inicijalizacija igre postavljanjem, dimenzija ploce, trenutnog levela, stanja igre
void tetrisInitialization(TETRIS* tetris, const int boardWidth, const int boardHeight) {
    // provjeravamo validnost ulaznog parametra
    if (tetris == NULL || boardWidth <= 0 || boardHeight <= 0) {
        fprintf(stderr, "Invalid parameters for tetrisInitialization\n");
        return;
    }
    
    tetris->level = 1;
    tetris->score = 0;
    tetris->gameover = 0;
    tetris->paused = 0;
    tetris->width = boardWidth;
    tetris->height = boardHeight;

    // alokacija za stupce
    tetris->board = (char**)malloc(boardWidth * sizeof(char*));
    if (tetris->board == NULL) {
        fprintf(stderr, "Memory allocation failed for board columns\n");
        exit(EXIT_FAILURE);
    }

    // za svaki red alocira memoriju i inicijalizira prazno polje
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

/*16. Sigurno brisanje memorije koja je dinamički zauzeta, anuliranje memorijskog prostora, provjera pokazivača*/

// oslobađa memoriju koja je bila zauzeta za ploču igre.
void tetrisFree(TETRIS* tetris) {
    if (tetris == NULL) {
        fprintf(stderr, "Invalid parameter for tetrisFree\n");
        return;
    }
    
    for (int x = 0; x < tetris->width; x++) {
        free(tetris->board[x]);
    }
    free(tetris->board);
}

// ispisuje trenutno stanje igre na konzoli, uključujući ploču, trenutni level i rezultat
void tetrisPrint(TETRIS* tetris) {
    if (tetris == NULL) {
        fprintf(stderr, "Invalid parameter for tetrisPrint\n");
        return;
    }
    
    system("cls");
    printf("\n");
    if (tetris->paused) {
        printf("\t\t    *** [ PAUSE ] ***");
    }
    printf("\n\t\t");

    // ispisuje okvir ploce
    for (int x = 0; x < 2 * tetris->width + 4; x++) {
        printf("=");
    }
    printf("\n");

    // prikazuje plocu s trenutnim blokom koji pada
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
}

// provjerava sudar bloka s rubom ploce ili drugim blokom 
int tetrisHittest(TETRIS* tetris) {
    if (tetris == NULL) {
        fprintf(stderr, "Invalid parameter for tetrisHittest\n");
        return 1; // Assume hit if tetris is NULL
    }
    
    int absX, absY;
    TETROMINO block = tetris->current;
    for (int x = 0; x < block.width; x++) {
        for (int y = 0; y < block.height; y++) {
            absX = tetris->blockX + x;
            absY = tetris->blockY + y;
            if (!(absX >= 0 && absX < tetris->width)) {
                return 1;       // vraca 1 ako dolazi do sudara s plocom
            }
            if (block.data[y][x] != ' ') {
                if ((absY >= tetris->height) ||
                    (absX >= 0 && absX < tetris->width && absY >= 0 && tetris->board[absX][absY] != ' ')) {
                    return 1;   // vraca 1 ako dolazi do sudara s drugim blokom
                }
            }
        }
    }
    return 0;   // ako nema usdara vraca 0
}

// generira novi blok i postavlja ga na vrh ploce
void tetrisNewBlock(TETRIS* tetris) {
    if (tetris == NULL) {
        fprintf(stderr, "Invalid parameter for tetrisNewBlock\n");
        return;
    }

    // nasumicno se bira blok iz strukture blokova 
    tetris->current = blocks[rand() % TETRIS_PIECES];
    tetris->blockX = (tetris->width / 2) - (tetris->current.width / 2);
    tetris->blockY = 0;
    // provjera sudara nakon postavljanja bloka
    if (tetrisHittest(tetris)) {
        tetris->gameover = 1;
    }
}

// ispisuje trenutni blok na plocu
void tetrisPrintBlock(TETRIS* tetris) {
    if (tetris == NULL) {
        fprintf(stderr, "Invalid parameter for tetrisPrintBlock\n");
        return;
    }
    
    TETROMINO block = tetris->current;
    for (int x = 0; x < block.width; x++) {
        for (int y = 0; y < block.height; y++) {
            if (block.data[y][x] != ' ') {
                tetris->board[tetris->blockX + x][tetris->blockY + y] = block.data[y][x];
            }
        }
    }
}

// rotira trenutni blok u smjeru kazaljke na satu
void tetrisRotate(TETRIS* tetris) {
    if (tetris == NULL) {
        fprintf(stderr, "Invalid parameter for tetrisRotate\n");
        return;
    }
    
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

    // ako rotacija uzrokuje sudar, vraca se blok u pocetni polozaj
    if (tetrisHittest(tetris)) {
        tetris->current = original;
        tetris->blockX = x;
        tetris->blockY = y;
    }
}

// pomjera trenutni blok jedan za jedan red dolje 
void tetrisGravity(TETRIS* tetris) {
    if (tetris == NULL) {
        fprintf(stderr, "Invalid parameter for tetrisGravity\n");
        return;
    }
    
    // pomjera blok za jedan red dolje i provjerava sudar
    tetris->blockY++;
    if (tetrisHittest(tetris)) {        // ako dolazi do sudara, blok se vraca na prethodnu poziciju i postaje dio ploce
        tetris->blockY--;
        tetrisPrintBlock(tetris);
        tetrisNewBlock(tetris);
    }
}

// pomjera sve redove iznad linije l za jedan red dolje
// int l je linija koja se brise
void tetrisFall(TETRIS* tetris, int l) {
    if (tetris == NULL) {
        fprintf(stderr, "Invalid parameter for tetrisFall\n");
        return;
    }
    
    // pomjera sve redove iznad l za red dolje
    int x, y;
    for (y = l; y > 0; y--) {
        for (x = 0; x < tetris->width; x++) {
            tetris->board[x][y] = tetris->board[x][y - 1];
        }
    }
    // postavlja gornji red na prazno
    for (x = 0; x < tetris->width; x++) {
        tetris->board[x][0] = ' ';
    }
}

// provjerava i brise pune linije na ploci te azurira rezultat
void tetrisCheckLines(TETRIS* tetris) {  
    if (tetris == NULL) {
        fprintf(stderr, "Invalid parameter for tetrisCheckLines\n");
        return;
    }
    
    // provjerava svaku liniju od dna prema vrhu
    
    int x, y, full;
    int linesCleared = 0;
    for (y = tetris->height - 1; y >= 0; y--) {
        full = 1;
        for (x = 0; x < tetris->width && full; x++) {
            if (tetris->board[x][y] == ' ') {
                full = 0;
            }
        }
        // ako je linija puna, brise je i pomjera sve linije iznad prema dolje
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

// vraca trenutno vrijeme padanja blokova u nanosec, bazirano na levelu 
int tetrisLevel(TETRIS* tetris) {
    if (tetris == NULL) {
        fprintf(stderr, "Invalid parameter for tetrisLevel\n");
        return -1; // Return an invalid level
    }

    for (int i = 0; i < TETRIS_LEVELS; i++) {
        if (tetris->score >= levels[i].score) {
            tetris->level = i + 1;
        }
        else break;
    }
    return levels[tetris->level - 1].nsec;
}

// glavna funkcija koja pokrece igru
// Postavlja igru, upravlja korisničkim unosom, ažurira stanje igre, i prikazuje trenutnu situaciju na ploči sve dok igra ne završi.
void tetrisRun(const int boardWidth, const int boardHeight, int hs) {
    if (boardWidth <= 0 || boardHeight <= 0) {
        fprintf(stderr, "Invalid board dimensions for tetrisRun\n");
        return;
    }
    
    struct timespec tm = { 0, 0 };

    TETRIS tetris;
    USER* user = allocateUser();
    
    char cmd;
    int count = 0;

    tetrisInitialization(&tetris, boardWidth, boardHeight);

    enterUsername(user);
    user->score = 0;

    tm.tv_sec = 0;
    tm.tv_nsec = 50000000;

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

            if (cmd == 'p'||cmd == 'P') {
                tetris.paused = !tetris.paused;
                if (tetris.paused) {
                    tetrisPrint(&tetris);
                }
            }

            else if (!tetris.paused) {
                switch (cmd) {
                case 'a':
                case 'A':
                    tetris.blockX--;
                    if (tetrisHittest(&tetris))
                        tetris.blockX++;
                    break;
                case 'd':
                case 'D':
                    tetris.blockX++;
                    if (tetrisHittest(&tetris))
                        tetris.blockX--;
                    break;
                case 's':
                case 'S':
                    tetrisGravity(&tetris);
                    break;
                case ' ':
                    tetrisRotate(&tetris);
                    break;
                }
            }

            tm.tv_nsec = tetrisLevel(&tetris);

        }
    }

    

    user->score = tetris.score;

    printf("GAME OVER %s! Your score: %d\n", user->username, user->score);
    
    if (user->score > hs) {
        hs = user->score;
        printf("Congratulations %s! New high score!\n", user->username);
        saveScore(user, "scores.txt"); // Save username and highscore to file
    }
    else {
        printf("Better luck next time!\n");
    }

    tetrisFree(&tetris);
    freeUser(user);

    printf("\nPress ENTER to return to main menu...\n");
    getchar();
}
