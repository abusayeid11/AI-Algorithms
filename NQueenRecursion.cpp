#include <iostream>
#include <vector>

using namespace std;

int N;  // Size of the chessboard
vector<vector<char>> board;  // Chessboard represented as a 2D grid

// Function to print one solution
void printSolution() {
    cout << "One solution for " << N << "-Queens problem:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if a queen placement is safe
bool isSafe(int row, int col) {
    // Check the column
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 'Q') return false;
    }

    // Check the upper-left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') return false;
    }

    // Check the upper-right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++) {
        if (board[i][j] == 'Q') return false;
    }

    return true;
}

// Recursive function to solve the N-Queens problem row by row
bool solve(int row) {
    if (row == N) {  // All queens are placed successfully
        printSolution();
        return true;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row][col] = 'Q';  // Place the queen
            if (solve(row + 1)) {  // Try to place queens in the next row
                return true;  // Stop when a solution is found
            }
            board[row][col] = '.';  // Backtrack: remove the queen
        }
    }

    return false;  // No solution found in this configuration
}

int main() {
    cout << "Enter the number of queens: ";
    cin >> N;

    // Initialize the board with empty spaces (.)
    board = vector<vector<char>>(N, vector<char>(N, '.'));

    // Try to find one solution
    if (!solve(0)) {
        cout << "No solution found for " << N << "-Queens problem.\n";
    }

    return 0;
}


