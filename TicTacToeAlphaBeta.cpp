#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

const char PLAYER = 'X';
const char COMPUTER = 'O';
const char EMPTY = ' ';
const int MAX_DEPTH = 6;

// Global variables for tracking branching factor and depth
int branchingFactor = 0;
int maxDepthReached = 0;

// Function prototypes
void printBoard(const vector<vector<char>>& board);
bool isMovesLeft(const vector<vector<char>>& board);
int evaluate(const vector<vector<char>>& board, int N);
int minimax(vector<vector<char>>& board, int depth, bool isMax, int N, int alpha, int beta);
pair<int, int> findBestMove(vector<vector<char>>& board, int N);
pair<int, int> getRandomMove(const vector<vector<char>>& board, int N);

int main() {
    srand(time(0));  // Seed for random number generation

    int N;
    cout << "Enter the size of the Tic-Tac-Toe board (N x N): ";
    cin >> N;

    vector<vector<char>> board(N, vector<char>(N, EMPTY));

    int turn = 0;
    while (true) {
        printBoard(board);

        if (turn % 2 == 0) {  // Player's turn
            int row, col;
            cout << "Enter your move (row and column): ";
            cin >> row >> col;
            if (row >= 0 && row < N && col >= 0 && col < N && board[row][col] == EMPTY) {
                board[row][col] = PLAYER;
                turn++;
            } else {
                cout << "Invalid move! Try again." << endl;
            }
        } else {  // Computer's turn
            cout << "Computer is making a move..." << endl;

            pair<int, int> bestMove;

                branchingFactor = 0;
                maxDepthReached = 0;
                bestMove = findBestMove(board, N);
                cout << "Branching Factor: " << branchingFactor << endl;
                cout << "Max Depth Reached: " << maxDepthReached << endl;


            board[bestMove.first][bestMove.second] = COMPUTER;
            turn++;
        }

        int score = evaluate(board, N);
        if (score == 10) {
            printBoard(board);
            cout << "Computer wins!" << endl;
            break;
        } else if (score == -10) {
            printBoard(board);
            cout << "You win!" << endl;
            break;
        } else if (!isMovesLeft(board)) {
            printBoard(board);
            cout << "It's a tie!" << endl;
            break;
        }
    }

    return 0;
}

// Function to print the board
void printBoard(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            cout << (cell == EMPTY ? '.' : cell) << " ";
        }
        cout << endl;
    }
}

// Function to check if there are moves left
bool isMovesLeft(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == EMPTY) {
                return true;
            }
        }
    }
    return false;
}

// Function to evaluate the board and return score
int evaluate(const vector<vector<char>>& board, int N) {
    // Check rows
    for (int row = 0; row < N; ++row) {
        if (board[row][0] != EMPTY) {
            bool row_win = true;
            for (int col = 1; col < N; ++col) {
                if (board[row][col] != board[row][0]) {
                    row_win = false;
                    break;
                }
            }
            if (row_win) return (board[row][0] == COMPUTER) ? 10 : -10;
        }
    }
    // Check columns
    for (int col = 0; col < N; ++col) {
        if (board[0][col] != EMPTY) {
            bool col_win = true;
            for (int row = 1; row < N; ++row) {
                if (board[row][col] != board[0][col]) {
                    col_win = false;
                    break;
                }
            }
            if (col_win) return (board[0][col] == COMPUTER) ? 10 : -10;
        }
    }
    // Check diagonals
    bool diag1 = true, diag2 = true;
    for (int i = 1; i < N; ++i) {
        if (board[i][i] != board[0][0] || board[0][0] == EMPTY) diag1 = false;
        if (board[i][N - i - 1] != board[0][N - 1] || board[0][N - 1] == EMPTY) diag2 = false;
    }
    if (diag1) return (board[0][0] == COMPUTER) ? 10 : -10;
    if (diag2) return (board[0][N - 1] == COMPUTER) ? 10 : -10;

    return 0;  // No winner
}

// Minimax function with alpha-beta pruning
int minimax(vector<vector<char>>& board, int depth, bool isMax, int N, int alpha, int beta) {
    maxDepthReached = max(maxDepthReached, depth);
    int score = evaluate(board, N);
    if (score == 10 || score == -10) return score;
    if (!isMovesLeft(board)) return 0;

    if(depth >= MAX_DEPTH ) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i][j] == EMPTY) {
                    branchingFactor++;  // Increment branching factor
                    board[i][j] = COMPUTER;
                    int val = minimax(board, depth + 1, !isMax, N, alpha, beta);
                    best = max(best, val);
                    alpha = max(alpha, best);
                    board[i][j] = EMPTY;
                    if (beta <= alpha) break;
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i][j] == EMPTY) {
                    branchingFactor++;  // Increment branching factor
                    board[i][j] = PLAYER;
                    int val = minimax(board, depth + 1, !isMax, N, alpha, beta);
                    best = min(best, val);
                    beta = min(beta, best);
                    board[i][j] = EMPTY;
                    if (beta <= alpha) break;
                }
            }
        }
        return best;
    }
}

// Function to find the best move for the computer
pair<int, int> findBestMove(vector<vector<char>>& board, int N) {
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] == EMPTY) {
                board[i][j] = COMPUTER;
                int moveVal = minimax(board, 0, false, N, -1000, 1000);
                board[i][j] = EMPTY;
                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

// Function to get a random move for the computer's first turn
pair<int, int> getRandomMove(const vector<vector<char>>& board, int N) {
    vector<pair<int, int>> emptyCells;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] == EMPTY) {
                emptyCells.push_back({i, j});
            }
        }
    }
    return emptyCells[rand() % emptyCells.size()];
}



