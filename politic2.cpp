/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("politic2.in", "r", stdin);
FILE *fout = freopen("politic2.out", "w", stdout);

const int MAX_N = 1 + 1000;
const int Root = 0;

/*------------------------*/
int N;
int vote[MAX_N];
vector< int > graph[MAX_N];
/*------------------------*/
int checked[MAX_N], cycleSize[MAX_N];
bool isRoot[MAX_N], inCycle[MAX_N];
/*------------------------*/
bool used[MAX_N];
int weight[MAX_N];
int dp[MAX_N][MAX_N];


void readInput() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        scanf("%d", &vote[i]);
        graph[vote[i]].push_back(i);
    }
}

void detectCycles() {
    for(int i = 1; i <= N; i++) {
        if(!checked[i]) {
            checked[i] = i;

            int node = i;
            while(!checked[vote[node]]) {
                node = vote[node];
                checked[node] = i;
            }

            if(checked[vote[node]] == i) { /* daca avem ciclu */
                isRoot[node] = true;
                graph[Root].push_back(node);

                int crtNode = node, crtCycleSize = 0;
                do {
                    inCycle[crtNode] = true;
                    crtCycleSize ++;

                    if(crtNode != node) {
                        for(int nxtNode : graph[crtNode]) {
                            graph[node].push_back(nxtNode); /* reunim toti fiii nodurilor din ciclul curent */
                        }
                    }

                    crtNode = vote[crtNode];
                }while(crtNode != node);

                cycleSize[node] = crtCycleSize;
            }
        }
    }
}

void runDP(int node) {
    /* node poate sa fie doar: capul unui ciclu sau un nod care nu se afla in ciclu */

    used[node] = true;
    int subtreeSize, sons = 0;

    if(inCycle[node]) {
        subtreeSize = cycleSize[node];
    } else {
        subtreeSize = 1;
    }

    /* caz particular : node este radacina fictiva */
    if(node == Root) {
        subtreeSize = 0;
    }

    for(int nxtNode : graph[node]) {
        if(!used[nxtNode] && (!inCycle[nxtNode] || isRoot[nxtNode])) {
            sons ++;
        }
    }

    if(node != Root) {
        dp[node][subtreeSize] = sons;
        if(inCycle[node]) {
            dp[node][subtreeSize] += subtreeSize;
        }
    }

    weight[node] = subtreeSize;

    for(int nxtNode : graph[node]) {
        if(!used[nxtNode] && (!inCycle[nxtNode] || isRoot[nxtNode])) {
            runDP(nxtNode);
            weight[node] += weight[nxtNode];

            for(int i = weight[node]; i >= subtreeSize; i--) {
                for(int j = subtreeSize; j < i && j <= weight[node] - weight[nxtNode]; j++) {
                    dp[node][i] = max(dp[node][i], dp[node][j] + dp[nxtNode][i - j]);
                }
            }
        }
    }
}

void writeOutput() {
    int Answer = 0;
    for(int i = 1; i <= N; i++) {
        Answer = max(min(Answer + 1, N), dp[Root][i]);
        printf("%d\n", N - Answer);
    }
}

int main() {
    readInput();
    detectCycles();
    runDP(Root);
    writeOutput();

    return 0;
}
