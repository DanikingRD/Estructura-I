/*
 * ENUNCIADO: HashTable
 * INTEGRANTES: 1113684 - Clay Manuel Gomera Arias
 *              1114116 - Jean Carlos Araujo Molina
 *              1116906 - Gabriel Mejía Acosta
 *              1114441 - Rafael Eduardo Peralta Pimentel
 *              1114814 - Hadelin Maria García Cedano
 *              1114950 - Elian Gabriel Villegas Báez
 *              1116614 - Luis Daniel de la Cruz García
 *              1116623 - Aquilenyi Suero de los Santos
 * FECHA: 1/09/2023 <== Fecha de realización
 */
#include <iomanip>
#include <iostream>

using namespace std;

struct Student;
int readInt();
string readStr();
Student* createStudent(int studentId, bool idOnly);
void printTable(Student* current, int slot);

int IDS[] = {1115075, 1116614, 1114790, 1113810, 1114116, 1115242, 1116238,
             1113902, 1109094, 1114056, 1114814, 1113684, 1116176, 1087257,
             1116783, 1115079, 1114306, 1116906, 1115419, 1114204, 1115989,
             1115915, 1116733, 1114290, 1113744, 1114441, 1115997, 1114531,
             1115279, 1115395, 1114042, 1114343, 1116842, 1105307, 1113891,
             1116623, 1116351, 1114929, 1114331, 1114950};

const unsigned int TOTAL_ID_COUNT = sizeof(IDS) / sizeof(IDS[0]);

struct Student {
    int id;
    string name;
    string coordinator;
    int academic_idx;
    Student* next;
};

Student table[TOTAL_ID_COUNT] = {};

bool arrayContains(int* arr, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value)
            return true;
    }
    return false;
}

// Regresa un número entre 0 y MAX
int hashFN(int id) { return id % TOTAL_ID_COUNT; };

Student* createStudent(int studentId, bool idOnly) {
    if (idOnly) {
        Student* student = new (Student){
            .id = studentId,
            .next = 0,
        };
        return student;
    }
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

void insertStudent(int studentId, bool idOnly = false) {
    if (!arrayContains(IDS, TOTAL_ID_COUNT, studentId)) {
        cout << "El estudiante con id: " << studentId
             << " no está en el curso.\n";
        return;
    }
    Student* st = 0;
    int bucket = hashFN(studentId);

    if (table[bucket].id) {
        // resolver colisión
        Student* current = &table[bucket];
        while (current->next) {
            current = current->next;
        }
        st = createStudent(studentId, idOnly);
        current->next = st;
    } else {
        // insertar en bucket, no hay colisión
        // será la cabeza de la lista enlazada
        st = createStudent(studentId, idOnly);
        table[bucket] = *st;
    }
    cout << " * Estudiante insertado en slot #" << bucket << endl;
}

void populate() {
    for (int i = 0; i < TOTAL_ID_COUNT; i++) {
        int studentId = IDS[i];
        int index = hashFN(i);
        insertStudent(studentId, true);
    }
}

void displayHashTable() {
    cout << " * Imprimiendo tabla hash..." << endl;
    for (int i = 0; i < TOTAL_ID_COUNT; i++) {
        Student* current = &table[i];
        while (current) {
            printTable(current, i);
            current = current->next;
        }
    }
}

void searchStudent(int studentId) {
    // Resumen de pasos:
    // 1) Hashear el id del estudiante
    // 2) Buscar el bucket correspondiente
    // 3) Recorrer la lista enlazada hasta encontrar el estudiante
    // 4) Imprimir el estudiante
    cout << "Buscando estudiante con Id: " << studentId << endl;
    int bucket = hashFN(studentId);
    Student* st = &table[bucket];
    while (st) {
        if (st->id == studentId) {
            printTable(st, bucket);
            return;
        }
        st = st->next;
    }
    cout << "No se encontró el estudiante con id: " << studentId << endl;
}

string padString(string str, int width) {
    return string(width - str.length(), ' ') + str;
}

void printTable(Student* current, int slot) {

    if (slot > 9)
        cout << "┌─────────────────"
             << " Slot#" << slot << " ──────────────┐" << endl;
    else
        cout << "┌──────────────────"
             << " Slot#" << slot << " ──────────────┐  " << endl;

    string nextPtr = current->next ? to_string(current->next->id) : "null";
    cout << "│ Id: " << padString(to_string(current->id), 35) << "│ " << endl;
    cout << "│ Nombre: " << padString(current->name, 31) << "│ " << endl;
    cout << "│ Coordinador: " << padString(current->coordinator, 26) << "│ "
         << endl;
    cout << "│ Indice académico: "
         << padString(to_string(current->academic_idx), 21) << "│" << endl;
    cout << "│ Siguiente: " << padString(nextPtr, 28) << "│" << endl;
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
    populate();
    displayHashTable();
    while (true) {
        cout << "Seleccione una opción: " << endl;
        cout << "0. Salir" << endl;
        cout << "1. Insertar campos de un estudiante." << endl;
        cout << "2. Buscar un estudiante." << endl;
        cout << "3. Para mostrar la tabla hash." << endl;
        cout << "Opción: ";
        int option = readInt();
        cout << endl;
        bool exit = false;
        switch (option) {
        case 0:
            exit = true;
            break;
        case 1:
            cout << "Ingrese el id del estudiante: ";
            int studentId;
            studentId = readInt();
            insertStudent(studentId);
            break;
        case 2:
            cout << "Ingrese el id del estudiante: ";
            studentId = readInt();
            searchStudent(studentId);
            break;
        case 3:
            displayHashTable();
            break;
        default:
            break;
        }
        if (exit) {
            cout << "Saliendo del programa...\n";
            cout << "Liberando memoria...\n";
            // free memory
            for (int i = 0; i < TOTAL_ID_COUNT; i++) {
                Student* current = table[i].next; 
                while (current) {
                    Student* temp = current; 
                    current = current->next; 
                    delete temp;             
                }
            }
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
