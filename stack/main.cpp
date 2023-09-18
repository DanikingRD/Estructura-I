#include <iostream>

using namespace std;

/*
 * ENUNCIADO: Stack
 * INTEGRANTES: 1113684 - Clay Manuel Gomera Arias
 *              1114116 - Jean Carlos Araujo Molina
 *              1116906 - Gabriel Mejía Acosta
 *              1114441 - Rafael Eduardo Peralta Pimentel
 *              1114814 - Hadelin Maria García Cedano
 *              1114950 - Elian Gabriel Villegas Báez
 *              1116614 - Luis Daniel de la Cruz García
 *              1116623 - Aquilenyi Suero de los Santos
 * FECHA: 05/08/2023 <== Fecha de realización
 */

/*
 * Representa un nodo en la pila.
 *
 * Un nodo se puede visualizar como una caja que contiene
 * un valor y una referencia al siguiente nodo en la pila.
 *
 * +-------+-------+       +-------+-------+
 * | value | next  | ----> | value | next  | ----> ...
 * +-------+-------+       +-------+-------+
 */
struct Node
{
    /// @brief Referencia al siguiente nodo. Puede ser `nullptr`
    Node *next;
    /// @brief Valor almacenado en el nodo.
    int value;
};

/*
 * Representa un `Stack` o pila de datos.
 *
 * El stack almacena los datos en orden LIFO (Last In First Out)
 * haciendo uso de nodos que referencian al siguiente formando una cadena.
 *
 *  - Representación de una pila con 3 elementos:
 *      +-------+
 *      |   3   | valor de next: 2
 *      +-------+
 *      |   2   | valor de next: 1
 *      +-------+
 *      |   1   | valor de next: null
 *      +-------+
 *      |  null |
 *      +-------+
 */
struct Stack
{
private:
    /// @brief  Referencia al nodo en el tope de la pila.
    Node *top;
    /// @brief  Cantidad de elementos en la pila.
    unsigned int length;

public:
    // El constructor crea una pila vacia.
    Stack()
    {
        top = nullptr;
        length = 0;
    }

    /*
     * El método `push` inserta un nuevo elemento en el tope (TOP) de la pila.
     */
    void push(int value)
    {
        // 1) Crear un nuevo nodo
        Node *newNode = new Node();
        // 2) Asignar el valor deseado
        newNode->value = value;
        // 3) Hacer que el nuevo nodo apunte al nodo siguiente.
        // El siguiente nodo será cualquier nodo que haya en el `TOP`
        // al momento de llamar esta funcion.
        newNode->next = this->top;
        // 4) Actualizar el nodo en el TOP.
        this->top = newNode;
        // 5) Incrementar su tamaño
        this->length++;
    }

    /*
     * El método `pop` elimina el elemento en el tope (TOP) de la pila.
     * Si la pila está vacia, no hace nada.
     */
    void pop()
    {
        if (length == 0)
            // Que pasaría si hacemos pop en un stack vacío?
            // segmentation fault >_<
            return;

        // 1) Obtener el siguiente nodo en la pila.
        Node *nextInStack = this->top->next; // Tiene referencia al siguiente elemento del stack
        // 2) Eliminar el nodo actualmente en el TOP
        delete this->top; // borra la memoria de ese nodo
        // 3) Actualizar el nodo en el TOP.
        this->top = nextInStack;
        // Disminuir su tamaño
        this->length--;
    }

    /*
     * El método `peek` retorna el valor del elemento en el tope (TOP) de la pila.
     * O retorna -1 si la pila está vacia.
     */
    int peek()
    {
        if (isEmpty())
        {
            return -1;
        }
        return this->top->value;
    }

    /*
     * `contains` retorna `true` si la pila contiene el valor especificado.
     */
    bool contains(int value)
    {
        Node *index = top;
        while (index != nullptr)
        {
            int nodeValue = index->value;
            if (nodeValue == value)
            {
                return true;
            }
            index = index->next;
        }
        return false;
    }

    /*
     * Retorna la cantidad de elementos en la pila.
     */
    unsigned int size() const
    {
        return this->length;
    }

    /*
     * Retorna `true` si la pila está vacia.
     */
    bool isEmpty() const
    {
        return this->length == 0;
    }

