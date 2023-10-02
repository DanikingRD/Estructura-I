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
 * FECHA: 17/09/2023 <== Fecha de realización
 */
#include <iomanip>
#include <iostream>
using namespace std;

struct Student {
    int id;
    string name;
    string coordinator;
    int academic_idx;
    Student* next;
};

const unsigned int MAX = 40;

Student hash_table[MAX] = {};
int readInt();
string readStr();
Student* createStudent(int studentId);

int hashfn(int id) { return id % MAX; }

void insertStudent(int studentId) {
    // check if table is full
    if (hash_table[MAX - 1].id) {
        cout << "Tabla llena" << endl;
        return;
    }
    int table_index = hashfn(studentId);
    // check if there is a collision
    if (hash_table[table_index].id) {
        cout << "Resolviendo colisión..." << endl;
        // resolve collision
        Student* current = &hash_table[table_index];
        // go to the last element
        while (current->next) {
            current = current->next;
        }
        Student* st = createStudent(studentId);
        current->next = st;
    } else {
        // There is no collision
        Student* st = createStudent(studentId);
        hash_table[table_index] = *st;
    }
    cout << " * Estudiante insertado en slot #" << table_index << endl;
}

Student* createStudent(int studentId) {
    cout << "Ingrese el nombre del estudiante: ";
    string name = readStr();
    cout << "Ingrese el nombre del coordinador: ";
    string coordinator = readStr();
    cout << "Ingrese el indice académico del estudiante: ";
    int academic_idx = readInt();
    Student* student = new (Student){
        .id = studentId,
        .name = name,
        .coordinator = coordinator,
        .academic_idx = academic_idx,
        .next = 0,
    };
    return student;
}

void displayHashTable() {
    cout << " * Imprimiendo tabla hash..." << endl;
    for (int i = 0; i < MAX; i++) {
        Student* current = &hash_table[i];
        while (current) {
            // draw some sort of pretty table
            string id = to_string(current->id);
            string name = current->name;
            string coordinator = current->coordinator;
            string academic_idx = to_string(current->academic_idx);
            // calculate the width of each field
            int next_width =
                current->next ? to_string(current->next->id).length() : 4;
            string nextPtr =
                current->next ? to_string(current->next->id) : "null";
            // pad the fields with spaces to ensure that the display borders are
            // fixed
            int extra_padding = 2;
            string id_padded = string(35 - id.length(), ' ') + id;
            string name_padded = string(31 - name.length(), ' ') + name;
            string coordinator_padded =
                string(26 - coordinator.length(), ' ') + coordinator;
            string academic_idx_padded =
                string(21 - academic_idx.length(), ' ') + academic_idx;
            string next_padded = string(28 - next_width, ' ') + nextPtr;

            if (i > 9)
                cout << "\033[1;33m┌───────────────── \033[0m"
                     << "Slot#" << i << "\033[1;33m ──────────────┐\033[0m"
                     << endl;
            else
                cout << "\033[1;33m┌────────────────── \033[0m"
                     << "Slot#" << i << "\033[1;33m ──────────────┐\033[0m"
                     << endl;
            cout << "\033[1;33m│ Id: " << id_padded << "│\033[0m" << endl;
            cout << "\033[1;33m│ Nombre: " << name_padded << "│\033[0m" << endl;
            cout << "\033[1;33m│ Coordinador: " << coordinator_padded
                 << "│ \033[0m" << endl;
            cout << "\033[1;33m│ Indice académico: " << academic_idx_padded
                 << "│\033[0m" << endl;
            cout << "\033[1;33m│ Siguiente: " << next_padded << "│\033[0m"
                 << endl;
            cout
                << "\033[1;33m└────────────────────────────────────────┘\033[0m"
                << endl;
            current = current->next;
        }
    }
}

string readStr() {
    string value;
    while (!(cin >> value)) {
        cout << "Ingrese un valor válido: ";
        cin.clear();
        cin.ignore(123, '\n');
    }
    std::cin.ignore();
    return value;
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
    displayHashTable();
    while (true) {
        cout << "Seleccione una opción: " << endl;
        cout << "0. Salir" << endl;
        cout << "1. Insertar un estudiante." << endl;
        cout << "4. Para mostrar la tabla hash." << endl;
        cout << "Opción: ";
        int option = readInt();
        cout << endl;

        switch (option) {
        case 0:
            cout << "Saliendo del programa...\n";
            exit(0);
            break;
        case 1:
            cout << "Ingrese el id del estudiante: ";
            int studentId;
            studentId = readInt();
            cout << "Insertando estudiante con Id: " << studentId << endl;
            insertStudent(studentId);
            break;
        case 4:
            displayHashTable();
            break;
        default:
            break;
        }
        cout << endl;
    }
}

int main(void) {
    cout << "Corriendo programa Tabla Hash...\n" << endl;
    run();
    return 0;
}
