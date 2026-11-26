#include <stdio.h>
#include "../include/game.h"

void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    char count = '1';
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            board[r][c] = count++;
        }
    }
}

void displayInstructions(void) {
    printf("\n=======================================================\n");
    printf("         GRIDLOCK - 3x3 TIC-TAC-TOE SYSTEM IN C         \n");
    printf("=======================================================\n");
    printf(" Rules:\n");
    printf(" - Two players alternate placing their marks ('X' and 'O').\n");
    printf(" - Enter grid cell numbers (1 to 9) corresponding to the\n");
    printf("   coordinate matrix shown below.\n");
    printf(" - First player to complete 3 marks in any row, column,\n");
    printf("   or diagonal wins the round.\n");
    printf(" - Attempting to select an occupied cell will be rejected.\n");
    printf("=======================================================\n\n");
}

void displayBoard(const char board[BOARD_SIZE][BOARD_SIZE]) {
    printf("\n");
    printf("         +---+---+---+\n");
    for (int r = 0; r < BOARD_SIZE; r++) {
        printf("         |");
        for (int c = 0; c < BOARD_SIZE; c++) {
            char cell = board[r][c];
            if (cell == 'X') {
                printf(" X |");
            } else if (cell == 'O') {
                printf(" O |");
            } else {
                printf(" %c |", cell);
            }
        }
        printf("\n");
        printf("         +---+---+---+\n");
    }
    printf("\n");
}

int isValidMove(const char board[BOARD_SIZE][BOARD_SIZE], int cellNumber) {
    if (cellNumber < 1 || cellNumber > 9) {
        return 0; // Out of bounds
    }
    int row = (cellNumber - 1) / BOARD_SIZE;
    int col = (cellNumber - 1) % BOARD_SIZE;
    return (board[row][col] != 'X' && board[row][col] != 'O');
}

int makeMove(char board[BOARD_SIZE][BOARD_SIZE], int cellNumber, char player) {
    if (!isValidMove(board, cellNumber)) {
        return 0;
    }
    int row = (cellNumber - 1) / BOARD_SIZE;
    int col = (cellNumber - 1) % BOARD_SIZE;
    board[row][col] = player;
    return 1;
}

char checkWinner(const char board[BOARD_SIZE][BOARD_SIZE]) {
    // Check Rows
    for (int r = 0; r < BOARD_SIZE; r++) {
        if (board[r][0] == board[r][1] && board[r][1] == board[r][2]) {
            return board[r][0];
        }
    }

    // Check Columns
    for (int c = 0; c < BOARD_SIZE; c++) {
        if (board[0][c] == board[1][c] && board[1][c] == board[2][c]) {
            return board[0][c];
        }
    }

    // Check Main Diagonal
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    }

    // Check Anti-Diagonal
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }

    return ' '; // No winner yet
}

int isBoardFull(const char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            if (board[r][c] != 'X' && board[r][c] != 'O') {
                return 0; // Found unplayed cell
            }
        }
    }
    return 1; // All cells occupied
}

void updateScoreboard(Scoreboard *score, char winner) {
    score->totalRounds++;
    if (winner == 'X') {
        score->playerXWins++;
    } else if (winner == 'O') {
        score->playerOWins++;
    } else {
        score->drawCount++;
    }
}

void displayScoreboard(const Scoreboard *score) {
    printf("\n=======================================================\n");
    printf("                  SESSION SCOREBOARD                   \n");
    printf("=======================================================\n");
    printf(" Total Matches Played : %d\n", score->totalRounds);
    printf(" Player X Victories   : %d\n", score->playerXWins);
    printf(" Player O Victories   : %d\n", score->playerOWins);
    printf(" Stalemate Draws      : %d\n", score->drawCount);
    printf("=======================================================\n\n");
}
