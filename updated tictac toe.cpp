#include <iostream>
using namespace std;

class Board {
private:
    char grid[3][3];

public:
    Board() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                grid[i][j] = ' ';
    }

    void display() const {
        for (int i = 0; i < 3; ++i) {
            cout << " " << grid[i][0] << " | " << grid[i][1] << " | " << grid[i][2] << "\n";
            if (i < 2) cout << "---|---|---\n";
        }
    }

    bool isCellEmpty(int row, int col) const {
        return grid[row][col] == ' ';
    }

    bool setCell(int row, int col, char player) {
        if (isCellEmpty(row, col)) {
            grid[row][col] = player;
            return true;
        }
        return false;
    }

    bool isFull() const {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (grid[i][j] == ' ')
                    return false;
        return true;
    }

    bool checkWin(char player) const {
        for (int i = 0; i < 3; ++i)
            if ((grid[i][0] == player && grid[i][1] == player && grid[i][2] == player) ||
                (grid[0][i] == player && grid[1][i] == player && grid[2][i] == player))
                return true;

        if ((grid[0][0] == player && grid[1][1] == player && grid[2][2] == player) ||
            (grid[0][2] == player && grid[1][1] == player && grid[2][0] == player))
            return true;

        return false;
    }

    int getEmptyCells(int rows[], int cols[]) const {
        int count = 0;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (grid[i][j] == ' ') {
                    rows[count] = i;
                    cols[count] = j;
                    ++count;
                }
        return count;
    }
};

class AI {
private:
    int counter;

public:
    AI() : counter(0) {}

    void chooseMove(const Board& board, int& row, int& col) {
        int rows[9], cols[9];
        int count = board.getEmptyCells(rows, cols);
        if (count > 0) {
            counter = (counter + 1) % count;
            row = rows[counter];
            col = cols[counter];
        }
    }
};

class Game {
private:
    Board board;
    AI ai;
    char player1 = 'X';
    char player2 = 'O';
    bool vsAI;

public:
    Game() {
        int choice;
        cout << "Choose mode:\n1. Player vs AI\n2. Player vs Player\nEnter choice: ";
        cin >> choice;
        vsAI = (choice == 1);
    }

    void play() {
        char currentPlayer = player1;

        while (true) {
            board.display();
            int row, col;

            if (vsAI && currentPlayer == player2) {
                cout << "AI is making a move...\n";
                ai.chooseMove(board, row, col);
                board.setCell(row, col, player2);
            } else {
                cout << "Player " << currentPlayer << "'s turn.\n";
                cout << "Enter row (1-3): ";
                cin >> row;
                cout << "Enter column (1-3): ";
                cin >> col;
                row--; col--;

                if (!board.setCell(row, col, currentPlayer)) {
                    cout << "Cell is occupied. Try again.\n";
                    continue;
                }
            }

            if (board.checkWin(currentPlayer)) {
                board.display();
                cout << "Player " << currentPlayer << " wins!\n";
                break;
            }

            if (board.isFull()) {
                board.display();
                cout << "It's a draw!\n";
                break;
            }

            currentPlayer = (currentPlayer == player1) ? player2 : player1;
        }
    }
};

int main() {
	cout <<"----- ----- -----"<<endl;
	cout <<"  | ic  |ac   |oe"<<endl;
	cout <<"--------------------------------------------------"<<endl;
	while(true){
    Game game;
    game.play();}
    return 0;
}

