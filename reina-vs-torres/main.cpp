/*
 * ENUNCIADO: Reina vs Torres Enemigas
 * INTEGRANTES: 1113684 - Clay Manuel Gomera Arias
 *              1114116 - Jean Carlos Araujo Molina
 *              1116906 - Gabriel Mejía Acosta
 *              1114441 - Rafael Eduardo Peralta Pimentel
 *              1114814 - Hadelin Maria García Cedano
 *              1114950 - Elian Gabriel Villegas Báez
 *              1116614 - Luis Daniel de la Cruz García
 *              1116623 - Aquilenyi Suero de los Santos
 * FECHA: 17/09/2023 <== Fecha de realización
 */

#include <iostream>

using namespace std;

const unsigned int ROWS = 8;
const unsigned int COLS = 8;

const char TOWER = 'T';
const char QUEEN = 'R';
const char CAN_PLAY = 'V';
const char IS_ELIMINATED = 'X';

typedef int Table[ROWS][COLS];
typedef int Pos[2];

struct Game {
    Table table;
    Pos queenPos;
    Pos towerPos[2];
};

Game game = {};

bool isPosOutOfBounds(int x, int y) {
    return x < 1 || x > ROWS || y < 1 || y > COLS;
}

void printTable() {
    cout << "  ";
    // Imprime las columnas
    for (int i = 0; i < COLS; i++) {
        cout << (i + 1) << " ";
    }
    cout << endl;
    for (int i = 0; i < ROWS; i++) {
        cout << (i + 1) << " "; // Imprime las filas
        for (int j = 0; j < COLS; j++) {

            char value = game.table[i][j];

            if (value == 0) {
                cout << "- ";
                continue;
            }

            if (value == TOWER)
                printf("\033[1;31m%c\033[0m ", value);
            else if (value == QUEEN)
                printf("\033[1;32m%c\033[0m ", value);
            else
                printf("%c ", value);
        }
        cout << endl;
    }
    cout << endl;
}

bool checkPos(Pos* pos) {

    int x = (*pos)[0];
    int y = (*pos)[1];

    if (isPosOutOfBounds(x, y)) {
        cout << "La posición (" << x << ", " << y
             << ") está fuera de los límites del tablero.\n";
        return false;
    }

    int row = x - 1;
    int col = y - 1;

    if (game.table[row][col] != 0) {
        cout << "La posición (" << x << ", " << y << ") ya está ocupada.\n";
        return false;
    }
    return true;
}

void readPosition(Pos& pos, const char* ficha) {
    cout << "Ingrese la posición de la " << ficha << " (fila, columna): ";
    while (!(cin >> pos[0] >> pos[1])) {
        cout << "Ingrese un posición válida: (fila, columna) ";
        cin.clear();
        cin.ignore(123, '\n');
    }
    cout << " * Posición de la " << ficha << ": (" << pos[0] << ", " << pos[1]
         << ")\n";
}

void setPositions() {
    printTable();
    const unsigned int pieces = 3;
    const char* names[] = {"reina", "torre 1", "torre 2"};
    const char tags[] = {QUEEN, TOWER, TOWER};

    for (int i = 0; i < pieces; i++) {
        Pos pos = {};
        do {
            readPosition(pos, names[i]);
        } while (!checkPos(&pos));
        // actualiza el tablero
        int x = pos[0] - 1;
        int y = pos[1] - 1;
        game.table[x][y] = tags[i];
        switch (tags[i]) {
        case QUEEN:
            game.queenPos[0] = x;
            game.queenPos[1] = y;
            break;
        case TOWER:
            game.towerPos[i - 1][0] = x;
            game.towerPos[i - 1][1] = y;
            break;
        }
        printTable();
    }
}


void checkMove(int i, int j, Pos towerA, Pos towerB) {
    int x = game.queenPos[0];
    int y = game.queenPos[1];

}
void generateQueenMoves() {
    int queenX = game.queenPos[0];
    int queenY = game.queenPos[1];
    Pos& towerA = game.towerPos[0];
    Pos& towerB = game.towerPos[1];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            Pos checkPos = {i, j};

            bool skipQueen = queenX == i && queenY == j;
            bool skipTowerA = towerA[0] == i && towerA[1] == j;
            bool skipTowerB = towerB[0] == i && towerB[1] == j;

            if (skipQueen || skipTowerA || skipTowerB)
                continue;

            bool isDiagonalMove = std::abs(i - queenX) == std::abs(j - queenY);
            bool isQueenMove = isDiagonalMove || i == queenX || j == queenY;

            if (isQueenMove) {
                checkMove(i, j, towerA, towerB);
            }
        }
    }
    printTable();
}


int readInt() {
    int value;
    while (!(cin >> value)) {
        cout << "Ingrese un valor válido: ";
        cin.clear();
        cin.ignore(123, '\n');
    }
    return value;
}

static bool tableInitialized = false;

void run() {
    while (true) {
        cout << "Presione: \n"
             << "   0) - Para salir del programa.\n"
             << "   1) - Para colocar a las torres y la reina.\n"
             << "   2) - Para generar los movimientos de la reina.\n"
             << "   3) - Para mostrar el tablero.\n"
             << "Ingrese su opción: ";

        int option = readInt();
        cout << endl;

        switch (option) {
        case 0:
            cout << "Saliendo del programa...\n";
            exit(0);
            break;
        case 1:
            for (int i = 0; i < ROWS; i++) {
                for (int j = 0; j < COLS; j++)
                    game.table[i][j] = 0;
            }
            setPositions();
            tableInitialized = true;
            break;
        case 2:
            if (!tableInitialized) {
                cout << " * Debe colocar las torres y la reina primero.\n";
                break;
            }
            generateQueenMoves();
            break;
        case 3:
            printTable();
            break;
        default:
            break;
        }
        cout << endl;
    }
}

int main(int argc, char const* argv[]) {
    cout << "Corriendo programa Reina vs Torres...\n" << endl;
    run();
    return 0;
}
