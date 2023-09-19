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
	
	void insert(int value) {
		this->insert(this->root, value);
	}

	// Insertar un valor al árbol.
	void insert(Node*& node, int value) {
		if (node == nullptr) {
			// Si el arbol está vacío, crea el nodo raíz.
			node = new Node(value);
			return;
		}
		if (value < node->value) {
			insert(node->left, value);
		} else {
			insert(node->right, value);
		}
	}

	
	static void traversePreOrder(Node* node) {
		if (node == nullptr) return;
		// 1. Visit the root.
		// 2. Traverse the left-side of the sub tree
		// 3. Traverse the right-side of the sub tree
		cout << node->value << " - ";
		traversePreOrder(node->left);
		traversePreOrder(node->right);
	}

	static void traverseInOrder(Node* node) {
		// 1. Traverse the left-side of the sub-tree
		// 2. Visit the root.
		// 3. Traverse the right-side of the tree.
		if (node == nullptr) return;
		traverseInOrder(node->left);
		cout << node->value << endl;
		traverseInOrder(node->right);
	}

	static void traversePostOrder(Node* node) {
		// 1. Traverse the left-side of the sub-tree
		// 2. Traverse the right-side of the sub-tree
		// 3. Visit the root.
		if (node == nullptr) return;
		traversePostOrder(node->left);
		traversePostOrder(node->right);
		cout << node->value << " - " << "\n";
	}


	bool contains(int value) {
		return this->contains(this->root, value);
	}

	bool contains(Node*& node, int value) {
		if (node == nullptr) return false;
		if (node->value == value) {
			return true;
		} else if (value < node->value) {
			return contains(node->left, value);
		} else {
			return contains(node->right, value);
		}
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

	void display() {
		displayTree(this->root);
	}

	void displayTree(Node* node, int indent = 0) {
		if (node == nullptr) {
			return;
		}
		displayTree(node->right, indent + 1);
		for (int level = 0; level < indent; level++) {
			cout << "    ";
		}
		cout << node->value << "\n";
		displayTree(node->left, indent + 1);
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
	tree->insert(data);
	printf(" * El valor %d ha sido insertado.\n", data);
}

void checkValue(BinarySearchTree* tree) {
	cout << "Ingrese el valor a buscar: ";
	int data = readInt();
	if (tree->contains(data)) {
		printf("El valor %d si se encuentra en el árbol\n", data);
	} else {
		printf("El valor %d no se encuentra en el árbol\n", data);
	}
	
}
void run() {
	BinarySearchTree* tree = new BinarySearchTree();
	bool exit;
	int option;

	while (true) {
		cout << "Presione: \n"
         << "   0) - Para salir del programa.\n"
         << "   1) - Para ingresar un valor al árbol (insert).\n"
		 << "   2) - Para eliminar un elemento del árbol (remove)\n"
		 << "   3) - Para verificar si el árbol contiene un valor (contains).\n"
		 << "   4) - Para hacer un reccorido en PreOrden\n"
		 << "   5) - Para hacer un recorrido en InOrden\n"
		 << "   6) - Para hacer un recorrido en PostOrden\n"
         << "Ingrese su opción: ";
		
		option = readInt();

		switch (option) {
			case 0:
				exit = true;
				break;
			case 1:
				makeInsert(tree);
				break;
			case 2:
				checkValue(tree);
				break;
			default:
				printf(" * La opción %d no existe. Intente de nuevo.", option);
				break;
		}

		tree->display();

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
