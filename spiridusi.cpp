/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("spiridusi.in", "r", stdin);
FILE *fout = freopen("spiridusi.out", "w", stdout);

const int MAX_N = 1 + 100000;

vector <int> G[MAX_N];
int s[MAX_N], p[MAX_N];
int N, C;

int father[MAX_N];
int ancestor[MAX_N][20], dp[MAX_N][20];

int stack[MAX_N], pSum[MAX_N], sSum[MAX_N];
int stackSize;

int sol = -MAX_N;

void readData() {
    scanf("%d%d", &N, &C);
    for(int i = 1; i <= N; ++i) {
        scanf("%d", &s[i]);
    }
    for(int i = 1; i <= N; ++i) {
        scanf("%d", &p[i]);
    }
    for(int i = 1; i < N; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        G[u].push_back(v); G[v].push_back(u);
    }
}

void initDFS(int node) {
    ancestor[node][0] = father[node];
    for(int i = 1; i < 19 && ancestor[node][i - 1] != 0; ++i) {
        ancestor[node][i] = ancestor[ancestor[node][i - 1]][i - 1];
    }
    for(vector <int>::iterator it = G[node].begin(); it != G[node].end(); ++it) {
        if(*it != father[node]) {
            father[*it] = node;
            initDFS(*it);
        }
    }
}

int binarySearch() {
    int answer = stackSize + 1, left = 1, right = stackSize;

    while(left <= right) {
        int mid = (left + right) >> 1;
        if(sSum[stackSize] - sSum[mid - 1] <= C) {
            answer = mid; right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return answer;
}

void finalDFS(int node) {
    stackSize++;
    stack[stackSize] = node;
    pSum[stackSize] = pSum[stackSize - 1] + p[node];
    sSum[stackSize] = sSum[stackSize - 1] + s[node];

    dp[node][0] = pSum[stackSize - 1];
    for(int i = 1; i < 19 ; ++i) {
        dp[node][i] = min(dp[node][i - 1], dp[ancestor[node][i - 1]][i - 1]);
    }

    int pos = binarySearch();
    if(pos <= stackSize) {

        if(pos == stackSize) {
            int current = p[node];
            sol = max(current, sol);
        }
        else {
            int i = 0;
            while(1 << (i + 1) <= stackSize - pos + 1) {
                i++;
            }
            int current = pSum[stackSize] - min(dp[node][i], dp[stack[pos + (1 << i) - 1]][i]);
            sol = max(sol, current);
        }
    }

    for(vector <int>::iterator it = G[node].begin(); it != G[node].end(); ++it) {
        if(*it != father[node]) {
            finalDFS(*it);
        }
    }
    stackSize--;
}

int main() {
    readData();
    initDFS(1);
    finalDFS(1);
    printf("%d", sol);
    return 0;
}
