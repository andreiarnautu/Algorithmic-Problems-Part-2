/**
  *  Worg
  */
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <algorithm>

#define inf 2000000000

using namespace std;
ifstream in("zeap.in");
ofstream out("zeap.out");

int nodes;
char s[20];

struct treap{

        int key, priority, minim, maxim, difMin;
        treap *left, *right;

        treap(int key, int priority, int minim, int maxim, int difMin, treap *left, treap *right) {

            this -> key = key, this -> priority = priority;
            this -> minim = minim, this -> maxim = maxim, this -> difMin = difMin;
            this -> left = left, this -> right = right;
        }
} *root, *empty;

void update(treap *&node) {

    node->maxim = max(node->key, node->right->maxim);
    node->minim = min(node->key, node->left->minim);
    node->difMin = min(min(node->left->difMin, node->right->difMin),
                       min(abs(node->key - node->left->maxim), abs(node->key - node->right->minim)));
}

void rotLeft(treap *&node) {

    treap *t = node->left;
    node->left = t->right, t->right = node;
    node = t;

    if(node != empty && node->right != empty)
        update(node->right);
}

void rotRight(treap *&node) {

    treap *t = node->right;
    node->right = t->left, t->left = node;
    node = t;

    if(node != empty && node->left != empty)
        update(node->left);
}

void balance(treap *&node) {

    if(node->priority < node->left->priority)
        rotLeft(node);
    else if(node->priority < node->right->priority)
        rotRight(node);
    update(node);
}

void insert(treap *&node, int key, int priority) {

    if(node == empty) {
        node = new treap(key, priority, key, key, inf, empty, empty);
        ++nodes;
        return;
    }

    if(key < node->key)
        insert(node->left, key, priority);
    else if(key > node->key)
        insert(node->right, key, priority);
    balance(node);
}

void erase(treap *&node, int key) {

    if(node == empty)
        return;
    if(key < node->key)
        erase(node->left, key);
    else if(key > node->key)
        erase(node->right, key);
    else {

        if(node->left == empty && node->right == empty)
            delete node, node = empty, --nodes;
        else {
            (node->left->priority > node->right->priority) ? rotLeft(node) : rotRight(node);
            erase(node, key);
        }
    }
    if(node != empty)
        update(node);
}

int search(treap *node, int key) {

    if(node == empty)
        return 0;
    if(node->key == key)
        return 1;
    if(key < node->key)
        return search(node->left, key);
    else
        return search(node->right, key);
}

void init() {

    srand(unsigned(time(0)));
    root = empty = new treap(0, 0, inf, -inf, inf, NULL, NULL);
}

int main() {

    init();

    int x;
    while( in >> s ) {

        if(s[0] == 'I') {

            in >> x;
            insert(root, x, rand() % inf + 1);
        }

        else if(s[0] == 'S') {

            in >> x;
            if( !search(root, x) )
                out << "-1\n";
            else
                erase(root, x);
        }

        else if(s[0] == 'C') {

            in >> x;
            out << search(root, x) << '\n';
        }

        else if(s[1] == 'A') {

            if(nodes < 2)
                out << "-1\n";
            else
                out << root->maxim - root->minim << '\n';
        }

        else {
            if(nodes < 2)
                out << "-1\n";
            else
                out << root->difMin << '\n';
        }
    }
    return 0;
}
