#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

const int N = 3;  // Board size (3x3 for 8-puzzle)
const vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};  // Possible moves: up, down, left, right

// Function to calculate the Manhattan distance for a board
int calculateManhattan(const vector<vector<int>>& board, const vector<vector<int>>& goalBoard) {
    int dist = 0;

    // Create a map for target positions in the goalBoard
    unordered_map<int, pair<int, int>> targetPositions;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            targetPositions[goalBoard[i][j]] = {i, j};
        }
    }

    // Calculate Manhattan distance for each tile in the board
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int tile = board[i][j];
            if (tile != 0) {  // Skip the empty tile
                int targetX = targetPositions[tile].first;
                int targetY = targetPositions[tile].second;
                dist += abs(i - targetX) + abs(j - targetY);
            }
        }
    }

    return dist;
}


// Check if two boards are equal (goal reached)
bool isGoal(const vector<vector<int>>& board, const vector<vector<int>>& goalBoard) {
    return board == goalBoard;
}

// Print the board configuration
void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }
    cout << "----" << endl;
}

// A* algorithm to solve the 8-puzzle with path printing
void solve8Puzzle(const vector<vector<int>>& startBoard, const vector<vector<int>>& goalBoard, int startX, int startY) {
    priority_queue<pair<int, pair<vector<vector<int>>, pair<int, int>>>,
                   vector<pair<int, pair<vector<vector<int>>, pair<int, int>>>>,
                   greater<>> openList;

    set<vector<vector<int>>> closedList;
    map<vector<vector<int>>, vector<vector<int>>> parentMap; // For tracking the path

    int startH = calculateManhattan(startBoard, goalBoard);
    openList.push({startH, {startBoard, {startX, startY}}});
    parentMap[startBoard] = {};  // No parent for the start node

    while (!openList.empty()) {
        auto [f, state] = openList.top();
        auto [currentBoard, pos] = state;
        openList.pop();

        // If the current board is the goal, print the solution
        if (isGoal(currentBoard, goalBoard)) {
            cout << "Solution found in steps:" << endl;

            // Trace and print the path from start to goal
            vector<vector<vector<int>>> path;
            while (!currentBoard.empty()) {
                path.push_back(currentBoard);
                currentBoard = parentMap[currentBoard];
            }
            reverse(path.begin(), path.end());
            for (const auto& step : path) {
                printBoard(step);
            }
            return;
        }

        closedList.insert(currentBoard);

        for (const auto& dir : directions) {
            int newX = pos.first + dir[0];
            int newY = pos.second + dir[1];

            if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
                vector<vector<int>> newBoard = currentBoard;
                swap(newBoard[pos.first][pos.second], newBoard[newX][newY]);

                if (closedList.find(newBoard) == closedList.end()) {
                    int g = f - calculateManhattan(currentBoard, goalBoard) + 1;  // g = cost so far
                    int h = calculateManhattan(newBoard, goalBoard);
                    openList.push({g + h, {newBoard, {newX, newY}}});
                    parentMap[newBoard] = currentBoard;  // Record the parent
                }
            }
        }
    }

    cout << "No solution exists!" << endl;
}

int main() {
    vector<vector<int>> startBoard(N, vector<int>(N));
    vector<vector<int>> goalBoard(N, vector<int>(N));
    int startX, startY;

    cout << "Enter the initial board (use 0 for empty space):" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> startBoard[i][j];
            if (startBoard[i][j] == 0) {
                startX = i;
                startY = j;
            }
        }
    }

    cout << "Enter the goal board:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> goalBoard[i][j];
        }
    }

    solve8Puzzle(startBoard, goalBoard, startX, startY);

    return 0;
}
