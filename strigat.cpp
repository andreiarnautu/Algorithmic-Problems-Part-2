/**
  *  Worg
  */
#include <queue>
#include <cstdio>

using namespace std;
FILE *fin = freopen("strigat.in", "r", stdin);
FILE *fout = freopen("strigat.out", "w", stdout);

const int MAX_N = 1 + 100;
const int MAX_M = 1 + 100;
const int MAX_WORD = 1 + 100;
const int Sigma = 26;

/*-------- Input data --------*/
int N, M;
int value, currentState;
char Word[MAX_WORD];
/*-------- Aho Corasick data --------*/
struct Trie {
    Trie *son[Sigma], *nxt[Sigma];
    Trie *failLink;
    char lastChar;
    int value;
    int state;
    int dp[MAX_N];
    Trie *before[MAX_N];

    /* Vectorul nxt are urmatoarea semnificatie:
            - daca adaugam la starea curenta caracterul x, in ce stare se va ajunge? */

    Trie() {
        for(int i = 0; i < Sigma; i++) {
            this->son[i] = this->nxt[i] = NULL;
        }
        for(int i = 0; i < MAX_N; i++) {
            this->dp[i] = -1;
            this->before[i] = NULL;
        }
        this->failLink = NULL;
        this->lastChar = '$';
        this->value = 0;
        this->state = 0;
    }
};

Trie *Root = new Trie();
queue< Trie* > Queue;
vector< Trie* > List;
/*-------- Solution --------*/
char outputString[MAX_N];
int Solution = -1;
/*-------- --------*/

void Insert(Trie *node, char *word, int value) {
    if(*word == '\0') {
        node->value += value;
    } else {
        if(node->son[*word - 'a'] == NULL) {
            node->son[*word - 'a'] = new Trie();
            node->son[*word - 'a']->state = (++ currentState);
        }
        node->son[*word - 'a']->lastChar = *word;
        Insert(node->son[*word - 'a'], word + 1, value);
    }
}

void readInput() {
    scanf("%d %d ", &N, &M);
    for(int i = 1; i <= M; i++) {
        scanf("%s", Word);
        scanf("%d ", &value);

        Insert(Root, Word, value);
    }
}

void computeFailLinks() {
    /* initializam datele pentru radacina */
    Root->failLink = Root;
    for(int i = 0; i < Sigma; i++) {
        if(Root->son[i] != NULL) {
            Root->son[i]->failLink = Root;
            Queue.push(Root->son[i]);
        }
    }

    List.push_back(Root);
    while(!Queue.empty()) {
        Trie *node = Queue.front(); Queue.pop();
        List.push_back(node);

        //printf("%d %d\n", node->state, node->value);
        for(int i = 0; i < Sigma; i++) {
            if(node->son[i] != NULL) {
                Trie *fail = node->failLink;

                while(fail != Root && fail->son[i] == NULL) {
                    fail = fail->failLink;
                }
                if(fail->son[i] != NULL && fail->son[i] != node->son[i]) {
                    fail = fail->son[i];
                }

                node->son[i]->failLink = fail;
                node->son[i]->value += fail->value;
                Queue.push(node->son[i]);
            }
        }
    }
}

void getNextStates() {
    /* initializam datele pentru radacina */
    for(int i = 0; i < Sigma; i++) {
        if(Root->son[i] != NULL) {
            Root->nxt[i] = Root->son[i];
        } else {
            Root->nxt[i] = Root;
        }
    }

    for(Trie *node : List) {
        /* parcurgem nodurile in ordinea precalculata */
        if(node == Root) {continue;}

        for(int i = 0; i < Sigma; i++) {
            if(node->son[i] != NULL) {
                node->nxt[i] = node->son[i];
            } else {
                node->nxt[i] = node->failLink->nxt[i];
            }
        }
    }
}

void runDP() {
    Root->dp[0] = 0;
    for(int i = 0; i < N; i++) {
        for(Trie *node : List) {
            /* parcurgem lista cu noduri */
            if(node->dp[i] != -1) {
                /* daca in starea curenta se poate ajunge dupa i pasi */
                for(int j = 0; j < Sigma; j++) {
                    if(node->nxt[j]->dp[i + 1] < node->dp[i] + node->nxt[j]->value) {
                        node->nxt[j]->dp[i + 1] = node->dp[i] + node->nxt[j]->value;
                        node->nxt[j]->before[i + 1] = node;
                    }
                }
            }
        }
    }

    Trie *now = NULL;
    for(Trie *node : List) {
        if(Solution < node->dp[N]) {
            Solution = node->dp[N];
            now = node;
        }
    }
    printf("%d\n", Solution);

    int Level = N;
    while(Level > 0) {
        if(now->lastChar != '$') {
            outputString[Level] = now->lastChar;
        } else {
            outputString[Level] = 'z';
        }

        now = now->before[Level];
        Level --;
    }

    printf("%s", outputString + 1);
}

int main() {
    readInput();
    computeFailLinks();
    getNextStates();
    runDP();
    return 0;
}
