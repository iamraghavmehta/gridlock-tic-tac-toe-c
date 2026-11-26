#ifndef GAME_H
#define GAME_H

#define BOARD_SIZE 3

typedef struct {
    int playerXWins;
    int playerOWins;
    int drawCount;
    int totalRounds;
} Scoreboard;

/* Board lifecycle */
void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]);
void displayBoard(const char board[BOARD_SIZE][BOARD_SIZE]);
void displayInstructions(void);

/* Moves and Validation */
int isValidMove(const char board[BOARD_SIZE][BOARD_SIZE], int cellNumber);
int makeMove(char board[BOARD_SIZE][BOARD_SIZE], int cellNumber, char player);

/* Win / Draw State Checks */
char checkWinner(const char board[BOARD_SIZE][BOARD_SIZE]);
int isBoardFull(const char board[BOARD_SIZE][BOARD_SIZE]);

/* Scoreboard */
void updateScoreboard(Scoreboard *score, char winner);
void displayScoreboard(const Scoreboard *score);

#endif /* GAME_H */
