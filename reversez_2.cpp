/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

#define leftSon (node << 1)
#define rightSon ((node << 1) + 1)

using namespace std;
FILE *fin = freopen("reversez.in", "r", stdin);
FILE *fout = freopen("reversez.out", "w", stdout);

const int MAX_N = 1 + 300000;
const int MOD = 666013;

/*-------- Input data --------*/
int N, Sigma;
int Lcp[MAX_N];
/*-------- Disjoint sets --------*/
int father[MAX_N];
/*-------- Segment tree --------*/
int STree[MAX_N << 2];
/*-------- Graph data --------*/
vector< int > graph[MAX_N];
queue< int > Q;
bool checked[MAX_N], inQueue[MAX_N];
/*-------- --------*/

void readInput() {
    scanf("%d%d", &N, &Sigma);
    for(int i = 1; i <= N; i++) {
        scanf("%d", &Lcp[i]);
    }
}

int Group(int x) {
    if(x != father[x]) {
        father[x] = Group(father[x]);
    }
    return father[x];
}

void Unite(int x, int y) {
    x = Group(x);
    y = Group(y);
    father[x] = y;
}

void Update(int node, int left, int right, int first, int last, int value) {
    if(first <= left && right <= last) {
        STree[node] = value;
    } else {
        int mid = (left + right) >> 1;
        if(first <= mid) {
            Update(leftSon, left, mid, first, last, value);
        }
        if(mid < last) {
            Update(rightSon, mid + 1, right, first, last, value);
        }
    }
}

void buildSegmentTree() {
    /* primul Lcp nu ne intereseaza fiindca nu ne spune nimic */
    for(int i = 2; i <= N; i++) {
        if(Lcp[i] > 0) {
            Update(1, 1, N, i, i + Lcp[i] - 1, i - 1);
        }
    }
}

void solveSTree(int node, int left, int right) {
    if(left == right) {
        /* am ajuns intr-o frunza */
        Unite(left, left - STree[node]);
    } else {
        /* propagam valoarea nodului curent inspre fii */
        STree[leftSon] = max(STree[leftSon], STree[node]);
        STree[rightSon] = max(STree[rightSon], STree[node]);

        int mid = (left + right) >> 1;
        solveSTree(leftSon, left, mid);
        solveSTree(rightSon, mid + 1, right);
    }
}

void buildGraph() {
    for(int i = 2; i <= N; i++) {
        int u = 1 + Lcp[i];
        int v = i + Lcp[i];

        if(u <= N && v <= N) {
            u = Group(u);
            v = Group(v);

            graph[u].push_back(v);
            graph[v].push_back(u);
        }
    }

    for(int i = 1; i <= N; i++) {
        sort(graph[i].begin(), graph[i].end());
        graph[i].erase(unique(graph[i].begin(), graph[i].end()), graph[i].end());
    }
}

int getSolution() {
    int Solution = 1;

    Q.push(1); inQueue[1] = true;
    while(!Q.empty()) {
        int node = Q.front(); Q.pop();
        checked[node] = true;

        int current = Sigma;
        for(int nxt : graph[node]) {
            if(checked[nxt]) {
                current --;
            } else {
                if(!inQueue[nxt]) {
                    Q.push(nxt); inQueue[nxt] = true;
                }
            }
        }

        Solution = (1LL * Solution * current) % MOD;
    }
    return Solution;
}

int main() {
    readInput();
    buildSegmentTree();
    for(int i = 1; i <= N; i++) {
        /* initializam padurile de multimi disjuncte */
        father[i] = i;
    }
    solveSTree(1, 1, N);
    buildGraph();
    printf("%d", getSolution());
    return 0;
}
