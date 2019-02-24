/**
  *  Worg
  */
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("smen.in", "r", stdin);
FILE *fout = freopen("smen.out", "w", stdout);

const int MAX_N = 700;
const int MAX_DIF = 400;
const int MAX_INF = 0x3fffffff;

/*--------------------*/
int a[MAX_N];
int N, K, A, B;
/*--------------------*/ /** Min cost max flow */
vector< int > graph[MAX_N];
int cap[MAX_N][MAX_N], cost[MAX_N][MAX_N];

queue< int > Q;
bool inQueue[MAX_N];
int dmin[MAX_N], before[MAX_N];
/*--------------------*/ /** Output data */
int solCost;
/*--------------------*/

void readData() {
    scanf("%d%d%d%d", &N, &K, &A, &B);
    for(int i = 1; i <= N; i++) {
        int x; scanf("%d", &x);
        a[i] = x;
        for(int j = A; j <= B; j++) {
            int index = N + 1 + j - A;
            cap[i][index] = 1;
            cost[i][index] = abs(j - x);
            cost[index][i] = -abs(j - x);
            graph[i].push_back(index);
            graph[index].push_back(i);
        }
    }

    const int S1 = N + MAX_DIF + 2;
    const int S2 = N + MAX_DIF + 3;
    const int D = N + MAX_DIF + 4;

    cap[S1][S2] = K;
    graph[S1].push_back(S2); graph[S2].push_back(S1);
    for(int i = 1; i <= N; i++) {
        cap[S2][i] = 1;
        graph[S2].push_back(i); graph[i].push_back(S2);
    }
    for(int i = A; i <= B; i++) {
        int index = N + 1 + i - A;
        cap[index][D] = 1;
        graph[index].push_back(D); graph[D].push_back(index);
    }
}

bool BFS() {
    const int S1 = N + MAX_DIF + 2;
    const int S2 = N + MAX_DIF + 3;
    const int D = N + MAX_DIF + 4;

    for(int i = 1; i <= D; i++) {
        dmin[i] = MAX_INF;
    }
    dmin[S1] = 0; Q.push(S1);

    while(!Q.empty()) {
        int node = Q.front(); Q.pop(); inQueue[node] = false;
        for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
            if(cap[node][*it] && dmin[*it] > dmin[node] + cost[node][*it]) {
                dmin[*it] = dmin[node] + cost[node][*it];
                before[*it] = node;
                if(!inQueue[*it]) {
                    Q.push(*it); inQueue[*it] = true;
                }
            }
        }
    }

    if(dmin[D] == MAX_INF) {
        return false;
    } else {
        int flow = MAX_INF;
        for(int node = D; node != S1; node = before[node]) {
            flow = min(flow, cap[before[node]][node]);
        }
        for(int node = D; node != S1; node = before[node]) {
            solCost += cost[before[node]][node] * flow;
            cap[before[node]][node] -= flow;
            cap[node][before[node]] += flow;
        }

        return true;
    }
}

int getNumber(int x) {
    int answer = a[x];
    for(int i = A; i <= B; i++) {
        int index = N + 1 + i - A;
        if(cap[x][index] == 0) {
            answer = i;
        }
    }
    return answer;
}

void writeData() {
    printf("%d\n", solCost);
    for(int i = 1; i <= N; i++) {
        printf("%d ", getNumber(i));
    }
}

int main() {
    readData();
    while(BFS());
    writeData();
    return 0;
}
