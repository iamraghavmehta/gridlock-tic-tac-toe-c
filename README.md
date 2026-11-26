# GridLock - Tic-Tac-Toe Game Engine

A robust, turn-based two-player Tic-Tac-Toe console game implemented in pure C (C99) using two-dimensional arrays, matrix win evaluation algorithms, move verification, and round scorekeeping.

## Features & Implementation Concepts

- **2D Coordinate Matrix (char board[3][3])**: Dynamic grid representation mapping numerical user inputs (1-9) to row and column indices.
- **Matrix Win Detection**: Algorithmic evaluation across horizontal rows, vertical columns, and primary/anti-diagonals.
- **Move Validation**: Rejects out-of-range inputs and blocks cell overwrite attempts.
- **Scoreboard Persistence**: Multi-round match tracker recording Player X victories, Player O victories, and stalemate draws.
- **Modular C Design**: Separates game engine logic (src/game.c) from execution loop (src/main.c) and interface contracts (include/game.h).

## Compilation and Execution

`ash
gcc -Wall -Wextra -std=c99 -Iinclude src/game.c src/main.c -o gridlock
./gridlock
`

## Interactive Web Game Mirror

A live interactive web version is deployed at:
https://iamraghavmehta.github.io/gridlock-tic-tac-toe-c/
