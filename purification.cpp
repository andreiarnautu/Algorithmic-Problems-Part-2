/**
  *  Worg
  */
#include <deque>
#include <cstdio>
#include <vector>
#include <utility>

#define Root (N)

using namespace std;
FILE *fin = freopen("purification.in", "r", stdin);
FILE *fout = freopen("purification.out", "w", stdout);

const int MAX_N = 1 + 2000;
const int MAX_INF = 0x3fffffff;

int N;
int cost[MAX_N];
/*------- Graph stuff --------*/
vector< int > graph[MAX_N];
deque< int > list[MAX_N];
int dp[MAX_N][MAX_N];
pair< int,int > before[MAX_N][MAX_N];
/*---------------*/

void readInput() {
    scanf("%d", &N);
    for(int i = 0; i < N; i++) {
        scanf("%d", &cost[i]);
    }
    for(int i = 0; i < N; i++) {
        int father; scanf("%d", &father);
        if(father == -1) {
            graph[Root].push_back(i);
        } else {
            graph[father].push_back(i);
        }
    }
}

void mergeLists(deque< int > &p, deque< int > &q) {
    int sizeP = (int)p.size();
    int sizeQ = (int)q.size();

    /* initializam dinamica */
    for(int i = 0; i <= sizeP; i++) {
        for(int j = 0; j <= sizeQ; j++) {
            dp[i][j] = MAX_INF;
        }
    }
    /* construim dinamica */
    for(int i = 0; i <= sizeP; i++) {
        for(int j = 0; j <= sizeQ; j++) {
            int coef = (i + j);
            if(i == 0 && j == 0) {
                dp[i][j] = 0;
            } else if(i == 0) {
                dp[i][j] = dp[i][j - 1] + coef * cost[q[j - 1]];
                before[i][j] = make_pair(i, j - 1);
            } else if(j == 0) {
                dp[i][j] = dp[i - 1][j] + coef * cost[p[i - 1]];
                before[i][j] = make_pair(i - 1, j);
            } else {
                if(dp[i - 1][j] + coef * cost[p[i - 1]] < dp[i][j]) {
                    dp[i][j] = dp[i - 1][j] + coef * cost[p[i - 1]];
                    before[i][j] = make_pair(i - 1, j);
                }
                if(dp[i][j - 1] + coef * cost[q[j - 1]] < dp[i][j]) {
                    dp[i][j] = dp[i][j - 1] + coef * cost[q[j - 1]];
                    before[i][j] = make_pair(i, j - 1);
                }
            }

        }
    }

    deque< int > New;
    pair< int,int > now = make_pair(sizeP, sizeQ);
    pair< int,int > null = make_pair(0, 0);

    while(now != null) {
        pair< int,int > previous = before[now.first][now.second];
        if(previous.first == now.first - 1) {
            New.push_front(p[previous.first]);
        } else {
            New.push_front(q[previous.second]);
        }
        now = previous;
    }
    p = New;
}

void DFS(int node) {
    deque< int > current;
    for(int son : graph[node]) {
        DFS(son);
        mergeLists(current, list[son]);
    }

    if(node != Root) {
        current.push_front(node);
    }
    list[node] = current;
}

void writeOutput() {
    int coef = 0;
    int Solution = 0;
    for(int node : list[Root]) {
        coef ++;
        Solution += cost[node] * coef;
    }
    printf("%d\n", Solution);
}

int main() {
    readInput();
    DFS(Root);
    writeOutput();
    return 0;
}
