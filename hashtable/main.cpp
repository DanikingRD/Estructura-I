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

const unsigned int MAX = 40;

struct Student;
int readInt();
string readStr();
Student* createStudent(int studentId);
void printTable(Student* current, int slot);

struct Student {
    int id;
    string name;
    string coordinator;
    int academic_idx;
    Student* next;
};

Student hash_table[MAX] = {};

void displayHashTable() {
    cout << " * Imprimiendo tabla hash..." << endl;
    for (int i = 0; i < MAX; i++) {
        Student* current = &hash_table[i];
        while (current) {
            printTable(current, i);
            current = current->next;
        }
    }
}

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

void get(int studentId) {
    // Resumen de pasos:
    // 1) Hashear el id del estudiante
    // 2) Buscar el bucket correspondiente
    // 3) Recorrer la lista enlazada hasta encontrar el estudiante
    // 4) Imprimir el estudiante
    cout << "Buscando estudiante con Id: " << studentId << endl;
    int hash = hashfn(studentId);
    Student* entry = &hash_table[hash];
    while (entry) {
        if (entry->id == studentId) {
            printTable(entry, hash);
            return;
        }
        entry = entry->next;
    }
    cout << "No se encontró el estudiante con id: " << studentId << endl;
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

string padString(string str, int width) {
    return string(width - str.length(), ' ') + str;
}

void printTable(Student* current, int slot) {
    string id_pad = padString(to_string(current->id), 35);
    string name_padded = padString(current->name, 31);
    string coordinator_padded = padString(current->coordinator, 26);
    string academic_idx_padded =
        padString(to_string(current->academic_idx), 21);
    string nextPtr = current->next ? to_string(current->next->id) : "null";
    string next_padded = padString(nextPtr, 28);

    if (slot > 9)
        cout << "┌─────────────────"
             << " Slot#" << slot << " ──────────────┐" << endl;
    else
        cout << "┌──────────────────"
             << " Slot#" << slot << " ──────────────┐  " << endl;
    cout << "│ Id: " << id_pad << "│ " << endl;
    cout << "│ Nombre: " << name_padded << "│ " << endl;
    cout << "│ Coordinador: " << coordinator_padded << "│ " << endl;
    cout << "│ Indice académico: " << academic_idx_padded << "│" << endl;
    cout << "│ Siguiente: " << next_padded << "│" << endl;
    cout << "└────────────────────────────────────────┘" << endl;
}

string readStr() {
    string value;
    while (!(cin >> value)) {
        cout << "Ingrese un valor válido: ";
        cin.clear();
        cin.ignore(123, '\n');
    }
    cin.ignore(123, '\n');
    return value;
}

int readInt() {
    int value;
    while (!(cin >> value)) {
        cout << "Ingrese un valor válido: ";
        cin.clear();
        cin.ignore(123, '\n');
    }
    cin.ignore(123, '\n');
    return value;
}

void run() {
    displayHashTable();
    while (true) {
        cout << "Seleccione una opción: " << endl;
        cout << "0. Salir" << endl;
        cout << "1. Insertar un estudiante." << endl;
        cout << "2. Buscar un estudiante." << endl;
        cout << "3. Para mostrar la tabla hash." << endl;
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
        case 2:
            //check if empty
            if (!hash_table[0].id) {
                cout << " * Tabla vacía. Inserte un estudiante primero." << endl;
                break;
            }
            cout << "Ingrese el id del estudiante: ";
            studentId = readInt();
            get(studentId);
            break;
        case 3:
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
