/**
  *  Worg
  */
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <algorithm>
//FILE *fin = freopen("main.in", "r", stdin);
//FILE *fout = freopen("main.out", "w", stdout);

const long long kModulo = 1000000007;
const long long kCoef = 666013;
const int kMaxN = 2e5 + 1;
const int kMaxNodes = 4e5 + 1;

/*-------- Structures --------*/
struct Treap {
    Treap *leftSon, *rightSon;
    long long priority;
    int key;
    int size;
    long long hashValue;
};
/*-------- Treap data --------*/
Treap *emptyNode, *root, *rootRev;
long long precalculatedHash[kMaxNodes];
/*-------- Input data --------*/
int N, M;
char s[kMaxN];
/*-------- --------*/

void Initialize() {
    srand(time(NULL));
    emptyNode = root = rootRev = new Treap {NULL, NULL, -1, 0, 0, 0};
    precalculatedHash[0] = 1;
    for(int i = 1; i < kMaxNodes; i++) {
        precalculatedHash[i] = (precalculatedHash[i - 1] * kCoef) % kModulo;
    }
}

void Update(Treap *node) {
    if(node != emptyNode) {
        node->size = node->leftSon->size + node->rightSon->size + 1;
        node->hashValue = node->leftSon->hashValue +
                          precalculatedHash[node->leftSon->size] * node->key +
                          precalculatedHash[node->leftSon->size + 1] * node->rightSon->hashValue;
        node->hashValue %= kModulo;
    }
}

Treap* NewNode(int value) {
    return new Treap {
        emptyNode, emptyNode,
        ((1LL * rand() << 45) + (1LL * rand() << 30) + (1LL * rand() << 15) + (1LL * rand())) & 0x7fffffffffffffff,
        value,
        1,
        1LL * value
    };
}

std::pair<Treap*, Treap* > Split(Treap *node, int position) {
    if(node == emptyNode) {
        return {emptyNode, emptyNode};
    } else if(position <= node->leftSon->size) {
        auto p = Split(node->leftSon, position);
        auto answer = std::make_pair(p.first, node);
        answer.second->leftSon = p.second;
        Update(answer.second);
        return answer;
    } else {
        auto p = Split(node->rightSon, position - node->leftSon->size - 1);
        auto answer = std::make_pair(node, p.second);
        answer.first->rightSon = p.first;
        Update(answer.first);
        return answer;
    }
}

Treap* Join(Treap *A, Treap *B) {
    if(A == emptyNode) {
        return B;
    } else if(B == emptyNode) {
        return A;
    } else if(A->priority > B->priority) {
        Treap *answer = A;
        answer->rightSon = Join(A->rightSon, B);
        Update(answer);
        return answer;
    } else {
        Treap *answer = B;
        answer->leftSon = Join(A, B->leftSon);
        Update(answer);
        return answer;
    }
}

Treap *Insert(Treap *root, Treap *node, int position) {
    Treap *answer;
    if(node->priority > root->priority) {
        auto p = Split(root, position);
        node->leftSon = p.first; node->rightSon = p.second;
        answer = node;
    } else if(position <= root->leftSon->size) {
        answer = root;
        answer->leftSon = Insert(answer->leftSon, node, position);
    } else {
        answer = root;
        answer->rightSon = Insert(answer->rightSon, node, position - root->leftSon->size - 1);
    }
    Update(answer);
    return answer;
}

Treap* Insert(Treap *root, int value, int where) {
    return Insert(root, NewNode(value), where);
}

void WriteTreap(Treap *node) {
    if(node != emptyNode) {
        WriteTreap(node->leftSon);
        printf("%d; ", node->key);
        WriteTreap(node->rightSon);
    }
}

void ReadInput() {
    scanf("%d%d", &N, &M);
    scanf("%s", s + 1);
    for(int i = 1; i <= N; i++) {
        root = Insert(root, (int)s[i], i - 1);
    }
    for(int i = N; i >= 1; i--) {
        rootRev = Insert(rootRev, (int)s[i], N - i);
    }
}

void ProcessOperation() {
    char c; scanf(" %c", &c);
    if(c == 'Q') {
        int x, y; scanf("%d%d", &x, &y);
        auto t1 = Split(root, y);
        auto t2 = Split(t1.first, x - 1);
        auto u1 = Split(rootRev, N - x + 1);
        auto u2 = Split(u1.first, N - y);

        if(t2.second->hashValue == u2.second->hashValue) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
        t1.first = Join(t2.first, t2.second);
        root = Join(t1.first, t1.second);

        u1.first = Join(u2.first, u2.second);
        rootRev = Join(u1.first, u1.second);
    } else {
        int type; scanf("%d", &type);
        if(type == 1) {
            int x, y, k; scanf("%d%d%d", &x, &y, &k);
            auto t1 = Split(root, y); /// [1...y] [y+1..N]
            auto t2 = Split(t1.first, x - 1); /// [1..x-1] [x, y]
            auto t3 = Join(t2.first, t1.second); /// [1..x-1, y+1..N]
            auto t4 = Split(t3, k);
            auto t5 = Join(t4.first, t2.second);
            root = Join(t5, t4.second);

            auto u1 = Split(rootRev, N - x + 1); /// [N..x] [x-1..1]
            auto u2 = Split(u1.first, N - y); /// [N..y+1] [y..x]
            auto u3 = Join(u2.first, u1.second); ///[N..y+1][x-1..1]
            auto u4 = Split(u3, N - (y - x + 1) - k);
            auto u5 = Join(u4.first, u2.second);
            rootRev = Join(u5, u4.second);

        } else if(type == 2) {
            int x, y; scanf("%d%d", &x, &y);
            auto t1 = Split(root, y);
            auto t2 = Split(t1.first, x - 1);
            auto u1 = Split(rootRev, N - x + 1);
            auto u2 = Split(u1.first, N - y);
            std::swap(t2.second, u2.second);

            t1.first = Join(t2.first, t2.second);
            root = Join(t1.first, t1.second);

            u1.first = Join(u2.first, u2.second);
            rootRev = Join(u1.first, u1.second);
         } else {
            int x; char c; scanf("%d %c", &x, &c);
            root = Insert(root, (int)c, x - 1);
            rootRev = Insert(rootRev, (int)c, N - x + 1);
            N ++;
         }
    }
}

int main() {
    Initialize();
    ReadInput();

    for(int i = 1; i <= M; i++) {
        ProcessOperation();
    }
    return 0;
}
