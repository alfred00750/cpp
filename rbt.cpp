#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;

enum Color { RED, BLACK };

template <typename T>
class RedBlackTree {
private:
    struct Node {
        T value;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        Node(const T& v) : value(v), color(RED),
            left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;
    Node* NIL;

public:
    RedBlackTree() {
        NIL = new Node(T());
        NIL->color = BLACK;
        NIL->left = NIL->right = NIL->parent = NIL;
        root = NIL;
    }

    void rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != NIL) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == NIL) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != NIL) x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == NIL) root = x;
        else if (y == y->parent->right) y->parent->right = x;
        else y->parent->left = x;
        x->right = y;
        y->parent = x;
    }

    void fixInsert(Node* k) {
        Node* uncle;
        while (k->parent->color == RED) {
            if (k->parent == k->parent->parent->left) {
                uncle = k->parent->parent->right;
                if (uncle->color == RED) {
                    k->parent->color = BLACK;
                    uncle->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) { k = k->parent; rotateLeft(k); }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rotateRight(k->parent->parent);
                }
            } else {
                uncle = k->parent->parent->left;
                if (uncle->color == RED) {
                    k->parent->color = BLACK;
                    uncle->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) { k = k->parent; rotateRight(k); }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rotateLeft(k->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void insert(const T& val) {
        Node* node = new Node(val);
        node->left = node->right = node->parent = NIL;

        Node* y = NIL;
        Node* x = root;
        while (x != NIL) {
            y = x;
            if (node->value < x->value) x = x->left;
            else if (node->value > x->value) x = x->right;
            else return; // déjà présent
        }

        node->parent = y;
        if (y == NIL) root = node;
        else if (node->value < y->value) y->left = node;
        else y->right = node;

        fixInsert(node);
    }

    bool find(const T& val) {
        Node* current = root;
        while (current != NIL) {
            if (val == current->value) return true;
            if (val < current->value) current = current->left;
            else current = current->right;
        }
        return false;
    }
};

// Chargement avec mesure du temps
RedBlackTree<string>* loadFile(const string& filename, int& count, double& duration_ms) {
    ifstream f(filename);
    if (!f) {
        cerr << "Erreur : impossible d'ouvrir " << filename << endl;
        return nullptr;
    }

    string line;
    auto* tree = new RedBlackTree<string>();
    count = 0;

    auto start = chrono::high_resolution_clock::now();
    while (getline(f, line)) {
        if (!line.empty()) {
            tree->insert(line);
            count++;
        }
    }
    auto end = chrono::high_resolution_clock::now();
    duration_ms = chrono::duration<double, milli>(end - start).count();

    return tree;
}

int main() {
    int nbMots = 0;
    double loadTime = 0.0;

    RedBlackTree<string>* rbt = loadFile("chaines.txt", nbMots, loadTime);

    if (!rbt) {
        cout << "Erreur chargement" << endl;
        return 0;
    }

    cout << "--- Red-Black Tree ---" << endl;
    cout << "Nombre de mots charges : " << nbMots << endl;
    cout << "Temps de chargement : " << loadTime << " ms" << endl << endl;

    string recherche = "bonjour";

    // Mesure du temps de recherche sur 7 itérations
    double totalSearchTime = 0.0;
    bool found = false;

    cout << "Recherche en cours : ";
            auto startSearch = chrono::high_resolution_clock::now();
    for (int i = 0; i < 7; i++) {
        found = rbt->find(recherche);

    cout << "'" << recherche << "' " << (found ? "trouve" : "non trouve") << endl;
    }
    auto endSearch = chrono::high_resolution_clock::now();
        totalSearchTime += chrono::duration<double, milli>(endSearch - startSearch).count();

    cout << " fini!" << endl;

    double avgSearchTime = totalSearchTime / 7.0;
    cout << "'" << recherche << "' " << (found ? "trouve" : "non trouve") << endl;
    cout << "Temps de recherche moyen sur 7 iterations : " << avgSearchTime << " ms" << endl;

    delete rbt;
    return 0;
}
