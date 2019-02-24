/**
  *  Worg
  */
#include <stack>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("retele.in", "r", stdin);
FILE *fout = freopen("retele.out", "w", stdout);

const int MAX_N = 1 + 50000;

/*-----------------------------*/
vector< int > G[MAX_N];
int N, M;
/*-----------------------------*/
int index[MAX_N], lowlink[MAX_N];
int currentIndex = 1;

stack< int > Stack;
bool inStack[MAX_N];
vector< vector< int > > SCC;
vector< int > aux;
/*-----------------------------*/

void readData() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        G[u].push_back(v);
    }
}

void strongConnect(int node) {
    index[node] = lowlink[node] = currentIndex++;
    Stack.push(node); inStack[node] = true;

    for(vector< int >::iterator it = G[node].begin(); it != G[node].end(); it++) {
        if(!index[*it]) {
            strongConnect(*it);
            lowlink[node] = min(lowlink[node], lowlink[*it]);
        } else if(inStack[*it]) {
            lowlink[node] = min(lowlink[node], index[*it]);
        }
    }

    if(lowlink[node] == index[node]) {
        int now;
        do {
            now = Stack.top(); Stack.pop();
            inStack[now] = false;
            aux.push_back(now);
        }while(now != node);

        sort(aux.begin(), aux.end());
        SCC.push_back(aux); aux.clear();
    }
}

void runTarjan() {
    for(int i = 1; i <= N; i++) {
        if(!index[i]) {
            strongConnect(i);
        }
    }
}

bool comp(vector< int > a, vector< int > b) {
    return (*a.begin() < *b.begin());
}

void writeData() {
    printf("%d\n", (int)SCC.size());
    for(int i = 0; i < (int)SCC.size(); i++) {
        printf("%d ", (int)SCC[i].size());
        for(vector< int >::iterator it = SCC[i].begin(); it != SCC[i].end(); it++) {
            printf("%d ", *it);
        }
        printf("\n");
    }
}

int main() {
    readData();
    runTarjan();
    sort(SCC.begin(), SCC.end(), comp);
    writeData();
    return 0;
}
