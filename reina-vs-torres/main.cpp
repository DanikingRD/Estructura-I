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
 * FECHA: 27/09/2023 <== Fecha de realización
 */

#include <iostream>

using namespace std;

const unsigned int ROWS = 8;
const unsigned int COLS = 8;

const char TOWER = 'T';
const char QUEEN = 'R';
const char CAN_PLAY = 'V';
const char IS_ELIMINATED = 'X';
// Representa el tablero de juego
typedef int Table[ROWS][COLS];
// Representa una posición en el tablero
typedef int Pos[2];

void readPos(Pos& pos, const char* ficha);
bool isPosBlocked(int currentRow, int currentCol);
bool towerKillsQueen(int towerX, int towerY, int checkX, int checkY);

// Contiene la información del juego
struct Game {
    Table table;
    Pos queenPos;
    Pos towerPos[2];
};

// Instancia del juego
Game game = {};

// Imprime el tablero de juego
void printTable() {
    cout << "  ";
    for (int i = 0; i < COLS; i++) {
        cout << (i + 1) << " "; // Imprime las columnas
    }
    cout << endl;
    for (int i = 0; i < ROWS; i++) {
        cout << (i + 1) << " "; // Imprime las filas
        for (int j = 0; j < COLS; j++) {
            char value = game.table[i][j];
            if (!value) { // Posición vacía
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

/*
 * Verifica si la posición ingresada es válida.
 * Una posición es válida si está dentro de los límites del tablero
 */
bool isPosValid(Pos* pos) {

    int row = (*pos)[0];
    int col = (*pos)[1];

    if (row < 1 || row > ROWS || col < 1 || col > COLS) {
        cout << "La posición (" << row << ", " << col
             << ") está fuera de los límites del tablero.\n";
        return false;
    }

    int i = row - 1;
    int j = col - 1;

    if (game.table[row][col] != 0) {
        cout << "La posición (" << row << ", " << col << ") ya está ocupada.\n";
        return false;
    }
    return true;
}

/*
 * Coloca las torres y la reina en el tablero
 */
void setPositions() {
    printTable();
    const unsigned int pieces = 3;
    const char* names[] = {"reina", "torre 1", "torre 2"};
    const char tags[] = {QUEEN, TOWER, TOWER};
    for (int i = 0; i < pieces; i++) {
        Pos pos = {};
        do {
            readPos(pos, names[i]);
        } while (!isPosValid(&pos));
        // actualiza el tablero
        int x = pos[0] - 1;
        int y = pos[1] - 1;

        // == Actualiza el estado del juego ==
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

/*
 * Genera los movimientos posibles de la reina
 */
void generateQueenMoves() {
    int queenCol = game.queenPos[0];
    int queenRow = game.queenPos[1];
    Pos& towerA = game.towerPos[0];
    Pos& towerB = game.towerPos[1];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            bool skipQueen = queenCol == i && queenRow == j;
            bool skipTowerA = towerA[0] == i && towerA[1] == j;
            bool skipTowerB = towerB[0] == i && towerB[1] == j;

            if (skipQueen || skipTowerA || skipTowerB)
                continue;

            bool isDiagonalMove =
                std::abs(i - queenCol) == std::abs(j - queenRow);

            bool isQueenMove = isDiagonalMove || i == queenCol || j == queenRow;

            if (!isQueenMove) {
                // salta si no es un movimiento válido de la reina
                continue;
            }

            if (!isPosBlocked(i, j)) {
                bool eliminatedByTowerA =
                    towerKillsQueen(towerA[0], towerA[1], i, j);
                bool eliminatedByTowerB =
                    towerKillsQueen(towerB[0], towerB[1], i, j);
                if (eliminatedByTowerA || eliminatedByTowerB) {
                    game.table[i][j] = IS_ELIMINATED;
                } else {
                    game.table[i][j] = CAN_PLAY;
                }
            }
        }
    }
    printTable();
}

/*
 * Determina si la posible siguiente posición de la reina
 * está bloqueada por alguna de las torres
 */
bool isPosBlocked(int currentRow, int currentCol) {
    int queenRow = game.queenPos[0];
    int queenCol = game.queenPos[1];
    for (int i = 0; i < 2; i++) {
        int towerRow = game.towerPos[i][0];
        int towerCol = game.towerPos[i][1];

        bool diagonalTower =
            abs(queenRow - towerRow) == abs(queenCol - towerCol);
        bool diagonalQueenPos =
            abs(queenRow - currentRow) == abs(queenCol - currentCol);

        if (!diagonalTower) {
            bool isTowerOnQueenRow = queenRow == towerRow;
            if (queenRow == currentRow && isTowerOnQueenRow) {
                if (queenCol < towerCol && towerCol < currentCol) {
                    return true;
                }
                if (queenCol > towerCol && towerCol > currentCol) {
                    return true;
                }
            }
            bool isTowerOnQueenCol = queenCol == towerCol;
            if (queenCol == currentCol && isTowerOnQueenCol) {
                if (queenRow < towerRow && towerRow < currentRow) {
                    return true;
                }
                if (queenRow > towerRow && towerRow > currentRow) {
                    return true;
                }
            }
        } else if (diagonalQueenPos) {
            // La torre esta en la misma diagonal que la reina
            // y a su vez la posible siguiente posición de la reina también es
            // diagonal
            if (queenRow < towerRow && towerRow < currentRow) {
                if (queenCol < towerCol && towerCol < currentCol) {
                    return true;
                }
                if (queenCol > towerCol && towerCol > currentCol) {
                    return true;
                }
            }
        }
    }
    return false; // Position is not blocked by towers
}

/*
 * Determina si la torre en la posición (towerX, towerY) mata a la reina
 */
bool towerKillsQueen(int towerX, int towerY, int checkX, int checkY) {
    if (towerX == checkX || towerY == checkY) {
        return true;
    }
    return false;
}

/*
 * Lee una posición del tablero
 */
void readPos(Pos& pos, const char* ficha) {
    cout << "Ingrese la posición de la " << ficha << " (fila, columna): ";
    while (!(cin >> pos[0] >> pos[1])) {
        cout << "Ingrese un posición válida: (fila, columna) ";
        cin.clear();
        cin.ignore(123, '\n');
    }
    cout << " * Posición de la " << ficha << ": (" << pos[0] << ", " << pos[1]
         << ")\n";
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
