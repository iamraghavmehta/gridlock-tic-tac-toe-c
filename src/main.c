#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"

static void clearInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main(void) {
    char board[BOARD_SIZE][BOARD_SIZE];
    Scoreboard score = {0, 0, 0, 0};
    char playAgain = 'y';

    displayInstructions();

    while (playAgain == 'y' || playAgain == 'Y') {
        initializeBoard(board);
        char currentPlayer = 'X';
        char winner = ' ';

        printf("\n>>> STARTING ROUND #%d <<<\n", score.totalRounds + 1);

        while (winner == ' ' && !isBoardFull(board)) {
            displayBoard(board);
            printf("Player %c's turn. Enter cell coordinate (1-9): ", currentPlayer);

            int cell = 0;
            if (scanf("%d", &cell) != 1) {
                printf("[ERROR] Numerical input required. Choose 1 through 9.\n");
                clearInput();
                continue;
            }
            clearInput();

            if (!isValidMove(board, cell)) {
                printf("[INVALID MOVE] Cell %d is either occupied or out of bounds. Try again.\n", cell);
                continue;
            }

            makeMove(board, cell, currentPlayer);
            winner = checkWinner(board);

            if (winner == ' ') {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }

        displayBoard(board);

        if (winner == 'X' || winner == 'O') {
            printf("*******************************************************\n");
            printf("            CONGRATULATIONS! PLAYER %c WINS!           \n", winner);
            printf("*******************************************************\n");
            updateScoreboard(&score, winner);
        } else {
            printf("-------------------------------------------------------\n");
            printf("          MATCH CONCLUDED IN A STALEMATE DRAW          \n");
            printf("-------------------------------------------------------\n");
            updateScoreboard(&score, 'D');
        }

        displayScoreboard(&score);

        printf("Would you like to play another match? (y/n): ");
        if (scanf(" %c", &playAgain) != 1) {
            playAgain = 'n';
        }
        clearInput();
    }

    printf("\nThank you for playing GridLock Tic-Tac-Toe. Final statistics recorded.\n");
    displayScoreboard(&score);

    return 0;
}
