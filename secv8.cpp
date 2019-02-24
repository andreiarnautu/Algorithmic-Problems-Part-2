/**
  *  Worg
  */
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

#define INF 2000000000

using namespace std;
FILE *fin=freopen("secv8.in","r",stdin);
FILE *fout=freopen("secv8.out","w",stdout);

struct treap {

            int key, priority, rev, cnt;
            treap *left, *right;

            treap(int key, int priority, int rev, int cnt, treap *left, treap *right) {

                this->key = key, this->priority = priority, this->rev = rev, this->cnt = cnt;
                this->left = left, this-> right = right;
            }
} *root, *empty;

void spread(treap *&node) {

    if(node->rev) {

        swap(node->left, node->right);
        node->rev ^= 1;
        node->left->rev ^= 1;
        node->right->rev ^= 1;
    }
}

void update(treap *&node) {

    if(node != empty)
        node->cnt = node->left->cnt + node->right->cnt + 1;
}

void rotLeft(treap *&node) {

    spread(node->left);

    treap *t = node->left;
    node->left = t->right, t->right = node;
    node = t;

    update(node->right); update(node);
}

void rotRight(treap *&node) {

    spread(node->right);

    treap *t = node->right;
    node->right = t->left, t->left = node;
    node = t;

    update(node->left); update(node);
}

void balance(treap *&node) {

    spread(node);

    if(node->left->priority > node->priority)
        rotLeft(node);
    else if(node->right->priority > node->priority)
        rotRight(node);
}

int search(treap *node, int pos) {

    spread(node);
    if(node->left->cnt >= pos)
        return search(node->left, pos);
    if(node->left->cnt + 1 < pos)
        return search(node->right, pos - node->left->cnt - 1);
    return node->key;
}

void insert(treap *&node, int key, int priority, int pos) {

    if(node == empty) {

        node = new treap(key, priority, 0, 1, empty, empty);
        return;
    }

    spread(node);
    if(node->left->cnt + 1 >= pos)
        insert(node->left, key, priority, pos);
    else
        insert(node->right, key, priority, pos - node->left->cnt - 1);

    update(node);
    balance(node);

}

void erase(treap *&node, int pos) {

    if(node == empty)
        return;
    spread(node);

    if(node->left->cnt >= pos)
        erase(node->left, pos);
    else if (node->left->cnt + 1 < pos)
        erase(node->right, pos - node->left->cnt - 1);
    else {

        if(node->left == empty && node->right == empty) {
                delete node, node = empty;
        }
        else {
            (node->left->priority > node->right->priority) ? rotLeft(node) : rotRight(node);
            erase(node, pos);
        }
    }
    update(node);
}

void split(treap *&node, treap *&lTreap, treap *&rTreap, int pos) {

    insert(node, 0, INF, pos);

    lTreap = node->left;
    rTreap = node->right;
    delete node; node = empty;
}

void join(treap *&node, treap*&lTreap, treap*&rTreap) {

    node = new treap(0, INF, 0, lTreap->cnt + rTreap->cnt + 1, lTreap, rTreap);
    erase(node, lTreap->cnt + 1);
}

void write(treap *node) {

    if(node == empty)
        return;
    spread(node);
    write(node->left);
    printf("%d ", node->key);
    write(node->right);
}

void init() {

    srand(unsigned(time(0)));
    root = empty = new treap(0, 0, 0, 0, NULL, NULL);
    empty->left = empty->right = empty;
}

int main() {

    int n, what_is_this, a, b;
    char c;

    init();
    for(scanf("%d %d ", &n, &what_is_this); n; --n) {

        scanf("%c ", &c);
        if(c == 'I') {
            scanf("%d %d ", &a, &b);
            insert(root, b, rand() % INF + 1, a);
        }
        if(c == 'A') {
            scanf("%d ", &a);
            printf("%d\n", search(root, a));
        }
        if(c == 'R') {
            scanf("%d %d ", &a, &b);
            treap *w, *x, *y, *z;

            split(root, w, x, b + 1);
            split(w, y, z, a);
            z -> rev ^= 1;
            join(w, y, z);
            join(root, w, x);
        }
        if(c == 'D') {
            scanf("%d %d ", &a, &b);
            treap *w, *x, *y, *z;

            split(root, w, x, b + 1);
            split(w, y, z, a);
            join(root, y, x);
        }
    }
    write(root);
    return 0;
}
