/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;
FILE *fin = freopen("renovare.in", "r", stdin);
FILE *fout = freopen("renovare.out", "w", stdout);

const int MAX_N = 1 + 200 + 10;
const int MAX_INF = 10000000;

/*----------------------------------------*/
int N, M, X;
int cap[MAX_N][MAX_N], cap_B[MAX_N][MAX_N], cost[MAX_N][MAX_N];
vector< int > graph[MAX_N];
/*----------------------------------------*/
queue< int > Q;
bool inQueue[MAX_N];
int dmin[MAX_N], before[MAX_N];
/*----------------------------------------*/
int solCost;


void readData() {
    scanf("%d%d%d", &N, &M, &X);
    for(int i = 1; i <= M; i++) {
        int a, b, c, cst; scanf("%d%d%d%d", &a, &b, &c, &cst);

        assert(1 <= a && a <= N); assert(1 <= b && b <= N);
        assert(0 <= cst);

        graph[a].push_back(b); graph[b].push_back(a);
        cap[a][b] += c; cap_B[a][b] = MAX_INF; cost[a][b] += cst;
    }

    graph[0].push_back(1); graph[1].push_back(0);
    cap[0][1] = X;
}

bool bellmanFord() {
    const int S = 0;
    const int D = N;

    for(int i = S; i <= D; i++) {
        dmin[i] = MAX_INF;
    }
    dmin[S] = 0; Q.push(S);

    while(!Q.empty()) {
        int node = Q.front(); Q.pop(); inQueue[node] = false;

        for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
            if(cap[node][*it] > 0 || cap_B[node][*it] > 0) {
                int add = 0;
                if(!cap[node][*it]) {
                    add = cost[node][*it];
                }
                if(dmin[*it] > dmin[node] + add) {
                    dmin[*it] = dmin[node] + add;
                    before[*it] = node;
                    if(!inQueue[*it]) {
                        Q.push(*it); inQueue[*it] = true;
                    }
                }
            }
        }
    }

    if(dmin[D] == MAX_INF) {
        return false;
    } else {
        int flow = MAX_INF;
        int crtCost = 0;

        for(int node = D; node != S; node = before[node]) {
          //  printf("%d %d\n", before[node], node);
            if(cap[before[node]][node]) {
                flow = min(flow, cap[before[node]][node]);
            } else {
                flow = min(flow, cap_B[before[node]][node]);
            }
        }

        for(int node = D; node != S; node = before[node]) {
            if(cap[before[node]][node]) {
                cap[before[node]][node] -= flow;
                cap[node][before[node]] += flow;
            } else {
                crtCost += cost[before[node]][node] * flow;
                cap_B[before[node]][node] -= flow;
                cap_B[node][before[node]] += flow;
            }
        }

        solCost += crtCost;
        //printf("%d\n---------------\n", crtCost);
        return true;
    }
}

void writeData() {
    printf("%d", solCost);
}

int main() {
    readData();
    while(bellmanFord());
    writeData();
    return 0;
}
