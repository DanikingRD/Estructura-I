/*
 * ENUNCIADO: Queue
 * INTEGRANTES: 1113684 - Clay Manuel Gomera Arias
 *              1114116 - Jean Carlos Araujo Molina
 *              1116906 - Gabriel Mejía Acosta
 *              1114441 - Rafael Eduardo Peralta Pimentel
 *              1114814 - Hadelin Maria García Cedano
 *              1114950 - Elian Gabriel Villegas Báez
 *              1116614 - Luis Daniel de la Cruz García
 *              1116623 - Aquilenyi Suero de los Santos
 * FECHA: 29/08/2023 <== Fecha de realización
 */

#include <iostream>

using namespace std;

struct Node
{
    Node *next;
    int value;
    int priority;
};

struct PriorityQueue
{
private:
    // Puntero al primer elemento en la cola
    Node *head;
    // Puntero al ultimo elemento en la cola
    Node *tail;
    // Cantidad de elementos en la cola
    unsigned int length;

    static const unsigned int defaultPriority = 16;

public:
    PriorityQueue()
    {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    void enqueue(int value, unsigned int priority = defaultPriority)
    {

        Node *node = new Node();
        node->value = value;
        node->priority = priority;
        node->next = nullptr;

        if (priority > defaultPriority)
        {
            // Asignar prioridad por defecto
            node->priority = defaultPriority;
        }

        // Si la cola esta vacía cola y cabeza deben apuntar al nuevo nodo.
        if (isEmpty())
        {
            head = node;
            tail = node;
        }
        else
        {
            // Si la prioridad de la cabeza es mayor a la prioridad del nuevo nodo
            // ej: head->priority = 5, priority = 3
            if (head->priority > priority)
            {
                // En este caso nodo siguiente va a ser la cabeza actual
                node->next = head;
                // El nuevo nodo se convierte en la cabeza de la cola
                head = node;
            }
            else
            {
                // Nodo auxiliar para recorrer la cola
                Node *i = head;
                // Nos movemos a traves de la cola hasta encontrar el ultimo nodo con prioridad menor o igual a la del nuevo nodo
                while (i->next != nullptr && i->next->priority <= priority)
                {
                    i = i->next;
                }
                // Al salir del ciclo, front apunta al lugar donde debe ir el nuevo nodo.
                // Ejemplo:
                // Value: 12 23 33 41
                // Prior: 1  5  5  6
                // Si llamamos Push(100, 5), el nuevo nodo debe ir entre el nodo 33 y el nodo 41
                // en este caso front apuntaria al nodo 33.
                node->next = i->next; // Le asignamos su siguiente nodo al nuevo nodo.
                // Al nodo 33 le asignamos como siguiente nodo al nuevo nodo.
                i->next = node;
                // Por último el nuevo nodo se coloca en su posición correspondiente.
                // Al finalizar el ejemplo, la cola quedaria asi:
                // Value: 12 23 33 100 41
                // Prior: 1  5  5   5  6
                // actualizar puntero de cola
                if (node->next == nullptr)
                {
                    tail = node;
                }
            }
        }
        length++;
    }

    /*
     * Elimina un elemento en la cabeza de la cola.
     * Retorna el valor del elemento eliminado.
     */
    int dequeue()
    {
        // Si la cola esta vacía no hacemos nada
        if (isEmpty())
        {
            return -1;
        }
        // Guardamos la referencia a la cabeza actual
        Node *prevHead = head;
        // La cabeza pasa a ser el siguiente nodo
        head = head->next;

        // Si el siguiente nodo es nulo, significa que la cola esta vacía
        if (head == nullptr)
        {
            // Por lo tanto la cola esta vacía y la cola pasa a ser nula
            tail = nullptr;
        }
        // Almacenar el valor antes de eliminar el nodo
        int value = prevHead->value;
        // Eliminamos el nodo que era la cabeza
        length--;
        delete prevHead;
        return value;
    }

    /*
     * Indica si la cola esta vacía.
     */
    bool isEmpty() const
    {
        return length == 0;
    }

    /*
     * Devuelve la cantidad de elementos en la cola.
     */
    unsigned int size() const
    {
        return length;
    }

    /*
     * Devuelve el valor del primer elemento en la cola.
     */
    int top() const
    {
        return head->value;
    }

    /*
     * Devuelve el valor del ultimo elemento en la cola.
     */
    int bottom() const
    {
        return tail->value;
    }

    /*
     * Elimina todos los elementos de la cola.
     */
    void clear()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }

