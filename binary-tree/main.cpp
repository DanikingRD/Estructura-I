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

using namespace std;

struct Node { 
	int value;
	Node* left;
	Node* right;
	
	Node(int value) {
		this->value = value;
		this->left = nullptr;
		this->right = nullptr;
	}
};


struct BinarySearchTree {
	Node* root;
public:
	BinarySearchTree() {
		this->root = nullptr;
	}

	// Insertar un valor al árbol.
	void insert(Node* node, int value) {
		if (node == nullptr) {
			// Si el arbol está vacío, crea el nodo raíz.
			this->root = new Node(value);
			return;
		}
		if (value < node->value) {
			insert(node->left, value);
		} else {
			insert(node->right, value);
		}
	}

	void displayTree(Node* side, int index) {
		if (isEmpty()) return;
		
		// primero imprime el lado derecho
		displayTree(side->right, index + 1);

		for (int i = 0; i < index; i++) {
			cout << "<< >>";
		}
		cout << side->value << "\n";

	}

	int leftValue() {
		return this->root->left->value;
	}

	int rightValue() {
		return this->root->right->value;
	}

	bool isEmpty() {
		return this->root == nullptr;
	}
};
int readInt() {
  	int value;
  	while (!(cin >> value)) {
		cout << "Ingrese un valor válido: ";
    	cin.clear();
    	cin.ignore(123, '\n');
	}
	return value;
}

void makeInsert(BinarySearchTree* tree) {
	cout << "Ingrese el valor a insertar: ";
	int data = readInt();
	tree->insert(tree->root, data);
	cout << " * El valor " << data << " ha sido insertado.\n";
}
void run() {
	
	BinarySearchTree* tree = new BinarySearchTree();
	bool exit;
	int option;

	while (true) {
		cout << "Presione: \n"
         << "   0) - Para salir del programa.\n"
         << "   1) - Para ingresar un elemento al árbol (insert).\n"
         << "Ingrese su opción: ";
		
		option = readInt();

		switch (option) {
			case 0:
				exit = true;
				break;
			case 1:
				makeInsert(tree);
				break;
			default: 
				break;
		}

		if (exit) {
			delete tree;
			break;
		}
	}

}

int main(void) {
	cout << "Corriendo programa árboles de búsqueda...\n";
	run();
	return 0;
}
