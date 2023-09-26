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

typedef int table_t[ROWS][COLS];
typedef int pos_t[2];

struct Game {
    table_t table;
    pos_t queenPos;
    pos_t towerPos[2];
};

void readPosition(pos_t& pos, const char* ficha) {
    cout << "Ingrese la posición de la " << ficha << " (fila, columna): ";
    while (!(cin >> pos[0] >> pos[1])) {
        cout << "Ingrese un posición válida: (fila, columna) ";
        cin.clear();
        cin.ignore(123, '\n');
    }
    cout << " * Posición de la " << ficha << ": (" << pos[0] << ", " << pos[1]
         << ")\n";
}

bool isPosOutOfBounds(int x, int y) {
    return x < 1 || x > ROWS || y < 1 || y > COLS;
}

void printTable(table_t* table) {
    cout << "  ";
    // Imprime las columnas
    for (int i = 0; i < COLS; i++) {
        cout << (i + 1) << " ";
    }
    cout << endl;
    for (int i = 0; i < ROWS; i++) {
        cout << (i + 1) << " "; // Imprime las filas
        for (int j = 0; j < COLS; j++) {

            char value = (*table)[i][j];

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

bool checkPos(table_t* table, pos_t* pos) {

    int x = (*pos)[0];
    int y = (*pos)[1];

    if (isPosOutOfBounds(x, y)) {
        cout << "La posición (" << x << ", " << y
             << ") está fuera de los límites del tablero.\n";
        return false;
    }

    int row = x - 1;
    int col = y - 1;

    if ((*table)[row][col] != 0) {
        cout << "La posición (" << x << ", " << y << ") ya está ocupada.\n";
        return false;
    }
    return true;
}

void getInput(Game* game, const char* ficha, char value) {
    table_t* table = &game->table;
    pos_t pos = {};
    do {
        readPosition(pos, ficha);
    } while (!checkPos(&game->table, &pos));
    // Actualiza la posición de la ficha
    int new_pos_x = pos[0] - 1;
    int new_pos_y = pos[1] - 1;
    (*table)[new_pos_x][new_pos_y] = value;

    if (value == QUEEN) {
        game->queenPos[0] = new_pos_x;
        game->queenPos[1] = new_pos_y;
    }
    if (value == TOWER) {
        int index = game->towerPos[0][0] == 0 ? 0 : 1;
        game->towerPos[index][0] = new_pos_x;
        game->towerPos[index][1] = new_pos_y;
    }
    printTable(table);
}

void setPositions(Game* game) {
    printTable(&game->table);
    getInput(game, "reina", QUEEN);
    getInput(game, "torre 1", TOWER);
    getInput(game, "torre 2", TOWER);
}

bool isTowerInRange(pos_t* towerPos, pos_t pos) {
    int towerX = (*towerPos)[0];
    int towerY = (*towerPos)[1];
    int checkX = pos[0];
    int checkY = pos[1];

    // La torre esta en el rango si la posicion coincide
    // con almenos uno de sus ejes.
    if (towerX == checkX || towerY == checkY) {
        return true;
    }
    return false;
}

void generateQueenMoves(Game* game) {
    // El programa debe desplegar el tablero con las
    // jugadas posibles de la Reina, colocando una V donde la reina pueda
    // moverse sin ser eliminada y una X donde pueda moverse, pero ser eliminada
    // por una o las dos torres enemiga

    // 1. Obtener la posición de la reina
    // 2. Obtener las posiciones de las torres
    // 3. Generar las posibles jugadas de la reina
    // 4. Marcar las posibles jugadas de la reina
    // 5. Marcar las posibles jugadas de la reina que pueden ser eliminadas por
    // las torres
    // 6. Mostrar el tablero con las jugadas posibles de la reina

    // 1. Obtener la posición de la reina
    int queenX = game->queenPos[0];
    int queenY = game->queenPos[1];

    // 2. Obtener las posiciones de las torres
    pos_t* towerA = &game->towerPos[0];
    pos_t* towerB = &game->towerPos[1];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            pos_t checkPos = {i, j};

            bool isQueenPos = queenX == i && queenY == j;
            bool isTowerAPos = (*towerA)[0] == i && (*towerA)[1] == j;
            bool isTowerBPos = (*towerB)[0] == i && (*towerB)[1] == j;

            if (isQueenPos || isTowerAPos || isTowerBPos) {
                continue;
            }

            bool isDiagonal = std::abs(i - queenX) == std::abs(j - queenY);
            if (isDiagonal || queenX == i || queenY == j) {
                bool eliminatedByTowerA = isTowerInRange(towerA, checkPos);
                bool eliminatedByTowerB = isTowerInRange(towerB, checkPos);

                if (eliminatedByTowerA || eliminatedByTowerB) {
                    game->table[i][j] = IS_ELIMINATED;
                } else {
                    game->table[i][j] = CAN_PLAY;
                }
            }
        }
    }
    // determinar las jugadas
    printTable(&game->table);
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

#include <cstring>

void run() {
    Game game = {};
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
            memset(game.table, 0, sizeof(game.table));
            setPositions(&game);
            break;
        case 2:
            generateQueenMoves(&game);
            break;
        case 3:
            printTable(&game.table);
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
