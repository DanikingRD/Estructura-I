#include <iostream>

using namespace std;

const unsigned int ROWS = 8;
const unsigned int COLS = 8;

const char TORRE = 'T';
const char REINA = 'R';
const char POSIBLE_JUGADA = 'V';
const char JUGADA_ELIMINADA = 'X';

typedef int table_t[ROWS][COLS];
typedef int pos_t[2];

struct Game {
    table_t table;
    pos_t queenPos;
    pos_t towerPos[2];
};

void readPosition(pos_t& pos, const char* ficha) {
    cout << "Ingrese la posición de la " << ficha << " (fila, columna): ";
    while (!(cin >> pos[0] >> pos[1]))
    {
        cout << "Ingrese un posición válida: (fila, columna) ";
        cin.clear();
        cin.ignore(123, '\n');
    }
    cout << " * Posición de la " <<  ficha << ": (" << pos[0] << ", " << pos[1] << ")\n";
}

bool isPosOutOfBounds(int x, int y) {
    return x < 1 || x > ROWS || y < 1 || y > COLS;
}

void printTable(table_t *table)
{
    cout << "  ";
    // Imprime las columnas
    for (int i = 0; i < COLS; i++)
    {
        cout << (i + 1) << " ";
    }
    cout << endl;
    for (int i = 0; i < ROWS; i++)
    {
        cout << (i + 1) << " "; // Imprime las filas
        for (int j = 0; j < COLS; j++)
        {
            
            char value = (*table)[i][j];

            if (value == 0) {
                cout << "- ";
                continue;
            }

            if (value == TORRE)
                printf("\033[1;31m%c\033[0m ", value);
            else if (value == REINA)
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
        cout << "La posición (" << x << ", " << y << ") está fuera de los límites del tablero.\n";
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
    pos_t newPos = {};
    do {
        readPosition(newPos, ficha);
    } while (!checkPos(&game->table, &newPos));
    // Actualiza la posición de la ficha
    (*table)[newPos[0] - 1][newPos[1] - 1] = value;
    
    if (value == REINA) {
        game->queenPos[0] = newPos[0];
        game->queenPos[1] = newPos[1];
    }
    if (value == TORRE) {
        int index = game->towerPos[0][0] == 0 ? 0 : 1;
        game->towerPos[index][0] = newPos[0];
        game->towerPos[index][1] = newPos[1];
    }
    printTable(table);
}

void setPositions(Game* game)
{
    printTable(&game->table);
    getInput(game, "reina", REINA);
    getInput(game, "torre 1", TORRE);
    getInput(game, "torre 2", TORRE);
}

void generateQueenMoves(Game* game) { 
    // El programa debe desplegar el tablero con las
    // jugadas posibles de la Reina, colocando una V donde la reina pueda moverse sin ser eliminada y
    // una X donde pueda moverse, pero ser eliminada por una o las dos torres enemiga

    // 1. Obtener la posición de la reina
    // 2. Obtener las posiciones de las torres
    // 3. Generar las posibles jugadas de la reina
    // 4. Marcar las posibles jugadas de la reina
    // 5. Marcar las posibles jugadas de la reina que pueden ser eliminadas por las torres
    // 6. Mostrar el tablero con las jugadas posibles de la reina

    // 1. Obtener la posición de la reina
    int queenX = game->queenPos[0];
    int queenY = game->queenPos[1];
    cout << "Posición de la reina: (" << queenX << ", " << queenY << ")\n";

    // 2. Obtener las posiciones de las torres
    pos_t* towerA  = &game->towerPos[0];
    pos_t* towerB  = &game->towerPos[1];
    
    cout << "Posición de la torre A: (" << (*towerA)[0] << ", " << (*towerA)[1] << ")\n";
    cout << "Posición de la torre B: (" << (*towerB)[0] << ", " << (*towerB)[1] << ")\n";

    // 3. Generar las posibles jugadas de la reina
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; ++j)
        {
            int x = i + 1;
            int y = j + 1;
            if (x == queenX && y == queenY) continue;
            if (x == queenX || y == queenY || abs(x - queenX) == abs(y - queenY)) {
                // 4. Marcar las posibles jugadas de la reina
                game->table[i][j] = POSIBLE_JUGADA; 
            }
        }
    }
    // TODO: 5. Marcar las posibles jugadas de la reina que pueden ser eliminadas por las torres
    // 6. Mostrar el tablero con las jugadas posibles de la reina
    printTable(&game->table);
}

int readInt()
{
    int value;
    while (!(cin >> value))
    {
        cout << "Ingrese un valor válido: ";
        cin.clear();
        cin.ignore(123, '\n');
    }
    return value;
}

void run()
{
    Game game = {};
    while (true)
    {
        cout << "Presione: \n"
             << "   0) - Para salir del programa.\n"
             << "   1) - Para colocar a las torres y la reina.\n"
             << "   2) - Para generar los movimientos de la reina.\n"
             << "   3) - Para mostrar el tablero.\n"
             << "Ingrese su opción: ";

        int option = readInt();
        cout << endl;

        switch (option)
        {
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

int main(int argc, char const *argv[])
{
    cout << "Corriendo programa Reina vs Torres...\n"
         << endl;
    run();
    return 0;
}
