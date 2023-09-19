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
	Node* parent;
	Node* left;
	Node* right;
	Node(Node* parent, int value) {
		this->parent = parent;
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
		this->insert(this->root, NULL, value);
	}

	// Insertar un valor al árbol.
	void insert(Node*& node, Node* parent, int value) {
		if (node == nullptr) {
			// Si el arbol está vacío, crea el nodo raíz.
			node = new Node(parent, value);
			return;
		}
		if (value < node->value) {
			insert(node->left, parent, value);
		} else {
			insert(node->right, parent, value);
		}
	}

	bool remove(int value) {
		return this->remove(this->root, value);
	}

	bool remove(Node*& node, int value) {
		if (node == nullptr) return false;
		if (value < node->value) {  
			// muevete al siguiente nodo por la izquierda.
			remove(node->left, value);
		} else if (value > node->value) {
			// muevete a al siguiente nodo por la derecha.
			remove(node->right, value);
		} else {
			remove(node);
		}
		return true;
	}

	void remove(Node* node) {
		if (node->left && node->right) {
			// Caso 1: arbol con 2 hijos
			// Primero buscamos el nodo derecho
			// Luego buscanos el minimo valor a partir de ahi.
			Node* min = BinarySearchTree::findMin(node->right);
			node->value = min->value;
			remove(min);
		} else if (node->left) {
			// Caso 2: Borrar nodo con solo 1 sub-arbol hijo
			replaceNode(node, node->left);
			destroyNode(node);
		} else if (node->right) {
			replaceNode(node, node->right);
			destroyNode(node);
		} else {
			// replaceNode(node, nullptr);
			destroyNode(node);
		}
	}

	static void destroyNode(Node*&node) {
		node->left = nullptr;
		node->right = nullptr;
		// cout << " At the moment of deleteNode address of root is " << node << endl;
		delete node;
		node = NULL;
	}
	
	static void replaceNode(Node* target, Node* newNode) {
		if (target->parent) {
			if (target->value == target->parent->left->value) {
				// Eliminar el nodo izquierdo
				target->parent->left = newNode;
				
			} else if (target->value == target->parent->right->value) {
				// Eliminar el nodo derecho
				target->parent->right = newNode;
			}
		}
		if (newNode) {
			// asignar nuevo padre
			newNode->parent = target->parent;
		}
	}

	static Node* findMin(Node* subTree) {
		if (!subTree) {
			return nullptr;
		} else if (subTree->left) {
			return findMin(subTree->left);
		} else {
			return subTree;
		}
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

	void display() {
		displayTree(this->root);
	}

	void displayTree(Node* node, int indent = 0) {
		// cout << " At the moment of display address of root is " << root << endl;
		if (node == nullptr) {
			return;
		}
		displayTree(node->right, indent + 1);
		for (int level = 0; level < indent; level++) {
			cout << "   ";
		}
		
		cout << node->value << endl;

		displayTree(node->left, indent + 1);
	}

};

void printPreOrder(Node* node) {
	if (node == nullptr) return;
	// 1. Visit the root.
	// 2. Traverse the left-side of the sub tree
	// 3. Traverse the right-side of the sub tree
	cout << node->value << " - ";
	printPreOrder(node->left);
	printPreOrder(node->right);
}

void printInOrder(Node* node) {
	// 1. Traverse the left-side of the sub-tree
	// 2. Visit the root.
	// 3. Traverse the right-side of the tree.
	if (node == nullptr) return;
	printInOrder(node->left);
	cout << node->value << endl;
	printInOrder(node->right);
}

void printPostOrden(Node* node) {
	// 1. Traverse the left-side of the sub-tree
	// 2. Traverse the right-side of the sub-tree
	// 3. Visit the root.
	if (node == nullptr) return;
	printPostOrden(node->left);
	printPostOrden(node->right);
	cout << node->value << " - " << "\n";
}

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
		printf("* El valor %d si se encuentra en el árbol\n", data);
	} else {
		printf(" * El valor %d no se encuentra en el árbol\n", data);
	}
}

void makeRemove(BinarySearchTree* tree) {
	printf("Ingrese el valor a eliminar: ");
	int data = readInt();
	if (tree->remove(data)) {
		printf(" * El valor %d ha sido eliminado.\n", data);
	} else {
		printf(" * El valor %d no se encuentra en el árbol\n", data);
	}
	// tree->display();
}


void clear() {
	#ifdef WINDOWS
		std::system("cls");
	#else
		// assume posix
		std::system("clear");
	#endif
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
		 << "   7) - Para mostrar el árbol\n"
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
				makeRemove(tree);
				break;
			case 3:
				checkValue(tree);
				break;
			case 4:
				printPreOrder(tree->root);
				break;
			case 5:
				printInOrder(tree->root);
				break;
			case 6:
				printPostOrden(tree->root);
			case 7:
				tree->display();
				break;
			default:
				printf(" * La opción %d no existe. Intente de nuevo.", option);
				break;
		}
		clear();	
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
