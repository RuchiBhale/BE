#include <iostream>
#include <vector>

using namespace std;

bool isSafe(const vector<vector<int>>& board, int row, int col, int N) {
    // Check the current column
    for (int i = 0; i < row; ++i) {
        if (board[i][col] == 1) {
            return false;
        }
    }

    // Check the upper-left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    // Check the upper-right diagonal
    for (int i = row, j = col; i >= 0 && j < N; --i, ++j) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;
}

bool solveNQueens(vector<vector<int>>& board, int row, int N) {
    if (row >= N) {
        return true; // All queens are placed
    }

    for (int col = 0; col < N; ++col) {
        if (isSafe(board, row, col, N)) {
            board[row][col] = 1; // Place queen

            if (solveNQueens(board, row + 1, N)) {
                return true;
            }

            board[row][col] = 0; // Backtrack
        }
    }

    return false; // No solution found
}

void printBoard(const vector<vector<int>>& board, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
}

int main() {
    int N;
    cout << "Enter the number of queens (N): ";
    cin >> N;

    vector<vector<int>> board(N, vector<int>(N, 0));

    // Try placing the first queen in every column of the first row
    bool solutionFound = false;
    for (int col = 0; col < N; ++col) {
        board[0][col] = 1; // Place the first queen
        if (solveNQueens(board, 1, N)) { // Start solving for the rest of the queens
            solutionFound = true;
            break;
        }
        board[0][col] = 0; // Backtrack if no solution found
    }

    if (solutionFound) {
        cout << "Solution:\n";
        printBoard(board, N);
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}