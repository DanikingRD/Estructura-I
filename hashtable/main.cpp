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
Student* createStudent(int studentId);
void updateStudent(Student* student);
void printTable(Student* current, int slot);

int ID_LIST[] = {1115075, 1116614, 1114790, 1113810, 1114116, 1115242, 1116238,
             1113902, 1109094, 1114056, 1114814, 1113684, 1116176, 1087257,
             1116783, 1115079, 1114306, 1116906, 1115419, 1114204, 1115989,
             1115915, 1116733, 1114290, 1113744, 1114441, 1115997, 1114531,
             1115279, 1115395, 1114042, 1114343, 1116842, 1105307, 1113891,
             1116623, 1116351, 1114929, 1114331, 1114950};

const unsigned int ID_COUNT = sizeof(ID_LIST) / sizeof(ID_LIST[0]);

struct Student {
    int id;
    string name;
    string coordinator;
    int academic_idx;
    Student* next;
};

// Tabla hash
Student table[ID_COUNT] = {};

/*
 * Verifica si un arreglo de enteros contiene un valor dado. 
*/
bool arrayContains(int* arr, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value)
            return true;
    }
    return false;
}

/**
 * Crea un nuevo estudiante con el id dado.
 * y valores por defecto para los demás campos.
*/
Student* createStudent(int studentId) {
    Student *student = new Student();
    student->id = studentId;
    student->next = 0;
    return student;
}

/*
* Función hash de la tabla hash.
* Esta implementacion hace uso del modulo 
* para obtener el bucket correspondiente.
*/
int hashFN(int id) { return id % ID_COUNT; };


/*
* Inserta un estudiante en la tabla hash.
* También se encarga de resolver colisiones,
* mediante el uso de listas enlazadas.
*/
void insert(int studentId) {
    if (!arrayContains(ID_LIST, ID_COUNT, studentId)) {
        cout << "El estudiante con id: " << studentId
             << " no está en el curso.\n";
        return;
    }
    Student* newStudent = 0;
    int bucket = hashFN(studentId);

    if (table[bucket].id) {
        // resolver colisión
        Student* current = &table[bucket];
        while (current->next) {
             current = current->next;
        }
        newStudent = createStudent(studentId);
        current->next = newStudent;
    } else {
        // insertar directamente, no hay colisión
        // será la cabeza de la lista enlazada
        newStudent = createStudent(studentId);
        table[bucket] = *newStudent;
    }
    cout << " * Estudiante insertado en slot #" << bucket << endl;
}

/*
* Llena la tabla hash con los ids de los estudiantes.
*/
void populateTable() {
    for (int i = 0; i < ID_COUNT; i++) {
        insert(ID_LIST[i]);
    }
}

/*
 * Busca un estudiante en la tabla hash para actualizar sus campos.
*/
void update(int studentId) {
    if (!arrayContains(ID_LIST, ID_COUNT, studentId)) {
        cout << "El estudiante con id: " << studentId
             << " no está en el curso.\n";
        return;
    }
    int bucket = hashFN(studentId);
    Student* student = &table[bucket];
    while (student) {
        if (student->id == studentId) {
            cout << " * Estudiante encontrado en slot #" << bucket << endl;
            updateStudent(student);
            return;
        }
        student = student->next;
    }
}

/*
* Actualiza los campos de un estudiante.
*/
void updateStudent(Student* student) {
    cout << "Ingrese el nombre del estudiante: ";
    string name = readStr();
    cout << "Ingrese el nombre del coordinador: ";
    string coordinator = readStr();
    cout << "Ingrese el indice académico del estudiante: ";
    int academic_idx = readInt();
    student->name = name;
    student->coordinator = coordinator;
    student->academic_idx = academic_idx;
}

void displayHashTable() {
    cout << " * Imprimiendo tabla hash..." << endl;
    for (int i = 0; i < ID_COUNT; i++) {
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

// ----------------------  Funciones no relacionadas a la tabla hash ----------------------
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


void run() {
    populateTable();
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
            update(studentId);
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
            for (int i = 0; i < ID_COUNT; i++) {
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
