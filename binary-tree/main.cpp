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

    void insert(int value) {
        insert(root, nullptr, value);
    }

    bool remove(int value) {
        return remove(root, value);
    }

    bool contains(int value) const {
        return contains(root, value);
    }

    void display() const {
        displayTree(root);
    }

    void printPreOrder() const {
        printPreOrder(root);
    }

    void printInOrder() const {
        printInOrder(root);
    }

    void printPostOrder() const {
        printPostOrder(root);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

private:
    void insert(Node*& node, Node* parent, int value) {
        if (node == nullptr) {
            node = new Node(parent, value);
            return;
        }
        if (value < node->value) {
            insert(node->left, node, value);
        } else {
            insert(node->right, node, value);
        }
    }

    bool remove(Node*& node, int value) {
        if (node == nullptr) {
            return false;
        }
        if (value < node->value) {
            return remove(node->left, value);
        } else if (value > node->value) {
            return remove(node->right, value);
        } else {
            removeNode(node);
            return true;
        }
    }

    void removeNode(Node*& node) {
        if (node->left && node->right) {
            Node* min = findMin(node->right);
            node->value = min->value;
            remove(node->right, min->value);
        } else {
            Node* temp = node;
            if (node->left) {
                node = node->left;
            } else if (node->right) {
                node = node->right;
            } else {
                node = nullptr;
            }
            delete temp;
        }
    }

    Node* findMin(Node* subTree) const {
        if (!subTree || !subTree->left) {
            return subTree;
        }
        return findMin(subTree->left);
    }

    bool contains(const Node* node, int value) const {
        if (node == nullptr) {
            return false;
        }
        if (node->value == value) {
            return true;
        } else if (value < node->value) {
            return contains(node->left, value);
        } else {
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
                  << "   0) - Exit the program.\n"
                  << "   1) - Insert a value into the tree.\n"
                  << "   2) - Remove an element from the tree.\n"
                  << "   3) - Check if the tree contains a value.\n"
                  << "   4) - Print PreOrder traversal.\n"
                  << "   5) - Print InOrder traversal.\n"
                  << "   6) - Print PostOrder traversal.\n"
                  << "   7) - Display the tree.\n"
                  << "Enter your choice: ";

        int option;
        std::cin >> option;

        switch (option) {
            case 0:
                exit = true;
                break;
            case 1:
                int value;
                std::cout << "Enter the value to insert: ";
                std::cin >> value;
                tree.insert(value);
                std::cout << " * Value " << value << " has been inserted.\n";
                break;
            case 2:
                std::cout << "Enter the value to remove: ";
                std::cin >> value;
                if (tree.remove(value)) {
                    std::cout << " * Value " << value << " has been removed.\n";
                } else {
                    std::cout << " * Value " << value << " was not found in the tree.\n";
                }
                break;
            case 3:
                if (tree.isEmpty()) {
                    std::cout << " * The tree is empty. Nothing to check.\n";
                } else {
                    std::cout << "Enter the value to check: ";
                    std::cin >> value;
                    if (tree.contains(value)) {
                        std::cout << " * Value " << value << " is in the tree.\n";
                    } else {
                        std::cout << " * Value " << value << " is not in the tree.\n";
                    }
                }
                break;
            case 4:
                if (tree.isEmpty()) {
                    std::cout << " * The tree is empty. Cannot perform traversal.\n";
                } else {
                    std::cout << "PreOrder Traversal: ";
                    tree.printPreOrder();
                    std::cout << std::endl;
                }
                break;
            case 5:
                if (tree.isEmpty()) {
                    std::cout << " * The tree is empty. Cannot perform traversal.\n";
                } else {
                    std::cout << "InOrder Traversal:\n";
                    tree.printInOrder();
                }
                break;
            case 6:
                if (tree.isEmpty()) {
                    std::cout << " * The tree is empty. Cannot perform traversal.\n";
                } else {
                    std::cout << "PostOrder Traversal: ";
                    tree.printPostOrder();
                    std::cout << std::endl;
                }
                break;
            case 7:
                if (tree.isEmpty()) {
                    std::cout << " * The tree is empty. Nothing to display.\n";
                } else {
                    std::cout << "Displaying the tree:\n";
                    tree.display();
                }
                break;
            default:
                std::cout << " * Option " << option << " does not exist. Please try again.\n";
                break;
        }

        if (!exit) {
            std::cout << "Press Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            system(CLEAR_COMMAND.c_str()); // Use the clear screen command based on the detected OS
        }
    }
    return 0;
}