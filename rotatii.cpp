/**
  *  Worg
  */
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("rotatii.in", "r", stdin);
FILE *fout = freopen("rotatii.out", "w", stdout);

const int buffer_dim = 1 + 100000;

/*-------- Input reader --------*/

class inputReader {
private:
        char buffer[buffer_dim];
        int pos = 0;

        bool digit(char c) {
            return('0' <= c && c <= '9');
        }

public:
        void get_buffer() {
            fread(buffer, 1, buffer_dim, stdin);
            pos = 0;
        }

        void operator >>(int &nr) {
            nr = 0;
            char c = '+';
            while(!digit(buffer[pos])) {
                c = buffer[pos];
                if(++pos == buffer_dim) {
                    get_buffer();
                }
            }
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == buffer_dim) {
                    get_buffer();
                }
            }
            if(c == '-') {
                nr = -nr;
            }
        }
} cin;

/*-------- Input data --------*/
int N, M;
/*-------- Treap data --------*/
struct Treap {
    Treap* left;
    Treap* right;
    long long priority;
    int value;
    int size;
    long long total_sum, min_sum;
};

Treap *empty_treap, *Root;
/*-------- --------*/

void initialize_treap() {
    srand(time(NULL));
    empty_treap = new Treap {NULL, NULL, -1, 0, 0, 0, 0};
    Root = empty_treap;
}

bool is_empty_treap(Treap *root) {
    return (root == empty_treap);
}

Treap* create_treap(int value) {
    return new Treap {
        empty_treap,
        empty_treap,
        ((1LL * rand() << 45) + (1LL * rand() << 30) + (1LL * rand() << 15) + (1LL * rand())) & 0x7fffffffffffffff,
        value,
        1,
        value,
        value
    };
}

void update_treap(Treap* root) {
    if(!is_empty_treap(root)) {
        root->size = root->left->size + root->right->size + 1;
        root->total_sum = root->left->total_sum + root->right->total_sum + 1LL * root->value;

        root->min_sum = min( root->left->min_sum,
                             min( root->left->total_sum + root->value,
                                  root->left->total_sum + root->value + root->right->min_sum)
                                                );

    }
}

pair<Treap*, Treap*> split(Treap* root, int where) {
    pair<Treap*, Treap*> answer;
    if(is_empty_treap(root)) {
        answer.first = answer.second = empty_treap;
    } else if(where <= root->left->size) {
        pair<Treap*, Treap*> t = split(root->left, where);
        answer.first = t.first;

        answer.second = root;
        answer.second->left = t.second;
        update_treap(answer.second);
    } else {
        pair<Treap*, Treap*> t = split(root->right, where - root->left->size - 1);
        answer.first = root;
        answer.first->right = t.first;
        update_treap(answer.first);

        answer.second = t.second;
    }

    return answer;
}

Treap *join(Treap *first, Treap* second) {
    Treap *answer;
    if(is_empty_treap(first)) {
        answer = second;
    } else if(is_empty_treap(second)) {
        answer = first;
    } else if(first->priority > second->priority) {
        answer = first;
        answer->right = join(answer->right, second);
        update_treap(answer);
    } else {
        answer = second;
        answer->left = join(first, answer->left);
        update_treap(answer);
    }

    return answer;
}

Treap* insert(Treap* root, Treap* node, int where) {
    Treap* answer;

    if(node->priority > root->priority) {
        pair<Treap*, Treap*> t = split(root, where);
        answer = node;
        answer->left = t.first;
        answer->right = t.second;
        update_treap(answer);
    } else if(where <= root->left->size) {
        answer = root;
        answer->left = insert(answer->left, node, where);
        update_treap(answer);
    } else {
        answer = root;
        answer->right = insert(answer->right, node, where - root->left->size - 1);
        update_treap(answer);
    }

    return answer;
}

Treap* insert(Treap* root, int value, int where) {
    return insert(root, create_treap(value), where);
}

Treap* erase(Treap* root, int where) {
    Treap* answer;

    if(where <= root->left->size) {
        answer = root;
        answer->left = erase(answer->left, where);
        update_treap(answer);
    } else if(where == root->left->size + 1) {
        answer = join(root->left, root->right);
        delete root;
    } else {
        answer = root;
        answer->right = erase(answer->right, where - root->left->size - 1);
        update_treap(answer);
    }

    return answer;
}

int get_min_sum(Treap* root) {
    if(is_empty_treap(root)) {
        return 0;
    } else if(root->left->min_sum == root->min_sum) {
        return get_min_sum(root->left);
    } else if(root->left->total_sum + root->value == root->min_sum) {
        return root->left->size + 1;
    } else {
        return root->left->size + 1 + get_min_sum(root->right);
    }
}

void write_treap(Treap *root) {
    if(!is_empty_treap(root)) {
        write_treap(root->left);
        printf("%d; ", root->value);
        write_treap(root->right);
    }
}

void read_input() {
    cin.get_buffer();
    cin >> N; cin >> M;

    for(int i = 1; i <= N; i++) {
        int value; cin >> value;
        Root = insert(Root, value, i - 1);
    }
}

void process_operations() {
    for(int i = 1; i <= M; i++) {
        int type; cin >> type;

        if(type == 0) {
            int value, where; cin >> where; cin >> value;

            Root = insert(Root, value, where);
        } else if(type == 1) {
            int x; cin >> x;
            Root = erase(Root, x);
        } else {
            if(Root->total_sum < 0) {
                printf("-1\n");
            } else {
                printf("%d\n", get_min_sum(Root) % Root->size);
            }
        }
    }
}

int main() {
    initialize_treap();
    read_input();
    process_operations();

    return 0;
}
