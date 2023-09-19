/*
 * ENUNCIADO: Árbol de Búsqueda Binario 
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
#include <limits>

#ifdef _WIN32 // Detectar si esta corriendo en un sistema windows
const std::string CLEAR_COMMAND = "cls"; // Usar el comando cls para limpiar la pantalla en Windows
#else
const std::string CLEAR_COMMAND = "clear"; // Usar el comando clear para limpiar la pantalla en sistemas UNIX
#endif

// Definición de la estructura Node (Nodo)
struct Node {
    int value;     // Valor almacenado en el nodo
    Node* parent;  // Nodo padre
    Node* left;    // Nodo hijo izquierdo
    Node* right;   // Nodo hijo derecho

    // Método constructor del nodo
    Node(Node* parent, int value) : parent(parent), value(value), left(nullptr), right(nullptr) {}
};

// Definición de la clase BinarySearchTree (Árbol Binario de Búsqueda)
class BinarySearchTree {
private:
    Node* root; // Raíz del árbol

public:
    // Método constructor de la clase BinarySearchTree
    BinarySearchTree() : root(nullptr) {}

    // Método destructor de la clase BinarySearchTree, responsable de liberar memoria
    ~BinarySearchTree() {
        destroyTree(root);
    }

    // Insertar un valor al árbol.
    void insert(int value) {
        insert(root, nullptr, value);
    }

    // Eliminar un valor del árbol.
    bool remove(int value) {
        return remove(root, value);
    }

    // Verificar si el árbol contiene un valor dado.
    bool contains(int value) const {
        return contains(root, value);
    }

    // Imprimir el árbol.
    void display() const {
        displayTree(root);
    }

    // Recorrer e imprimir los valores del árbol en preorden.
    void printPreOrder() const {
        printPreOrder(root);
    }

    // Recorrer e imprimir los valores del árbol en orden.
    void printInOrder() const {
        printInOrder(root);
    }

    // Recorrer e imprimir los valores del árbol en postorden.
    void printPostOrder() const {
        printPostOrder(root);
    }

    // Verificar si el árbol está vacío.
    bool isEmpty() const {
        return root == nullptr;
    }

private:
    void insert(Node*& node, Node* parent, int value) {
        if (node == nullptr) {
            // Si el nodo es nulo, creamos un nuevo nodo.
            node = new Node(parent, value);
            return;
        }
        // Nos movemos hasta encontrar un nodo nulo.
        if (value < node->value) {
            // Los valores menores al padre van a la izquierda.
            insert(node->left, node, value);
        } else {
            // Los valores mayores al padre van a la derecha.
            insert(node->right, node, value);
        }
    }

    bool remove(Node*& node, int value) {
        if (node == nullptr) {
            // Si el nodo es nulo, el valor no existe.
            return false;
        }
        // Nos movemos en el árbol.
        if (value < node->value) {
            // Nos movemos hacia la izquierda siempre que tengamos un valor menor.
            return remove(node->left, value);
        } else if (value > node->value) {
            // Nos movemos hacia la derecha siempre que tengamos un valor mayor.
            return remove(node->right, value);
        } else {
            // Entrar aquí significa que node->value y value son iguales,
            // vamos a removerlo.
            removeNode(node);
            return true;
        }
    }

    void removeNode(Node*& node) {
        // Caso 1) - El nodo tiene dos subárboles.
        if (node->left && node->right) {
            // 1. Encontramos el mínimo luego de habernos desplazado a la derecha.
            Node* min = findMin(node->right);
            // 2. Reemplazamos el valor del nodo padre con el nuevo valor.
            node->value = min->value;
            // 3. Removemos el nodo mínimo.
            remove(node->right, min->value);
        } else {
            // Caso 2 y 3) - El nodo tiene un subárbol derecho o uno izquierdo.
            if (node->left) {
                // Si tiene un subárbol izquierdo, hacemos que apunte
                // a su hijo izquierdo.
                node = node->left;
            } else if (node->right) {
                // Si tiene un subárbol derecho, hacemos que apunte
                // a su hijo derecho.
                node = node->right;
            } else {
                // Si no tiene hijos, lo eliminamos.
                node = nullptr;
            }
        }
    }

    // Encuentra el menor valor de un árbol
    Node* findMin(Node* subTree) const {
        if (!subTree || !subTree->left) {
            return subTree;
        }
        // Consiste en desplazarnos a la izquierda hasta
        // que se evalúe en true la condición anterior,
        // lo cual significa que no hay más nodos a la izquierda.
        return findMin(subTree->left);
    }

    // Método que busca si un valor se encuentra en el arbol
    bool contains(const Node* node, int value) const {
        if (node == nullptr) {
            // Si el árbol es nulo, no tenemos que verificar nada.
            return false;
        }
        // Si encontramos un número igual, retornamos true.
        if (node->value == value) {
            return true;
        } else if (value < node->value) {
            // Nos movemos a la izquierda tantas veces como sea necesario
            // hasta encontrar un número mayor o igual.
            return contains(node->left, value);
        } else {
            // Nos movemos a la derecha tantas veces como sea necesario
            // hasta encontrar un número mayor o igual.
            return contains(node->right, value);
        }
    }

    // Método que muestra el árbol en forma visual con indentación.
    // Utiliza un recorrido inverso en orden (derecha, raíz, izquierda) para imprimirlo de manera ordenada.
    void displayTree(const Node* node, int indent = 0) const {
        if (node == nullptr) {
            return; // Si el nodo es nulo, no hay nada que mostrar.
        }

        // Primero, llamamos recursivamente a la función con el hijo derecho (mayor valor).
        displayTree(node->right, indent + 1);

        // Luego, imprimimos espacios en blanco para la indentación.
        for (int level = 0; level < indent; level++) {
            std::cout << "   ";
        }

        // Después, imprimimos el valor del nodo actual.
        std::cout << node->value << std::endl;

        // Finalmente, llamamos recursivamente a la función con el hijo izquierdo (menor valor).
        displayTree(node->left, indent + 1);
    }

    // Método que destruye un árbol liberando la memoria de todos los nodos.
    void destroyTree(Node* node) {
        if (node) {
            // Si el nodo no es nulo, llamamos recursivamente a la función para los hijos izquierdo y derecho.
            destroyTree(node->left);
            destroyTree(node->right);
            // Luego, liberamos la memoria del nodo actual.
            delete node;
        }
    }

    // Método para imprimir el árbol en preorden (raíz, izquierda, derecha).
    void printPreOrder(const Node* node) const {
        if (node == nullptr) return; // Si el nodo es nulo, no hacemos nada.

        // Primero, imprimimos el valor del nodo actual.
        std::cout << node->value << " - ";

        // Luego, llamamos recursivamente a la función para el hijo izquierdo y el hijo derecho.
        printPreOrder(node->left);
        printPreOrder(node->right);
    }

    // Método para imprimir el árbol en orden (izquierda, raíz, derecha).
    void printInOrder(const Node* node) const {
        if (node == nullptr) return; // Si el nodo es nulo, no hacemos nada.

        // Primero, llamamos recursivamente a la función para el hijo izquierdo.
        printInOrder(node->left);

        // Luego, imprimimos el valor del nodo actual.
        std::cout << node->value << std::endl;

        // Finalmente, llamamos recursivamente a la función para el hijo derecho.
        printInOrder(node->right);
    }

    // Método para imprimir el árbol en postorden (izquierda, derecha, raíz).
    void printPostOrder(const Node* node) const {
        if (node == nullptr) return; // Si el nodo es nulo, no hacemos nada.

        // Primero, llamamos recursivamente a la función para el hijo izquierdo y el hijo derecho.
        printPostOrder(node->left);
        printPostOrder(node->right);

        // Luego, imprimimos el valor del nodo actual, seguido de un guión y una nueva línea.
        std::cout << node->value << " - " << std::endl;
    }

};

int main() {
    std::cout << "Ejecutando programa de Árbol Binario de Búsqueda...\n";
    BinarySearchTree tree;
    bool exit = false;

    while (!exit) {
        std::cout << "Presiona:\n"
                  << "   0) - Salir del programa.\n"
                  << "   1) - Insertar un elemento en el árbol.\n"
                  << "   2) - Eliminar un elemento del árbol.\n"
                  << "   3) - Verificar si el árbol contiene un valor dado.\n"
                  << "   4) - Imprimir recorrido PreOrden.\n"
                  << "   5) - Imprimir recorrido InOrden.\n"
                  << "   6) - Imprimir recorrido PostOrden.\n"
                  << "   7) - Mostrar el árbol.\n"
                  << "Ingresa tu elección: ";

        int option;
        std::cin >> option;

        if (std::cin.fail()) {
            std::cin.clear(); // Limpiamos el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignoramos el resto de la entrada inválida
            std::cout << "Entrada inválida. Por favor ingresa un número entero.\n";
            continue; // Volvemos al inicio del bucle
        }

        switch (option) {
            case 0:
                exit = true;
                break;
            case 1:
                int value;
                std::cout << "Ingresa el valor a insertar: ";
                std::cin >> value;
                tree.insert(value);
                std::cout << " * El valor " << value << " ha sido insertado.\n";
                break;
            case 2:
                std::cout << "Ingresa el valor a eliminar: ";
                std::cin >> value;
                if (tree.remove(value)) {
                    std::cout << " * El valor " << value << " ha sido eliminado.\n";
                } else {
                    std::cout << " * El valor " << value << " no se encuentra en el árbol.\n";
                }
                break;
            case 3:
                if (tree.isEmpty()) {
                    std::cout << " * El árbol está vacío. No hay nada que revisar.\n";
                } else {
                    std::cout << "Ingresa el valor a revisar: ";
                    std::cin >> value;
                    if (tree.contains(value)) {
                        std::cout << " * El valor " << value << " sí está en el árbol.\n";
                    } else {
                        std::cout << " * El valor " << value << " no está en el árbol.\n";
                    }
                }
                break;
            case 4:
                if (tree.isEmpty()) {
                    std::cout << " * El árbol está vacío. No se puede realizar un recorrido.\n";
                } else {
                    std::cout << "Recorrido PreOrden: ";
                    tree.printPreOrder();
                    std::cout << std::endl;
                }
                break;
            case 5:
                if (tree.isEmpty()) {
                    std::cout << " * El árbol está vacío. No se puede realizar un recorrido.\n";
                } else {
                    std::cout << "Recorrido InOrden:\n";
                    tree.printInOrder();
                }
                break;
            case 6:
                if (tree.isEmpty()) {
                    std::cout << " * El árbol está vacío. No se puede realizar un recorrido.\n";
                } else {
                    std::cout << "Recorrido PostOrden: ";
                    tree.printPostOrder();
                    std::cout << std::endl;
                }
                break;
            case 7:
                if (tree.isEmpty()) {
                    std::cout << " * El árbol está vacío. No hay nada que mostrar.\n";
                } else {
                    std::cout << "Mostrando árbol:\n";
                    tree.display();
                }
                break;
            default:
                std::cout << " * La opción " << option << " no existe. Inténtalo de nuevo.\n";
                break;
        }

        if (!exit) {
            std::cout << "Presiona Enter para continuar...";
            std::cin.ignore();
            std::cin.get();
            system(CLEAR_COMMAND.c_str()); // Usar el comando clear o cls dependiendo del sistema operativo
        }
    }
    return 0;
}