    string toString()
    {
        if (isEmpty())
        {
            return "* La cola esta vacía.";
        }
        cout << endl;
        cout << "-------------------" << endl;
        string result = "Value\t  Priority\n";
        Node *front = head;
        while (front != nullptr)
        {
            result += to_string(front->value) + "\t      " + to_string(front->priority) + "\n";
            front = front->next;
        }
        result += "-------------------";
        return result;
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

void makeEnqueue(PriorityQueue *queue)
{
    int value;
    cout << "Ingrese el valor a agregar: ";
    readInt(value);
    queue->enqueue(value);
    cout << " * El valor " << value << " ha sido agregado a la cola." << endl;
    cout << queue->toString() << endl;
}

void makeEnqueueWithPriority(PriorityQueue *queue)
{
    int value, priority;
    cout << "Ingrese el valor a agregar: ";
    readInt(value);
    cout << "Ingrese la prioridad del valor: ";
    readInt(priority);
    if (priority < 0)
    {
        cout << " * La prioridad no puede ser negativa." << endl;
        return;
    }
    queue->enqueue(value, priority);
    cout << " * El valor " << value << ", con prioridad " << priority << " ha sido agregado a la cola." << endl;
    cout << queue->toString() << endl;
}

void makeDequeue(PriorityQueue *queue)
{
    if (queue->isEmpty())
    {
        cout << " * La cola esta vacía." << endl;
        return;
    }
    int value = queue->dequeue();
    cout << "* El valor " << value << " ha sido eliminado de la cola." << endl;
    cout << queue->toString() << endl;
}
void makeClear(PriorityQueue *queue)
{
    queue->clear();
    cout << " * La cola ha sido limpiada." << endl;
}

void showSize(PriorityQueue *queue)
{
    cout << " * El tamaño de la cola es: " << queue->size() << endl;
}

void showHead(PriorityQueue *queue)
{
    if (queue->isEmpty())
    {
        cout << " * La cola esta vacía." << endl;
        return;
    }
    cout << " * El primer elemento de la cola es: " << queue->top() << endl;
}

void showTail(PriorityQueue *queue)
{
    if (queue->isEmpty())
    {
        cout << " * La cola esta vacía." << endl;
        return;
    }
    cout << " * El último elemento de la cola es: " << queue->bottom() << endl;
}

void run()
{
    PriorityQueue *queue = new PriorityQueue();

    while (true)
    {
        int option;
        cout << "Presione: \n"
             << "   0. Para salir del programa\n"
             << "   1. Para agregar un elemento a la cola (enqueue)\n"
             << "   2. Para agregar un elemento a la cola con prioridad (enqueue)\n"
             << "   3. Para eliminar un elemento de la cola (dequeue)\n"
             << "   4. Para limpiar la cola (clear)\n"
             << "   5. Para mostrar el tamaño de la cola (size)\n"
             << "   6. Para mostrar el primer elemento de la cola (head)\n"
             << "   7. Para mostrar el ultimo elemento de la cola (tail)\n"
             << "   8. Para mostrar la cola (toString)\n"
             << "Ingrese su opción: ";
        readInt(option);

        switch (option)
        {
        case 0:
            cout << "Saliendo del programa..." << endl;
            exit(0);
            break;
        case 1:
            makeEnqueue(queue);
            break;
        case 2:
            makeEnqueueWithPriority(queue);
            break;
        case 3:
            makeDequeue(queue);
            break;
        case 4:
            makeClear(queue);
            break;
        case 5:
            showSize(queue);
            break;
        case 6:
            showHead(queue);
            break;
        case 7:
            showTail(queue);
            break;
        case 8:
            cout << queue->toString() << endl;
            break;
        default:
            cout << "La opción " << option << " no existe.\n";
            break;
        }
    }
    delete queue;
}

int main(int argc, char const *argv[])
{
    cout << "Bienvenido al programa de Colas" << endl;
    run();

    return 0;
}