#include <iostream>
#include <vector>
#include <limits>
using namespace std;

vector<vector<int>> space;
vector<int> filled;
int rows, cols;
int playersnum = 0;
int currentplayer = 0;

bool check_win(int player, const vector<vector<int>>& board) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {

            if (col <= cols - 4 && board[row][col] == player && board[row][col + 1] == player &&
                board[row][col + 2] == player && board[row][col + 3] == player) {
                return true;
            }

            if (row <= rows - 4 && board[row][col] == player && board[row + 1][col] == player &&
                board[row + 2][col] == player && board[row + 3][col] == player) {
                return true;
            }

            if (row <= rows - 4 && col <= cols - 4 && board[row][col] == player &&
                board[row + 1][col + 1] == player && board[row + 2][col + 2] == player &&
                board[row + 3][col + 3] == player) {
                return true;
            }

            if (row >= 3 && col <= cols - 4 && board[row][col] == player &&
                board[row - 1][col + 1] == player && board[row - 2][col + 2] == player &&
                board[row - 3][col + 3] == player) {
                return true;
            }
        }
    }
    return false;
}

void drawboard() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            cout << space[row][col] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    while (true) {
        cout << "Enter the number of rows for the board (4-20): ";
        cin >> rows;
        if (cin.fail() || rows < 4 || rows > 20) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 4 and 20." << endl;
        } else {
            break;
        }
    }

    while (true) {
        cout << "Enter the number of columns for the board (4-20): ";
        cin >> cols;
        if (cin.fail() || cols < 4 || cols > 20) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 4 and 20." << endl;
        } else {
            break;
        }
    }

    space = vector<vector<int>>(rows, vector<int>(cols, 0));
    filled = vector<int>(cols, rows - 1);

    do {
        cout << "How many players do you want to play? (2-5): ";
        cin >> playersnum;
        if (playersnum < 2 || playersnum > 5) {
            cout << "Player count must be between 2 and 5." << endl;
        }
    } while (playersnum < 2 || playersnum > 5);

    currentplayer = 1;
    while (true) {
        drawboard();
        int pos_pl;
        cout << "Player " << currentplayer << "'s turn. Enter the column number (1-" << cols << "): ";
        cin >> pos_pl;

        if (pos_pl < 1 || pos_pl > cols) {
            cout << "Invalid column! Please enter a number between 1 and " << cols << "." << endl;
            continue;
        }

        if (filled[pos_pl - 1] < 0) {
            cout << "There are no more spaces in this column!" << endl;
            continue;
        }

        space[filled[pos_pl - 1]][pos_pl - 1] = currentplayer;

        if (check_win(currentplayer, space)) {
            drawboard();
            cout << "Player " << currentplayer << " wins!" << endl;
            return 0;
        }

        bool draw = true;
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                if (space[i][j] == 0){
                    draw = false;
                    break;
                }
            }
        }
        if (draw) {
            drawboard();
            cout << "The game is a draw!" << endl;
            return 0;
        }

        filled[pos_pl - 1]--;
        if (currentplayer == playersnum){
            currentplayer = 1;
        }
        else {
            currentplayer++;
        }
    }
}