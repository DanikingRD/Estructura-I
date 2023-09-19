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

#ifdef _WIN32 // Check if the code is running on a Windows system
const std::string CLEAR_COMMAND = "cls"; // Windows clear screen command
#else
const std::string CLEAR_COMMAND = "clear"; // UNIX/Linux/Mac clear screen command
#endif

struct Node {
    int value;
    Node* parent;
    Node* left;
    Node* right;

    Node(Node* parent, int value) : parent(parent), value(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;

public:
    BinarySearchTree() : root(nullptr) {}

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
	// Verifica si el árbol contiene un valor dado.
    bool contains(int value) const {
        return contains(root, value);
    }
	// Imprime el árbol.
    void display() const {
        displayTree(root);
    }
	// Recorre e imprime los valores del árbol de manera pre-order
    void printPreOrder() const {
        printPreOrder(root);
    }
	// Recorre e imprime los valores del árbol de manera in-order
    void printInOrder() const {
        printInOrder(root);
    }
	
	// Recorre e imprime los valores del árbol de manera post-order
    void printPostOrder() const {
        printPostOrder(root);
    }
	
	// Verifica si el árbol está vacío.
    bool isEmpty() const {
        return root == nullptr;
    }

private:
    void insert(Node*& node, Node* parent, int value) {
		if (node == nullptr) {
			// Si el nodo es nulo creamos un nuevo nodo.
            node = new Node(parent, value);
            return;
        }
		// Nos movemos hasta encontrar un nodo nulo
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
			// Si el nodo es nulo el valor existe.
            return false;
        }
		// Nos movemos en el arbol.
        if (value < node->value) {
			// Nos movemos hacia la izquierda siempre que tengamos un valor menor
            return remove(node->left, value);
        } else if (value > node->value) {
			// Nos movemos hasta la derecha siempre que tengamos un valor mayor.
            return remove(node->right, value);
        } else {
			// Entrar aqui significa que node->value y value son iguales
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
			// 3. Removemos el nodo a 
            remove(node->right, min->value);
        } else {
			// Caso 2 y 3) - El nodo tiene un sub-árbol derecho o uno izquierdo.
            Node* temp = node;

            if (node->left) {
				// Si tiene un sub-arbol izquierdo hacemos que apunte
				// a su hijo izquierdo.
                node = node->left;
            } else if (node->right) {
				// Si tiene un sub-arbol derecho hacemos que apunte
				// a su hijo derecho.
                node = node->right;
            } else {
				// Si no tiene hijos lo eliminamos.
                node = nullptr;
            }
            delete temp;
        }
    }
	
	// Encuentra el menor valor de un árbol
    Node* findMin(Node* subTree) const {
        if (!subTree || !subTree->left) {
            return subTree;
        }
		// Consiste en desplazarnos a la izquierda hasta
		// que se evalúe en true la condición anterior.
		// Lo cual significa que no hay más nodos la izquierda.
        return findMin(subTree->left);
    }


    bool contains(const Node* node, int value) const {
        if (node == nullptr) {
			// Si el árbol es nulo no tenemos que verificar nada.
            return false;
        }
		// Si encontramos ún numero igual retornamos true.
        if (node->value == value) {
            return true;
			// Nos movemos a la izquierda tantas veces hasta encontrar
			// un numero mayor o igual
        } else if (value < node->value) {
            return contains(node->left, value);
        } else {
			// Nos movemos a la derecha tantas veces hasta encontrar un numero
			// mayor o igual.
            return contains(node->right, value);
        }
    }

    void displayTree(const Node* node, int indent = 0) const {
        if (node == nullptr) {
            return;
        }
        displayTree(node->right, indent + 1);
        for (int level = 0; level < indent; level++) {
            std::cout << "   ";
        }
        std::cout << node->value << std::endl;
        displayTree(node->left, indent + 1);
    }

    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    void printPreOrder(const Node* node) const {
        if (node == nullptr) return;
        std::cout << node->value << " - ";
        printPreOrder(node->left);
        printPreOrder(node->right);
    }

    void printInOrder(const Node* node) const {
        if (node == nullptr) return;
        printInOrder(node->left);
        std::cout << node->value << std::endl;
        printInOrder(node->right);
    }

    void printPostOrder(const Node* node) const {
        if (node == nullptr) return;
        printPostOrder(node->left);
        printPostOrder(node->right);
        std::cout << node->value << " - " << std::endl;
    }
};

int main() {
    std::cout << "Running Binary Search Tree program...\n";
    BinarySearchTree tree;
    bool exit = false;

    while (!exit) {
        std::cout << "Press:\n"
                  << "   0) - Salir del programa.\n"
                  << "   1) - Insertar un elemento en el árbol.\n"
                  << "   2) - Eliminar un elemento del árbol.\n"
                  << "   3) - Verificar si el árbol contiene un valor dado.\n"
                  << "   4) - Imprimir recorrido PreOrden.\n"
                  << "   5) - Imprimir recorrido InOrden.\n"
                  << "   6) - Imprimir recorrido PostOrden.\n"
                  << "   7) - Mostrar el árbol.\n"
                  << "Enter your choice: ";

        int option;
        std::cin >> option;

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
                        std::cout << " * El valor " << value << " si está en el árbol.\n";
                    } else {
                        std::cout << " * El valor " << value << " no está en el árbol.\n";
                    }
                }
                break;
            case 4:
                if (tree.isEmpty()) {
                    std::cout << " * El árbol está vacío. No se puede realizar un recorrido.\n";
                } else {
                    std::cout << "Recorrido PreOrder: ";
                    tree.printPreOrder();
                    std::cout << std::endl;
                }
                break;
            case 5:
                if (tree.isEmpty()) {
					std::cout << " * El árbol está vacío. No se puede realizar un recorrido.\n";
                } else {
                    std::cout << "Recorrido InOrder:\n";
                    tree.printInOrder();
                }
                break;
            case 6:
                if (tree.isEmpty()) {
                    std::cout << " * El árbol está vacío. No se puede realizar un recorrido.\n";
                } else {
                    std::cout << "Recorrido PostOrder: ";
                    tree.printPostOrder();
                    std::cout << std::endl;
                }
                break;
            case 7:
                if (tree.isEmpty()) {
                    std::cout << " * El árbol está vacío. No hay nada que mostrar.\n";
                } else {
                    std::cout << "Mostrándo árbol:\n";
                    tree.display();
                }
                break;
            default:
                std::cout << " * La opción " << option << " no existe. Intenta de nuevo.\n";
                break;
        }

        if (!exit) {
            std::cout << "Presiona Enter para continuar...";
            std::cin.ignore();
            std::cin.get();
            system(CLEAR_COMMAND.c_str()); // Use the clear screen command based on the detected OS
        }
    }
    return 0;
}
