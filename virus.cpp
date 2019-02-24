/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("virus.in", "r", stdin);
FILE *fout = freopen("virus.out", "w", stdout);

const int MAX_N = 1 + 1000;
const int MAX_K = 1 + 1000;
const int MAX_L = 1 + 100000;

struct Trie {
    int cnt, nodeList;
    Trie* son[2];
    Trie() {
        this->cnt = 0; this->nodeList = -1;
        this->son[0] = this->son[1] = 0;
    }
};

/*------------------------*/
int L, N, K;
char S[MAX_L], V[MAX_K];
/*------------------------*/
vector< vector< int > > List;
vector< int > aux;
int crtIndex = 0;
/*------------------------*/
int queryAns[MAX_N];

Trie *root = new Trie;

void trieInsert(Trie *node, int pos, int index) {
    node->cnt++;
    if(pos == K) { /* we inserted the whole string */
        if(node->nodeList == -1) { /* we need to create a new nodelist */
            aux.push_back(index);
            List.push_back(aux);
            aux.clear();

            node->nodeList = crtIndex++;
        } else {
            List[node->nodeList].push_back(index);
        }
    } else { /* we continue inserting it */
        int nxt = V[pos] - '0';
        if(!node->son[nxt]) {
            node->son[nxt] = new Trie;
        }
        trieInsert(node->son[nxt], pos + 1, index);
    }
}

void readInput() {
    scanf("%d %d %s", &L, &N, S);
    for(int i = 1; i <= N; i++) {
        scanf("%d %s", &K, V);
        trieInsert(root, 0, i);
    }
}

void tryStart(Trie *node, int pos) {
    if(node->nodeList != -1) {
        for(vector< int >::iterator it = List[node->nodeList].begin(); it != List[node->nodeList].end(); it++) {
            queryAns[*it]++;
        }
    }
    if(pos == L) {
        return;
    }

    int nxt = S[pos] - '0';
    if(node->son[nxt]) {
        tryStart(node->son[nxt], pos + 1);
    }
}

void writeOutput() {
    for(int i = 1; i <= N; i++) {
        printf("%d\n", queryAns[i]);
    }
}

int main() {
    readInput();
    for(int start = 0; start < L; start++) {
        tryStart(root, start);
    }
    writeOutput();
}
