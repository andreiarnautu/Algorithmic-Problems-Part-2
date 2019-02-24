/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("sakura.in", "r", stdin);
FILE *fout = freopen("sakura.out", "w", stdout);

const int MAX_N = 1 + 500;

/*-------- Input data --------*/
int testCount;
int N, M;
vector< int > arbA[MAX_N], arbB[MAX_N];
/*-------- DP data --------*/
int dp[MAX_N][MAX_N];
int degreeA[MAX_N], degreeB[MAX_N];
int fatherA[MAX_N], fatherB[MAX_N];
int depthA[MAX_N], depthB[MAX_N];
int subtreeA[MAX_N], subtreeB[MAX_N];

vector< int > listA[MAX_N], listB[MAX_N];
bool hasSolution;

/*-------- Hopcroft Karp --------*/
vector< int > graph[MAX_N];
int left[MAX_N], right[MAX_N];
bool checked[MAX_N];

int Cuplaj;
/*-------- --------*/

void readInput() {
    scanf("%d", &N);
    for(int i = 1; i < N; i++) {
        int u, v; scanf("%d%d", &u, &v);
        arbA[u].push_back(v);
        arbA[v].push_back(u);
    }
    scanf("%d", &M);
    for(int i = 1; i < M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        arbB[u].push_back(v);
        arbB[v].push_back(u);
    }
}

void DFS_A(int node, int father = -1) {
    listA[depthA[node]].push_back(node);
    subtreeA[node] = 1;
    for(int nxt : arbA[node]) {
        if(nxt != father) {
            depthA[nxt] = depthA[node] + 1;
            DFS_A(nxt, node);
            degreeA[node] ++;
            fatherA[nxt] = node;
            subtreeA[node] += subtreeA[nxt];
        }
    }
}

void DFS_B(int node, int father = -1) {
    listB[depthB[node]].push_back(node);
    subtreeB[node] = 1;
    for(int nxt : arbB[node]) {
        if(nxt != father) {
            depthB[nxt] = depthB[node] + 1;
            DFS_B(nxt, node);
            degreeB[node] ++;
            fatherB[nxt] = node;
            subtreeB[node] += subtreeB[nxt];
        }
    }
}

void initializeDP() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(degreeB[j] == 0) {
                dp[i][j] = true;
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

    for(int nxt : graph[node]) {
        if(!right[nxt]) {
            left[node] = nxt;
            right[nxt] = node;
            Cuplaj ++;
            return true;
        }
    }

    for(int nxt : graph[node]) {
        if(pairUp(right[nxt])) {
            left[node] = nxt;
            right[nxt] = node;
            return true;
        }
    }

    return false;
}

void hopcroftKarp(int u, int v) {
    Cuplaj = 0;

    bool ok;
    do {
        for(int i : arbA[u]) {
            checked[i] = false;
        }
        ok = false;
        for(int i : arbA[u]) {
            if(!left[i]) {
                ok |= pairUp(i);
            }
        }
    }while(ok);

    for(int i : arbA[u]) {
        left[i] = 0;
        graph[i].clear();
    }
    for(int i : arbB[v]) {
        right[i] = 0;
    }
}

void compareNodes(int u, int v) {
    if(subtreeA[u] < subtreeB[v] || dp[u][v] == true) {
        return;
    }

    for(int i : arbA[u]) {
        for(int j : arbB[v]) {
            if(i != fatherA[u] && j != fatherB[v] && dp[i][j] == true) {
                graph[i].push_back(j);
            }
        }
    }

    hopcroftKarp(u, v);

    int expected = (int)arbB[v].size();
    if(v != 0) {
        expected --;
    }

    if(Cuplaj == expected) {
        dp[u][v] = true;
    }
}

void runDP() {
    /* cercetam nivelele de jos in sus */
    for(int i = M - 1; i >= 0; i--) {
        if(listA[i].size() > 0 && listB[i].size() > 0) {
            for(int u : listA[i]) {
                for(int v : listB[i]) {
                    compareNodes(u, v);
                }
            }
        }
    }

    if(dp[0][0] == true) {
        hasSolution = true;
    }
}

void clearTestData() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            dp[i][j] = false;
        }
    }

    for(int i = 0; i < N; i++) {
        arbA[i].clear(); listA[i].clear();
        degreeA[i] = subtreeA[i] = depthA[i] = 0;
        fatherA[i] = -1;
    }
    for(int i = 0; i < M; i++) {
        arbB[i].clear(); listB[i].clear();
        degreeB[i] = subtreeB[i] = depthB[i] = 0;
        fatherB[i] = -1;
    }
}

int main() {
    scanf("%d", &testCount);
    fatherA[0] = fatherB[0] = -1;
    for(; testCount > 0; testCount--) {
        readInput();
        if(M > N) {
            printf("-1\n");
            clearTestData();
            continue;
        }
        hasSolution = false;
        DFS_A(0);
        DFS_B(0);
        initializeDP();
        runDP();

        if(hasSolution) {
            printf("%d\n", N - M);
        } else {
            printf("-1\n");
        }

        clearTestData();
    }

    return 0;
}
