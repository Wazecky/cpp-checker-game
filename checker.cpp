#include <iostream>
#include <cmath>

const int SIZE = 8;

// Function to display the board
void displayBoard(char board[SIZE][SIZE]) {
    std::cout << "   ";
    for (int i = 0; i < SIZE; ++i) {
        std::cout << " " << i << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < SIZE; ++i) {
        std::cout << i << " [";
        for (int j = 0; j < SIZE; ++j) {
            std::cout << board[i][j] << "][";
        }
        std::cout << std::endl;
    }
}

// Function to initialize the checkerboard
void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if ((i + j) % 2 == 0) {
                if (i < 3) {
                    board[i][j] = 'X'; // Player X pieces
                } else if (i > 4) {
                    board[i][j] = 'O'; // Player O pieces
                } else {
                    board[i][j] = ' '; // Empty squares
                }
            } else {
                board[i][j] = ' '; // Empty squares
            }
        }
    }
}

// Function to check if a move is valid
bool isValidMove(char board[SIZE][SIZE], int startRow, int startCol, int endRow, int endCol, char currentPlayer) {
    // Check if the move is within the bounds of the board
    if (endRow < 0 || endRow >= SIZE || endCol < 0 || endCol >= SIZE) {
        return false;
    }

    // Check if the destination square is empty
    if (board[endRow][endCol] != ' ') {
        return false;
    }

    // Implement your logic for checking valid moves and captures
    if (currentPlayer == 'X') {
        if (endRow == startRow + 1 && (endCol == startCol - 1 || endCol == startCol + 1)) {
            return true; // Valid move for Player X
        } else if (endRow == startRow + 2 && std::abs(endCol - startCol) == 2 &&
                   board[startRow + 1][(startCol + endCol) / 2] == 'O') {
            return true; // Valid capture for Player X
        }
    } else if (currentPlayer == 'O') {
        if (endRow == startRow - 1 && (endCol == startCol - 1 || endCol == startCol + 1)) {
            return true; // Valid move for Player O
        } else if (endRow == startRow - 2 && std::abs(endCol - startCol) == 2 &&
                   board[startRow - 1][(startCol + endCol) / 2] == 'X') {
            return true; // Valid capture for Player O
        }
    }

    return false;
}

// Function to perform a move on the checkerboard
void performMove(char board[SIZE][SIZE], int startRow, int startCol, int endRow, int endCol) {
    // Perform the move
    board[endRow][endCol] = board[startRow][startCol];
    board[startRow][startCol] = ' ';

    // If it's a capture, remove the captured piece
    if (std::abs(endRow - startRow) == 2) {
        board[(startRow + endRow) / 2][(startCol + endCol) / 2] = ' ';
    }
}

// Function to check if a player has won
bool isGameOver(char board[SIZE][SIZE], char currentPlayer) {
    // Implement your logic for determining if the game is over
    // For simplicity, this code checks if the opponent has no pieces remaining
    char opponent = (currentPlayer == 'X') ? 'O' : 'X';

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == opponent) {
                return false; // Opponent still has pieces
            }
        }
    }

    return true; // Opponent has no pieces, current player wins
}

int main() {
    char board[SIZE][SIZE];

    // Display introductory messages and instructions
    std::cout << "Welcome to Text-Based Checkers!" << std::endl;
    std::cout << "Player X, you are represented by 'X'. Player O, you are represented by 'O'." << std::endl;
    std::cout << "To make a move, enter the starting row, starting column, ending row, and ending column." << std::endl;
    std::cout << "The board is represented as follows:" << std::endl;
    std::cout << "X - Player X piece | O - Player O piece |   - Empty square" << std::endl << std::endl;

    // Initialize the checkerboard
    initializeBoard(board);

    // Display the initial board
    displayBoard(board);

    char currentPlayer = 'X';

    // Game loop
    while (true) {
        // Get input from the current player
        int startRow, startCol, endRow, endCol;
        std::cout << "Player " << currentPlayer << ", enter your move (startRow startCol endRow endCol): ";
        std::cin >> startRow >> startCol >> endRow >> endCol;

        // Check if the move is valid
        if (isValidMove(board, startRow, startCol, endRow, endCol, currentPlayer)) {
            // Perform the move
            performMove(board, startRow, startCol, endRow, endCol);

            // Display the updated board
            displayBoard(board);

            // Check for game over conditions
            if (isGameOver(board, currentPlayer)) {
                std::cout << "Player " << currentPlayer << " wins!" << std::endl;
                break;
            }

            // Switch to the next player (X -> O or O -> X)
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        } else {
            std::cout << "Invalid move! Try again." << std::endl;
        }
    }

    return 0;
}
