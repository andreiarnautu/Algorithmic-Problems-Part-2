/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>

using namespace std;
FILE *fin = freopen("radare.in", "r", stdin);
FILE *fout = freopen("radare.out", "w", stdout);

const int MAX_N = 1 + 3000 + 1;
const int MAX_P = 1 + 3500;
const int MOD = 31333;
const int Root = 1;

/*-------------------------*/
int N, P;
int Time[MAX_N];
vector< int > graph[MAX_N];
/*-------------------------*/
pair< int,int > where[MAX_N];
int crtIndex, subTree[MAX_N];

int Pow[MAX_N];
int dp[MAX_N][MAX_P];
/*-------------------------*/

void readInput() {
    scanf("%d%d", &N, &P);
    for(int i = 1; i < N; i++) {
        int u, v; scanf("%d%d", &u, &v);
        graph[u].push_back(v); graph[v].push_back(u);
    }
    for(int i = 1; i <= N; i++) {
        scanf("%d", &Time[i]);
    }
}

void DFS(int node = Root, int father = 0) {
    ++crtIndex;
    int now = crtIndex;
    where[now].first = node;

    subTree[node] = 1;
    for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
        if(*it != father) {
            DFS(*it, node);
            subTree[node] += subTree[*it];
        }
    }
    where[now].second = crtIndex + 1;
}

void getPow() {
    Pow[0] = 1;
    for(int i = 1; i <= N; i++) {
        Pow[i] = Pow[i - 1] << 1;
        Pow[i] %= MOD;
    }
}

void runDP() {
    dp[1][0] = 1;
    for(int pos = 1; pos <= N; pos++) {
        for(int sum = 0; sum <= P; sum++) {
            if(dp[pos][sum] > 0) {
                int Node = where[pos].first;
                if(sum + Time[Node] <= P) {
                    dp[pos + 1][sum + Time[Node]] += dp[pos][sum];
                    dp[pos + 1][sum + Time[Node]] %= MOD;
                }

                dp[where[pos].second][sum] += (dp[pos][sum] * Pow[subTree[Node] - 1]);
                dp[where[pos].second][sum] %= MOD;
            }
        }
    }

    printf("%d", dp[N + 1][P]);
}

int main() {
    readInput();
    DFS();
    getPow();
    runDP();

    return 0;
}
