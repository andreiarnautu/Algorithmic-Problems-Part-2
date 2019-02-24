/**
  *  Worg
  */
#include <stack>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("santa.in", "r", stdin);
FILE *fout = freopen("santa.out", "w", stdout);

const int MAX_N = 1 + 45000;

/*----------------------------*/ /** General stuff */
vector< int > graph[MAX_N];
int N, M;
int S, E, Q;
/*----------------------------*/ /** Must visit */
bool mustVisit[MAX_N], checked[MAX_N];
/*----------------------------*/ /** Biconnected components */
bool criticalNode[MAX_N];
int level[MAX_N], biconnectedDP[MAX_N];

stack< int > Stack;
vector< vector< int > > comps;
vector< int > criticals, aux;
/*----------------------------*/ /** Path */
bool good[MAX_N];
vector< int > path;
/*----------------------------*/

void noChance() {
   printf("No chance\n"); exit(0);
}

void readData() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        graph[u].push_back(v); graph[v].push_back(u);
    }
    scanf("%d%d%d", &S, &E, &Q);
}

void addComponent(int node, int son) {
    if(!mustVisit[son]) {
        while(Stack.top() != son) {
            Stack.pop();
        }
        Stack.pop(); return;
    }

    criticals.push_back(node);
    while(Stack.top() != son) {
        aux.push_back(Stack.top()); Stack.pop();
    }
    Stack.pop();
    aux.push_back(son); aux.push_back(node);

    comps.push_back(aux); aux.clear();
}

void DFS(int node = E, int father = 0) {
    checked[node] = true;
    biconnectedDP[node] = level[node] = level[father] + 1;
    for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
        if(*it != father) {
            if(checked[*it]) {
                biconnectedDP[node] = min(biconnectedDP[node], level[*it]);
            } else {
                Stack.push(*it);
                DFS(*it, node);
                mustVisit[node] |= mustVisit[*it];
                biconnectedDP[node] = min(biconnectedDP[node], biconnectedDP[*it]);
                if(biconnectedDP[*it] >= level[node]) {
                    addComponent(node, *it);
                }
            }
        }
    }
}

bool Find(vector< int > &vec, int value) {
    for(vector< int >::iterator it = vec.begin(); it != vec.end(); it++) {
        if(*it == value) {
            return true;
        }
    }
    return false;
}

void Orientate() {
    if(!mustVisit[E]) {
        noChance();
    }

    if(!Find(comps[1], Q)) { /* if maxDamage is not in the first component, then we have to reverse the order of the components */
        reverse(comps.begin() + 1, comps.end());
        reverse(criticals.begin(), criticals.end());
    }

    if(!Find(comps[1], Q)) {
        noChance();
    }

    criticals[0] = Q;
    criticals.back() = 0; /* we want to start from Q */
}

bool Back(int limit, int current, int node, int last) {
    checked[node] = true;
    if(current > 1) {
        path.push_back(node);
    }

    if(current == limit) {
        if(!last || node == last) {
            return true;
        }
        checked[node] = false;
        path.pop_back();
        return false;
    } else {
        for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
            if(good[*it] && !checked[*it] && (*it != last || current == limit - 1) && Back(limit, current + 1, *it, last)) {
                return true;
            }
        }
        checked[node] = false; path.pop_back();
        return false;
    }
}

void solveComponent(int index, int first, int last) {
    for(vector< int >::iterator it = comps[index].begin(); it != comps[index].end(); it++) {
        checked[*it] = false; good[*it] = true;
    }
    if(!Back((int)comps[index].size(), 1, first, last)) {
        noChance();
    }
    for(vector< int >::iterator it = comps[index].begin(); it != comps[index].end(); it++) {
        good[*it] = false;
    }
}

void getPath() {
    for(int i = 1; i < (int)comps.size(); i++) {
        solveComponent(i, criticals[i - 1], criticals[i]);
    }
}

void writeData() {
    printf("%d\n", (int)path.size());
    for(vector< int >::iterator it = path.begin(); it != path.end(); it++) {
        printf("%d ", *it);
    }
}

int main() {
    readData();
    mustVisit[S] = true;
    criticals.push_back(S); comps.resize(1);
    DFS();
    Orientate(); /* maxDamage has to be in the first or the last biconnected component */
    path.push_back(Q);
    getPath();
    writeData();
    return 0;
}
