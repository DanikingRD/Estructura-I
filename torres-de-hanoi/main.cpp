/*
 * ENUNCIADO: Torres de Hanoi
 * INTEGRANTES: 1113684 - Clay Manuel Gomera Arias
 *              1114116 - Jean Carlos Araujo Molina
 *              1116906 - Gabriel Mejía Acosta
 *              1114441 - Rafael Eduardo Peralta Pimentel
 *              1114814 - Hadelin Maria García Cedano
 *              1114950 - Elian Gabriel Villegas Báez
 *              1116614 - Luis Daniel de la Cruz García
 *              1116623 - Aquilenyi Suero de los Santos
 * FECHA: 3/10/2023 <== Fecha de realización
 */
#include <iostream>

using namespace std;

int readInt();
int totalMoves = 0;
// src = source, aux = auxiliary, dest = destination, n = number of disks
void hanoi(int n, char src, char aux, char dst) {
    if (n == 1) {
        cout << "Se mueve anillo 1 de " << src << " a " << dst << endl;
        totalMoves++;
        return;
    }
    hanoi(n - 1, src, dst, aux);
    cout << "Se mueve anillo " << n << " de " << src << " a " << dst << endl;
    totalMoves++;
    hanoi(n - 1, aux, src, dst);
}

void getDisks() {
    int disks;
    cout << "Ingrese el número de discos: ";
    disks = readInt();
    cout << endl;
    cout << "Resolviendo Torres de Hanoi con " << disks << " discos..." << endl;
    hanoi(disks, 'A', 'B', 'C');
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

void run() {
    while (true) {
        cout << "Seleccione una opción: " << endl;
        cout << "0. Salir" << endl;
        cout << "1. Resolver Torres de Hanoi" << endl;
        cout << "Opción: ";
        int option = readInt();
        cout << endl;

        switch (option) {
        case 0:
            cout << "Saliendo del programa...\n";
            exit(0);
            break;
        case 1:
            getDisks();
            cout << "Total de movimientos: " << totalMoves << endl;
            break;
        default:
            break;
        }
        cout << endl;
        totalMoves = 0;
    }
}

int main(void) {
    cout << "Corriendo programa Torres de Hanoi...\n" << endl;
    run();
    return 0;
}
