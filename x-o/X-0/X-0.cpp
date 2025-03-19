#include <iostream>
#include <vector>
#include <limits>

using namespace std;


void printField(const vector<char>& field) {
    cout << " " << field[0] << " | " << field[1] << " | " << field[2] << "\n";
    cout << "---+---+---\n";
    cout << " " << field[3] << " | " << field[4] << " | " << field[5] << "\n";
    cout << "---+---+---\n";
    cout << " " << field[6] << " | " << field[7] << " | " << field[8] << "\n\n";
}

bool checkWin(const vector<char>& field, char player) {
    int winCombos[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };
    for (auto& combo : winCombos) {
        if (field[combo[0]] == player && field[combo[1]] == player && field[combo[2]] == player)
            return true;
    }
    return false;
}

bool isDraw(const vector<char>& field) {
    for (char cell : field) {
        if (cell != 'X' && cell != 'O') return false;
    }
    return true;
}

int getValidMove(vector<char>& field) {
    setlocale(LC_ALL, "Russian");
    int move;
    while (true) {
        cout << "Введите номер клетки (1-9): ";
        if (!(cin >> move) || move < 1 || move > 9 || field[move - 1] == 'X' || field[move - 1] == 'O') {
            cout << "Некорректный ввод\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
    return move - 1;
}

int main() {
    char playAgain;
    do {
        vector<char> field = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
        char currentPlayer = 'X';
        bool gameOver = false;

        while (!gameOver) {
            printField(field);
            cout << "Ход игрока " << currentPlayer << "\n";
            int move = getValidMove(field);
            field[move] = currentPlayer;

            if (checkWin(field, currentPlayer)) {
                printField(field);
                cout << "Игрок " << currentPlayer << " победил\n";
                gameOver = true;
            }
            else if (isDraw(field)) {
                printField(field);
                cout << "Ничья\n";
                gameOver = true;
            }
            else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }

        cout << "Ещё раз? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}
