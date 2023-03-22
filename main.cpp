#include <iostream>
#include <string>

using namespace std;


// Заполнение матриц
void filling(char matrix[11][11], char matrix2[11][11]) {
    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 11; ++j) {
            if (i == 0 && j != 0) {
                matrix[i][j] = static_cast<char>(j - 1 + '0');
                matrix2[i][j] = static_cast<char>(j - 1 + '0');
            } else if (j == 0 && i != 0) {
                matrix[i][j] = static_cast<char>(i - 1 + '0');
                matrix2[i][j] = static_cast<char>(i - 1 + '0');
            } else {
                matrix[i][j] = '.';
                matrix2[i][j] = '.';
            }
            matrix[0][0] = ' ';
            matrix2[0][0] = ' ';
        }
    }
}

//Отрисовка полей боя
void showFields(char matrix[11][11], char matrix2[11][11]) {

    cout << endl;
    cout << "Your Battlefield              Opponent's Battlefield\n";

    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 11; ++j) {
            cout << matrix[i][j] << ' ';
        }
        cout << "        ";
        for (int j = 0; j < 11; ++j) {
            cout << matrix2[i][j] << ' ';
        }
        cout << endl;
    }
        cout << endl;
}

// Проверка создания кораблей
bool initialShips(char matrix[11][11], int sizeShip) {
    int xStart, yStart, xEnd, yEnd;

    do {
        cout << "Input start coordinates X Y: ";
        cin >> xStart >> yStart;
    } while (xStart < 0 || xStart > 9 || yStart < 0 || yStart > 9);

    if (sizeShip > 1) {
        cout << "Input end coordinates X Y: ";
        cin >> xEnd >> yEnd;
    } else {
        xEnd = xStart;
        yEnd = yStart;
    }

    if (xStart < 0 || xStart > 9 || yStart < 0 || yStart > 9 || xEnd < 0 || xEnd > 9 || yEnd < 0 || yEnd > 9) {
        cerr << "Wrong coordinates!" << endl;
        return false;
    }

    //Поправка индексов под матрицы с координатами
    xStart += 1;
    yStart += 1;
    xEnd += 1;
    yEnd += 1;

    if (xEnd < xStart) {
        int tmp = xStart;
        xStart = xEnd;
        xEnd = tmp;
    }
    if (yEnd < yStart) {
        int tmp = yStart;
        yStart = yEnd;
        yEnd = tmp;
    }

    int xLength = xEnd - xStart;
    int yLength = yEnd - yStart;

    if (xLength != 0) {
        if ((xLength + 1 != sizeShip) && yLength == 0) {
            cerr << "Invalid size ship!" << endl;
            return false;
        }

        if (yLength != 0) {
            cerr << "Diagonal ships not support!" << endl;
            return false;
        }

        for (int x = xStart; x <= xEnd; ++x) {
            if (matrix[x][yStart] == '#') {
                cerr << "Ships cannot cross!" << endl;
                return false;
            }
        }
        for (int x = xStart; x <= xEnd; ++x) {
            matrix[x][yStart] = '#';
        }
    } else {
        if (yLength + 1 != sizeShip) {
            cerr << "Invalid size ship!" << endl;
            return false;
        }

        for (int y = yStart; y <= yEnd; ++y) {
            if (matrix[xStart][y] == '#') {
                cerr << "Ships cannot cross!" << endl;
                return false;
            }
        }

        for (int y = yStart; y <= yEnd; ++y) {
            matrix[xStart][y] = '#';
        }

    }

    return true;
}

//Расстановка кораблей
void placeShips(char field[11][11], char fieldOp[11][11]) {
    showFields(field, fieldOp);
    for (int i = 0; i < 1; ++i) {
        cout << "Place a BIG ship ####:" << endl;
        while (!initialShips(field, 4)) {
            cout << "Please, try again!" << endl;
        }
        showFields(field, fieldOp);
    }

    for (int i = 0; i < 2; ++i) {
        cout << "Place a MEDIUM ship ###:" << endl;
        while (!initialShips(field, 3)) {
            cout << "Please, try again!" << endl;
        }
        showFields(field, fieldOp);
    }

    for (int i = 0; i < 3; ++i) {
        cout << "Place a SMALL ship ##:" << endl;
        while (!initialShips(field, 2)) {
            cout << "Please, try again!" << endl;
        }
        showFields(field, fieldOp);
    }

    for (int i = 0; i < 4; ++i) {
        cout << "Place a TINY ship #:" << endl;
        while (!initialShips(field, 1)) {
            cout << "Please, try again!" << endl;
        }
        showFields(field, fieldOp);
    }

}

//Фаза атаки игрока
bool attack(char matrixPlayer1[11][11], char matrixPlayer2[11][11], char matrixOpponent1[11][11]) {
    int x, y;
    bool valid = false;

    showFields(matrixPlayer1, matrixOpponent1);

    do {
        cout << "Input attack coordinates X Y: ";
        cin >> x >> y;
        if (x < 0 || x > 9 || y < 0 || y > 9) {
            cout << "Wrong coordinates!" << endl;
        } else if (matrixOpponent1[x + 1][y + 1] == '+') {
            cout << "You already shot there!" << endl;
        } else {
            valid = true;
        }
    } while (!valid);

    //Поправка индексов под матрицы с координатами
    x += 1;
    y += 1;

    if (matrixPlayer2[x][y] == '#') {
        matrixPlayer2[x][y] = 'X';
        matrixOpponent1[x][y] = 'X';
        return true;
    } else {
        matrixOpponent1[x][y] = '+';
        return false;
    }
}

int main() {
    char fieldPlayer1[11][11], fieldPlayer2[11][11];
    char fieldOpponent1[11][11], fieldOpponent2[11][11];
    int countShips1 = 1 * 4 + 2 * 3 + 3 * 2 + 4 * 1;
    int countShips2 = 1 * 4 + 2 * 3 + 3 * 2 + 4 * 1;
    string player1, player2;

    filling(fieldPlayer1, fieldOpponent1);
    filling(fieldPlayer2, fieldOpponent2);

    cout << "Player 1, enter your name: ";
    cin >> player1;
    cout << "Player 2, enter your name: ";
    cin >> player2;

    cout << endl;
    cout << player1 << ", place ships!" << endl;
    placeShips(fieldPlayer1, fieldOpponent1);
    system("CLEAR");
    cout << player2 << ", place ships!  Press Enter to continue..." << endl;
    system("READ");
    placeShips(fieldPlayer2, fieldOpponent2);
    system("CLEAR");
    cout << "START" << endl;
    cout << "Press Enter to continue" << endl;
    system("READ");

    while (true) {
        cout << player1 << "! Your turn!" << endl;
        cout << "Press Enter to continue" << endl;
        system("READ");

        while (attack(fieldPlayer1, fieldPlayer2, fieldOpponent1)) {
            countShips2 -= 1;
            if (countShips2 == 0) {
                showFields(fieldPlayer1, fieldOpponent1);
                cout << endl;
                cout << player1 << " WINS!!" << endl;
                return 0;
            }
        }

        system("CLEAR");
        cout << player2 << "! Your turn!" << endl;
        cout << "Press Enter to continue" << endl;
        system("READ");

        while (attack(fieldPlayer2, fieldPlayer1, fieldOpponent2)) {
            countShips1 -= 1;
            if (countShips1 == 0) {
                showFields(fieldPlayer2, fieldOpponent2);
                cout << endl;
                cout << player2 << " WINS!!" << endl;
                return 0;
            }
        }
        system("CLEAR");
    }

}
