/**
  *  Worg
  */
#include <queue>
#include <stack>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("plimbare.in", "r", stdin);
FILE *fout = freopen("plimbare.out", "w", stdout);

const int MAX_N = 1 + 100 + 1;

/*-------------------------*/
vector< int > G[MAX_N];
bool adj[MAX_N][MAX_N];
int N, M;
/*-------------------------*/
int lowlink[MAX_N], index[MAX_N];
int currentIndex = 1;

stack< int > Stack;
bool inStack[MAX_N];

vector< vector< int > > SCC;
vector< int > aux;
/*-------------------------*/
vector< int > vec;
bool good[MAX_N], checked[MAX_N], inner[MAX_N], outter[MAX_N];
int path[MAX_N], father[MAX_N];
int pos;
/*-------------------------*/

void readData() {
    scanf("%d", &N); M = N * (N - 1) / 2;
    for(int i = 1; i <= M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        G[u].push_back(v);
        adj[u][v] = true;
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

int findBest() {
    int answer = 0, length = -1;
    for(int i = 0; i < (int)SCC.size(); i++) {
        if(length < (int)SCC[i].size()) {
            length = (int)SCC[i].size();
            answer = i;
        }
    }

    return answer;
}

bool found = false;

void DFS(int node, int Father = 0) {
    if(found) {
        return;
    }
    father[node] = Father;
    checked[node] = true;

    for(vector< int >::iterator it = G[node].begin(); it != G[node].end(); it++) {
        if(good[*it]) {
            if(!checked[*it]) {
                DFS(*it, node);
            } else {
                found = true;
                do {
                    aux.push_back(node);
                    node = father[node];
                }while(node != *it && node != 0);
                aux.push_back(node);
                for(int i = (int)aux.size() - 1; i >= 0; i--) {
                    path[++pos] = aux[i];
                }
                found = true;
                return;
            }
        }
        if(found) {
            return;
        }
    }

    checked[node] = false;
}

void solveComponent(int var) {
    vec = SCC[var];
    for(vector< int >::iterator it = vec.begin(); it != vec.end(); it++) {
        good[*it] = true;
    }

    DFS(*vec.begin());

    for(int i = 1; i <= N; i++) {
        checked[i] = false;
    }
    for(int i = 1; i <= pos; i++) {
        checked[path[i]] = true;
    }
    path[pos + 1] = path[1];
    for(int i = 1; i <= N; i++) {
        if(good[i]) {
            if(checked[i]) {
                for(vector< int >::iterator it = G[i].begin(); it != G[i].end(); it++) {
                    if(good[*it]) {
                        outter[*it] = true;
                    }
                }
            } else {
                for(vector< int >::iterator it = G[i].begin(); it != G[i].end(); it++) {
                    if(good[*it]) {
                        if(checked[*it]) {
                            inner[i] = true;
                        }
                    }
                }
            }
        }
    }

  //  printf("%d\n", checked[1]);

    while(pos < (int)SCC[var].size()) {
        bool ok = false;
        for(int i = 1; i <= N && ok == false; i++) {
            if(good[i] && !checked[i] && inner[i] && outter[i]) {
                for(int j = 1; j <= pos; j++) {
                    if(adj[path[j]][i] && adj[i][path[j + 1]]) {
                //        printf("%d %d\n", i, j);
                        for(int l = pos + 2; l > j + 1; l--) {
                            path[l] = path[l - 1];
                        }
                        path[j + 1] = i;
                        break;
                    }
                }
                for(int j = 1; j <= N; j++) {
                    if(!good[j]) {
                        continue;
                    }
                    if(adj[i][j]) {
                        outter[j] = true;
                    }
                    if(adj[j][i]) {
                        inner[j] = true;
                    }
                }
                checked[i] = true; pos++; ok = true;
            }
        }

        if(!ok) {
            int node_1 = -1, node_2 = -1;
            for(int i = 1; i <= N; i++) {
                if(good[i] && !checked[i] && outter[i]) {
                    node_1 = i; break;
                }
            }
            for(vector< int >::iterator it = G[node_1].begin(); it != G[node_1].end(); it++) {
                if(good[*it] && !checked[*it] && inner[*it]) {
                    node_2 = *it; break;
                }
            }


            if(node_1 == -1 || node_2 == -1) {
                while(1);
            }

            checked[node_1] = checked[node_2] = true;

            for(int i = 1; i <= pos; i++) {
                if(adj[path[i]][node_1] && adj[node_2][path[i + 1]]) {
                    for(int j = pos + 3; j > i + 2; j--) {
                        path[j] = path[j - 2];
                    }
                    path[i + 1] = node_1; path[i + 2] = node_2; pos += 2;
                    break;
                }
            }
            for(int i = 1; i <= N; i++) {
                if(!good[i]) {
                    continue;
                }
                if(adj[i][node_1] || adj[i][node_2]) {
                    inner[i] = true;
                }
                if(adj[node_1][i] || adj[node_2][i]) {
                    outter[i] = true;
                }
            }
        }
    }

    printf("%d\n", (int)SCC[var].size());
    if(pos != (int)SCC[var].size()) {
        while(1);
    }
    for(int i = 1; i <= pos; i++) {
        printf("%d ", path[i]);
    }

}

int main() {
    readData();
    runTarjan();
    solveComponent(findBest());
    return 0;
}
