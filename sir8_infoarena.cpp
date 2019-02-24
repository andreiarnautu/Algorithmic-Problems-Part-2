/**
  *  Worg
  */
#include <ctime>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <utility>

using namespace std;
FILE *fin = freopen("sir8.in", "r", stdin);
FILE *fout = freopen("sir8.out", "w", stdout);

const int MAX_K = 1 + 800000;
const int MAX_SIZE = 1 + 800000 + 1;
const int mod_1 = 100003;
const int mod_2 = 100007;
const int val_1 = 31;
const int val_2 = 37;

/*-------- Input data --------*/
char text[MAX_SIZE], text_size;

int K;
int word_size[MAX_K], word_hash_1[MAX_K], word_hash_2[MAX_K];
char word[MAX_SIZE];
/*-------- Hash data --------*/
int hash_1[MAX_K], hash_2[MAX_K];
int coef_1[MAX_SIZE], coef_2[MAX_SIZE];
/*-------- Treap data --------*/
struct Treap {
    Treap* left;
    Treap* right;
    long long priority;
    int size;
    int value;
    int hash_1;
    int hash_2;
};

Treap *empty_treap, *Root;

struct Element {
    int hash_1;
    int hash_2;
    int size;
};
vector< Element > list;
/*-------- --------*/

bool is_empty_treap(Treap* root) {
    return (root == empty_treap);
}

Treap* create_treap(int value) {
    return new Treap {
        empty_treap,
        empty_treap,
        ((1LL * rand() << 45) + (1LL * rand() << 30) + (1LL * rand() << 15) + (1LL * rand())) & 0x7fffffffffffffff,
        1,
        value,
        value,
        value,
    };
}

void update_treap(Treap *root) {
    if(!is_empty_treap(root)) {
        root->size = root->left->size + root->right->size + 1;
        root->hash_1 = (1LL * coef_1[root->right->size + 1] * root->left->hash_1 + 1LL * coef_1[root->right->size] * root->value + 1LL * root->right->hash_1) % mod_1;
        root->hash_2 = (1LL * coef_2[root->right->size + 1] * root->left->hash_2 + 1LL * coef_2[root->right->size] * root->value + 1LL * root->right->hash_2) % mod_2;
    }
}

pair<Treap*, Treap*> split(Treap* root, int where) {
    if(is_empty_treap(root)) {
        return make_pair(empty_treap, empty_treap);
    } else if(where <= root->left->size) {
        pair<Treap*, Treap*> t = split(root->left, where);
        root->left = t.second;
        update_treap(root);

        return make_pair(t.first, root);
    } else {
        pair<Treap*, Treap*> t = split(root->right, where - root->left->size - 1);
        root->right = t.first;
        update_treap(root);

        return make_pair(root, t.second);
    }
}

Treap* join(Treap* first, Treap* second) {
    if(is_empty_treap(first)) {
        return second;
    } else if(is_empty_treap(second)) {
        return first;
    } else if(first->priority > second->priority) {
        first->right = join(first->right, second);
        update_treap(first);
        return first;
    } else {
        second->left = join(first, second->left);
        update_treap(second);
        return second;
    }
}

Treap* insert(Treap* root, Treap* node, int where) {
    if(node->priority > root->priority) {
        pair<Treap*, Treap*> t = split(root, where);
        node->left = t.first;
        node->right = t.second;
        update_treap(node);
        return node;
    } else if(where <= root->left->size) {
        root->left = insert(root->left, node, where);
        update_treap(root);
        return root;
    } else {
        root->right = insert(root->right, node, where - root->left->size - 1);
        update_treap(root);
        return root;
    }
}

Treap* insert(Treap* root, int value, int where) {
    return insert(root, create_treap(value), where);
}

void query(Treap* root, int first, int last, int before = 0) {
    if(is_empty_treap(root)) {
        return;
    } else if(first <= before + 1 && before + root->size <= last) {
        list.push_back({root->hash_1, root->hash_2, root->size});
    } else {
        if(first <= before + root->left->size) {
            query(root->left, first, last, before);
        }
        if(first <= before + root->left->size + 1 && before + root->left->size + 1 <= last) {
            list.push_back({root->value, root->value, 1});
        }
        if(before + root->left->size + 1 < last) {
            query(root->right, first, last, before + root->left->size + 1);
        }
    }
}

void write_treap(Treap* root) {
    if(!is_empty_treap(root)) {
        write_treap(root->left);
        printf("%d; ", root->value);
        write_treap(root->right);
    }
}

void initialize() {
    srand(time(NULL));
    empty_treap = new Treap{NULL, NULL, -1, 0, 0, 0, 0};
    Root = empty_treap;

    coef_1[0] = coef_2[0] = 1;
    for(int i = 1; i < MAX_SIZE; i++) {
        coef_1[i] = (coef_1[i - 1] * val_1) % mod_1;
        coef_2[i] = (coef_2[i - 1] * val_2) % mod_2;
    }
}

void read_data() {
    gets(text + 1);

    for(int i = 1; text[i] != NULL; i++) {
        Root = insert(Root, text[i] - 'a' + 1, i - 1);
    }


    scanf("%d ", &K);
    for(int i = 1; i <= K; i++) {
        scanf("%s", word + 1);
        word_size[i] = strlen(word + 1);

        word_hash_1[i] = word[1] - 'a' + 1;
        word_hash_2[i] = word[1] - 'a' + 1;
        for(int j = 2; j <= word_size[i]; j++) {
            word_hash_1[i] = (word_hash_1[i] * val_1 + word[j] - 'a' + 1) % mod_1;
            word_hash_2[i] = (word_hash_2[i] * val_2 + word[j] - 'a' + 1) % mod_2;
        }
    }
}

void process_queries() {
    int Q; scanf("%d", &Q);
    bool lastResult = false;

    for(int i = 1; i <= Q; i++) {
        int type; scanf("%d", &type);

        if(type == 0) {
            int pos, a, b;
            char c;
            scanf("%d %c %d%d", &pos, &c, &a, &b);

            if(lastResult == false) {
                pos ^= a;
            } else {
                pos ^= b;
            }

            Root = insert(Root, c - 'a' + 1, pos - 1);
        } else {
            int pos, ind, a, b;
            scanf("%d%d%d%d", &pos, &ind, &a, &b);

            if(lastResult == false) {
                pos ^= a;
            } else {
                pos ^= b;
            }

            if(pos < word_size[ind]) {
                lastResult = false;
            } else {
                query(Root, pos - word_size[ind] + 1, pos);
                int expected_1 = 0, expected_2 = 0;

                for(Element now : list) {
                    expected_1 = (1LL * expected_1 * coef_1[now.size] + 1LL * now.hash_1) % mod_1;
                    expected_2 = (1LL * expected_2 * coef_2[now.size] + 1LL * now.hash_2) % mod_2;
                }

                if(expected_1 == word_hash_1[ind] && expected_2 == word_hash_2[ind]) {
                    lastResult = true;
                } else {
                    lastResult = false;
                }
                list.clear();
            }

            printf("%d\n", lastResult);
        }
    }
}

int main() {
    initialize();
    read_data();
    process_queries();
    return 0;
}
