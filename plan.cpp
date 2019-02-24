/**
  *  Worg
  */
#include <stack>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("plan.in", "r", stdin);
FILE *fout = freopen("plan.out", "w", stdout);

const int MAX_N = 1 + 500;

/*-----------------------*/ /** General data */
vector< int > G[MAX_N];
int N, M;
/*-----------------------*/ /** Strong connected components */
int index[MAX_N], lowlink[MAX_N], sccIndex[MAX_N];
int currentIndex = 1;

bool inStack[MAX_N];
stack< int > Stack;

vector< vector< int > > SCC;
vector< int > aux;
/*-----------------------*/ /** New graph(SCC components) */
vector< int > G2[MAX_N];
bool inner[MAX_N], outter[MAX_N], dfsChecked[MAX_N];

/*-----------------------*/ /** Hopcroft karp */
vector< int > G3[MAX_N];
bool checked[MAX_N], checkedRight[MAX_N];
int left[MAX_N], right[MAX_N];
/*-----------------------*/ /** Ending */
vector< pair< int,int > > couples, SOL;
/*-----------------------*/

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
            inStack[now] = false; sccIndex[now] = (int)SCC.size();
            aux.push_back(now);
        }while(now != node);

        SCC.push_back(aux); aux.clear();
    }
}

void runTarjan() {
    SCC.push_back(aux); /* we don't want the SCC to be indexed from 0 */
    for(int i = 1; i <= N; i++) {
        if(!index[i]) {
            strongConnect(i);
        }
    }
}

void makeNewGraph() {
    for(int i = 1; i <= N; i++) {
        for(vector< int >::iterator it = G[i].begin(); it != G[i].end(); it++) {
            if(sccIndex[i] != sccIndex[*it]) {
                G2[sccIndex[i]].push_back(sccIndex[*it]);
                inner[sccIndex[i]] = true;
                outter[sccIndex[*it]] = true;
            }
        }
    }
}

void DFS(int start, int node) {
    dfsChecked[node] = true;
    if(!G2[node].size()) {
        G3[start].push_back(node);
    } else {
        for(vector< int >::iterator it = G2[node].begin(); it != G2[node].end(); it++) {
            if(!dfsChecked[*it]) {
                DFS(start, *it);
            }
        }
    }
}

bool pairUp(int node) {
    if(checked[node]) {
        return false;
    } else {
        checked[node] = true;
    }

    for(vector< int >::iterator it = G3[node].begin(); it != G3[node].end(); it++) {
        if(!right[*it]) {
            left[node] = *it;
            right[*it] = node;

            return true;
        }
    }

    for(vector< int >::iterator it = G3[node].begin(); it != G3[node].end(); it++) {
        if(pairUp(*it)) {
            left[node] = *it;
            right[*it] = node;

            return true;
        }
    }

    return false;
}

void makeEdge(int comp_1, int comp_2) {
    SOL.push_back(make_pair(*SCC[comp_1].begin(), *SCC[comp_2].begin()));
}

void hopcroftKarp() {
    for(int i = 1; i < (int)SCC.size(); i++) {
        if(!outter[i]) {
            for(int j = 1; j < (int)SCC.size(); j++) {
                dfsChecked[j] = false;
            }
            DFS(i, i);
        }
    }

    bool ok;
    do {
        ok = false;
        for(int i = 1; i < (int)SCC.size(); i++) {
            checked[i] = false;
        }
        for(int i = 1; i < (int)SCC.size(); i++) {
            if(!checked[i]) {
                ok |= pairUp(i);
            }
        }
    }while(ok);

    for(int i = 1; i < (int)SCC.size(); i++) {
        if(left[i]) {
            checkedRight[left[i]] = true;
            couples.push_back(make_pair(i, left[i]));
        }
    }

    for(int i = 1; i < (int)SCC.size(); i++) {
        if(!outter[i] && !left[i]) {
            for(int j = 1; j < (int)SCC.size(); j++) {
                if(!inner[j] && !checkedRight[j]) {
                    makeEdge(j, i);
                    left[i] = j; checkedRight[j] = true;
                }
            }
        }
    }
}

void Ending() {
    for(int i = 0; i < (int)couples.size() - 1; i++) {
        makeEdge(couples[i].second, couples[i + 1].first);
    }

    makeEdge(couples[(int)couples.size() - 1].second, couples[0].first);

    for(int i = 1; i < (int)SCC.size(); i++) {
        if(!outter[i] && !left[i]) {
            makeEdge(couples[0].second, i);
        }
        if(!inner[i] && !checkedRight[i]) {
            makeEdge(i, couples[0].first);
        }
    }
}

void writeData() {
    printf("%d\n", (int)SOL.size());
    for(vector< pair< int,int > >::iterator it = SOL.begin(); it != SOL.end(); it++) {
        printf("%d %d\n", it->first, it->second);
    }
}

int main() {
    readData();
    runTarjan();
    if((int)SCC.size() == 2) {
        printf("0\n"); return 0;
    }
    makeNewGraph();
    hopcroftKarp();
    Ending();
    writeData();

    return 0;
}
