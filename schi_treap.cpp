/**
  *  Worg
  */
#include <ctime>
#include <cstdio>
#include <cstdlib>

using namespace std;
FILE *fin=freopen("schi.in","r",stdin);
FILE *fout=freopen("schi.out","w",stdout);

struct treap {

        int key, priority, total;
        treap *left, *right;

        treap(int key, int priority, int total, treap *left, treap *right) {

            this->key = key, this->priority = priority, this->total = total;
            this->left = left, this->right = right;

        }
} *root, *empty;

void update(treap *&node) {

    if(node == empty)
        node->total = 0;
    else
        node->total = (node->left == empty ? 0 : node->left->total) +
                        (node->right == empty ? 0 : node->right->total) + 1;
}

void rotLeft(treap *&node) {

    treap *T = node->left;
    node->left = T->right, T->right = node;
    node = T;

    update(node->right); update(node);
}

void rotRight(treap *&node) {

    treap *T = node->right;
    node->right = T->left, T->left = node;
    node = T;

    update(node->left); update(node);
}

void balance(treap *&node) {

    if(node->priority < node->left->priority)
        rotLeft(node);
    else if(node->priority < node->right->priority)
        rotRight(node);
}

void insert(treap *&node, int key, int pos) {

    if(node == empty) {

        node = new treap(key, rand() + 1, 1, empty, empty);
        update(node);
        return;
    }

    if(pos <= node->left->total)
        insert(node->left, key, pos);
    else
        insert(node->right, key, pos - node->left->total - 1);

    update(node);
    balance(node);
}

void write(treap *node) {

    if(node == empty)
        return;
    write(node->left);
    printf("%d\n", node->key);
    write(node->right);
}

void init() {

    srand(unsigned(time(0)));
    empty = root = new treap(0, 0, 0, NULL, NULL);
}

int main() {

    int n, x;
    scanf("%d ", &n);

    init();

    for(int i = 1; i <= n; ++i) {

        scanf("%d ", &x);
        insert(root, i, x - 1);
    }

    write(root);
    return 0;
}
