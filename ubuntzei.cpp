/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("ubuntzei.in", "r", stdin);
FILE *fout = freopen("ubuntzei.out", "w", stdout);

const int MAX_N = 1 + 2000,
          MAX_K = 16,
          MAX_INF = 0x3fffffff;

class node {

public:
    int vertex, dist;

    node(const int &vertex, const int &dist) {

        this->vertex = vertex, this->dist = dist;
    }
    bool operator <(const node other) const {

        return this->dist > other.dist;
    }
};

vector < node > G[MAX_N];
priority_queue < node > h;

int cost[MAX_K + 2][MAX_K + 2], dp[1 << (MAX_K + 2)][MAX_K + 2];
int vecini[MAX_K + 2];
char bit[1 << (MAX_K + 2)];

int dist[MAX_N];
int nr[MAX_K + 2];
int n, m, k;

void readData() {

    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= k; ++i)
        scanf("%d", &nr[i]);
    nr[0] = 1, nr[k + 1] = n, k += 2;
    for(int i = 1; i <= m; ++i) {

        int u, v, c; scanf("%d%d%d", &u, &v, &c);
        G[u].push_back(node(v, c));
        G[v].push_back(node(u, c));
    }
}

void dijkstra(int start, int ind) {

    for(int i = 1; i <= n; ++i)
        dist[i] = -1;
    dist[start] = 0;

    h.push(node(start, 0));
    while(!h.empty()) {

        node current = h.top(); h.pop();
        if(dist[current.vertex] != -1 && current.vertex != start)
            continue;
        dist[current.vertex] = current.dist;
        for(vector < node >::iterator it = G[current.vertex].begin(); it != G[current.vertex].end(); ++it)
                h.push(node(it->vertex, dist[current.vertex] + it->dist));
    }
    for(int i = 0; i < k; ++i) {

        cost[ind][i] = dist[nr[i]];
        cost[i][ind] = dist[nr[i]];
    }
}

void hamiltonianCycle() {

    int limit = (1 << (k - 1));
    for(int i = 0; i < k; ++i)
        bit[1 << i] = i;

    for(int i = 0; i < k; ++i)
        for(int j = 0; j < k; ++j)
            if(i != j)
                vecini[i] ^= (1 << j);
    for(int i = 0; i < limit; ++i)
        for(int j = 0; j < k; ++j)
            dp[i][j] = MAX_INF;
    dp[0][k - 1] = 0;
    for(int mask = 1; mask < limit; ++mask) {

        int tmpMask = mask;
        while(tmpMask) {

            int newMask = tmpMask & (tmpMask - 1);
            int v = bit[newMask ^ tmpMask];
            tmpMask = newMask;

            int config = vecini[v];
            while(config) {

                int newConfig = config & (config - 1);
                int u = bit[config ^ newConfig];
                config = newConfig;

                dp[mask][v] = min(dp[mask][v], dp[mask ^ (1 << v)][u] + cost[u][v]);
            }
        }
    }

    int sol = MAX_INF;
    int mask = (limit - 1) ^ 1;
    for(int i = 0; i < k - 1; ++i)
        sol = min(sol, dp[mask][i] + cost[i][0]);
    printf("%d", sol);
}

int main() {

    readData();
    for(int i = 0; i < k; ++i)
        dijkstra(nr[i], i);
    if(k == 2)
        printf("%d", cost[1][0]);
    else
        hamiltonianCycle();
    return 0;
}
