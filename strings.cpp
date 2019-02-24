/**
  *  Worg
  *  Mar 26, 2018
  *  12:12:21 PM
  */
#include <ctime>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>

FILE *fin = freopen("strings.in", "r", stdin); FILE *fout = freopen("strings.out", "w", stdout);

const long long mod = 1e9 + 7;
const long long coef = 666013;
const int maxN = 2e5 + 5;
const int maxNodes = 2 * maxN;

/*-------- Struct --------*/
struct Treap {
  Treap *leftSon, *rightSon;
  long long priority;
  int key;
  int size;
  long long hashValue;
};
/*-------- Data --------*/
Treap *emptyNode, *root, *revRoot;
long long hash[maxNodes];

int n, m;
char s[maxN];
/*-------- --------*/

/*----------------------------------- Treap zone -----------------------------------*/

void Update(Treap *node) {
  if(node == emptyNode) return;

  node->size = node->leftSon->size + node->rightSon->size + 1;

  node->hashValue = node->leftSon->hashValue +
                    hash[node->leftSon->size] * node->key +
                    hash[node->leftSon->size + 1] * node->rightSon->hashValue;

  node->hashValue %= mod;
}

Treap* NewNode(const int value) {
  return new Treap {
    emptyNode, emptyNode,
    ((1LL * rand() << 45) + (1LL * rand() << 30) + (1LL * rand() << 15) + (1LL * rand())) & 0x7fffffffffffffff,
    value,
    1,
    1LL * value
  };
}

std::pair<Treap*, Treap* > Split(Treap *node, const int position) {
  if(node == emptyNode) {
    return {emptyNode, emptyNode};
  } else if(position <= node->leftSon->size) {
    auto p = Split(node->leftSon, position);

    auto answer = std::make_pair(p.first, node); answer.second->leftSon = p.second;

    Update(answer.second); return answer;
  } else {
    auto p = Split(node->rightSon, position - node->leftSon->size - 1);
    auto answer = std::make_pair(node, p.second); answer.first->rightSon = p.first;

    Update(answer.first); return answer;
  }
}

Treap* Join(Treap *a, Treap *b) {
  if(a == emptyNode) {
    return b;
  } else if(b == emptyNode) {
    return a;
  } else if(a->priority > b->priority) {
    Treap *answer = a;

    answer->rightSon = Join(a->rightSon, b);

    Update(answer); return answer;
  } else {
    Treap *answer = b;

    answer->leftSon = Join(a, b->leftSon);

    Update(answer); return answer;
  }
}

Treap* Insert(Treap *root, Treap *node, int position) {
  Treap *answer;

  if(node->priority > root->priority) {
    auto p = Split(root, position);

    answer = node; answer->leftSon = p.first; answer->rightSon = p.second;
  } else if(position <= root->leftSon->size) {
    answer = root;
    answer->leftSon = Insert(root->leftSon, node, position);
  } else {
    answer = root;
    answer->rightSon = Insert(root->rightSon, node, position - root->leftSon->size - 1);
  }

  Update(answer); return answer;
}

Treap* Insert(Treap *root, int value, int position) {
  return Insert(root, NewNode(value), position);
}
/*----------------------------------- End of treap zone -----------------------------------*/

void Initialize() {
  hash[0] = 1;
  for(int i = 1; i < maxNodes; i++) {
    hash[i] = hash[i - 1] * coef % mod;
  }

  srand(time(NULL));

  emptyNode = root = revRoot = new Treap {NULL, NULL, -1, 0, 0, 0};
}

void ReadInput() {
  scanf("%d%d", &n, &m);
  scanf("%s", s + 1);

  ///  Build the initial treaps
  for(int i = 1; i <= n; i++) {
    root = Insert(root, s[i], i - 1);
  }
  for(int i = n; i >= 1; i--) {
    revRoot = Insert(revRoot, s[i], n - i);
  }
}

void ProcessOperations() {
  for(int i = 0; i < m; i++) {
    char c; scanf(" %c", &c);

    if(c == 'Q') {
      int x, y; scanf("%d%d", &x, &y);

      auto t1 = Split(root, y); auto t2 = Split(t1.first, x - 1);
      auto u1 = Split(revRoot, n - x + 1); auto u2 = Split(u1.first, n - y);

      if(t2.second->hashValue == u2.second->hashValue) {
        printf("YES\n");
      } else {
        printf("NO\n");
      }

      t1.first = Join(t2.first, t2.second); root = Join(t1.first, t1.second);
      u1.first = Join(u2.first, u2.second); revRoot = Join(u1.first, u1.second);
    } else {
      int type; scanf("%d", &type);

      if(type == 1) {
        int x, y, k; scanf("%d%d%d", &x, &y, &k);

        ///  This one is cancer

        ///  Change the normal treap
        auto t1 = Split(root, y);  //  [1..y] + [y+1..n]
        auto t2 = Split(t1.first, x - 1);  //  [1..x-1] + [x..y]
        auto t3 = Join(t2.first, t1.second);  //  T
        auto t4 = Split(t3, k);
        auto t5 = Join(t4.first, t2.second);
        root = Join(t5, t4.second);

        ///  Change the reversed treap
        auto u1 = Split(revRoot, n - x + 1);
        auto u2 = Split(u1.first, n - y);
        auto u3 = Join(u2.first, u1.second);
        auto u4 = Split(u3, n - (y - x + 1) - k);
        auto u5 = Join(u4.first, u2.second);
        revRoot = Join(u5, u4.second);
      } else if(type == 2) {
        int x, y; scanf("%d%d", &x, &y);

        ///  This one is kinda nice
        auto t1 = Split(root, y); auto t2 = Split(t1.first, x - 1);
        auto u1 = Split(revRoot, n - x + 1); auto u2 = Split(u1.first, n - y);

        std::swap(t2.second, u2.second);

        t1.first = Join(t2.first, t2.second); root = Join(t1.first, t1.second);

        u1.first = Join(u2.first, u2.second); revRoot = Join(u1.first, u1.second);
      } else {
        int x; char c; scanf("%d %c", &x, &c);

        root = Insert(root, (int)c, x - 1);
        revRoot = Insert(revRoot, (int)c, n - x + 1);

        n++;
      }
    }
  }
}

int main() {
  Initialize();

  ReadInput();

  ProcessOperations();
  return 0;
}