    /*
     * Elimina todos los elementos de la pila, haciendo que esta quede vacia.
     */
    void clear()
    {
        while (!isEmpty())
        {
            pop();
        }
    }
    /*
     * Retorna una representación de la pila en forma de cadena (string).
     */
    string toString()
    {
        if (isEmpty())
        {
            return " * La pila está vacía.\n";
        }

        Node *node = top;
        string stackStr = "[Stack]\n";

        while (node != nullptr)
        {
            stackStr += "  " + to_string(node->value) + "\n";
            node = node->next;
        }
        return stackStr;
    }
};

/*
 * Lee un valor entero. Si el valor ingresado no es un entero,
 * se solicita al usuario que ingrese un valor válido.
 */
void readInt(int &value)
{
    while (!(cin >> value))
    {
        cout << "Ingrese un valor válido: ";
        cin.clear();
        cin.ignore(123, '\n');
    }
}

/*
 * Pide un valor al usuario para insertar en el `Stack`.
 */
void makePush(Stack *stack)
{
    cout << "Ingrese el valor a insertar: ";
    int value;
    readInt(value);
    stack->push(value);
    cout << " * El valor " << value << " ha sido insertado en la pila\n";
    cout << stack->toString() << endl;
}

/*
 * Ejecuta `Pop` en el stack.
 * Luego procede a imprimir los datos disponibles.
 */
void makePop(Stack *stack)
{
    stack->pop();
    cout << stack->toString() << endl;
}

/*
 * Muestra el valor que se encuentra en el tope de la pila.
 */
void showPeek(Stack *stack)
{
    int x = stack->peek();
    if (x == -1)
    {
        cout << " * La pila está vacia.\n";
        return;
    }
    cout << " * El valor más alto de la pila es: " << x << endl;
}

/*
 * Pide un valor al usuario para buscar en el `Stack`.
 * Luego muestra un mensaje indicando si el valor se encuentra o no almacenado.
 */
void checkIfContains(Stack *stack)
{
    int value;
    cout << "Ingrese el valor a buscar: ";
    readInt(value);
    if (stack->contains(value))
    {
        cout << " * El valor " << value << " si se encuentra en la pila\n";
    }
    else
    {
        cout << " * El valor " << value << " no se encuentra en la pila\n";
    }
}

/*
 * Muestra los datos disponibles en el `Stack`.
 */
void showStack(Stack *stack)
{
    cout << stack->toString() << endl;
}

/*
 * Limpia el `Stack`.
 * Luego muestra un mensaje indicando que la pila ha sido limpiada.
 */
void makeClear(Stack *stack)
{
    stack->clear();
    cout << "* La pila ha sido limpiada.\n";
}

/*
 * Muestra la cantidad de elementos en el `Stack`.
 */
void showSize(Stack *stack)
{
    cout << " * La pila tiene " << stack->size() << " elementos.\n";
}

/*
 * Loop principal del programa.
 * Creamos un `Stack` y luego ejecutamos las acciones que el usuario solicite.
 * El loop se repite hasta que el usuario ingrese la opción 0.
 */
void run()
{
    // Instanciamos un nuevo Stack
    Stack *stack = new Stack();
    while (true)
    {
        int option;
        cout << "Presione: \n"
             << "   0) - Para salir del programa.\n"
             << "   1) - Para ingresar un valor a la pila (push).\n"
             << "   2) - Para eliminar un valor de la pila (pop).\n"
             << "   3) - Para obtener el valor más alto de la pila (peek).\n"
             << "   4) - Para verificar si un valor se encuentra en la pila (contains).\n"
             << "   5) - Para mostrar todos los valores de la pila.\n"
             << "   6) - Para limpiar la pila (clear).\n"
             << "   7) - Para mostrar el tamaño de la pila. (size)\n"
             << "Ingrese su opción: ";
        readInt(option);
        cout << endl;

        switch (option)
        {
        case 0:
            cout << "Saliendo del programa...\n";
            exit(0);
            break;
        case 1:
            makePush(stack);
            break;
        case 2:
            makePop(stack);
            break;
        case 3:
            showPeek(stack);
            break;
        case 4:
            checkIfContains(stack);
            break;
        case 5:
            showStack(stack);
            break;
        case 6:
            makeClear(stack);
            break;
        case 7:
            showSize(stack);
            break;
        default:
            cout << "La opcion " << option << " no existe.\n";
            break;
        }
    }
    delete stack; // Liberamos la memoria del stack
}

int main(int argc, char const *argv[])
{
    cout << "Bienvenido al programa de pilas\n";
    run();
    return 0;
}
