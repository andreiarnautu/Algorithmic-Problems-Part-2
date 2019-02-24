/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>

FILE *fin = freopen("sortaret.in", "r", stdin); FILE *fout = freopen("sortaret.out", "w", stdout);

const int maxN = 50000 + 5;

/*-------- Data --------*/
int n, m;
std::vector<std::vector<int > > graph;

int deg[maxN];
std::queue<int > q;

std::vector<int > topSort;
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &m);

  graph.resize(n + 1);

  for(int i = 1; i <= m; i++) {
    int u, v; scanf("%d%d", &u, &v);

    graph[u].push_back(v); deg[v]++;
  }
}

void TopologicalSort() {
  for(int i = 1; i <= n; i++) {
    if(!deg[i]) {
      q.push(i);
    }
  }

  while(!q.empty()) {
    int node = q.front(); q.pop();

    topSort.push_back(node);

    for(auto& nxt : graph[node]) {
      deg[nxt]--;

      if(!deg[nxt]) q.push(nxt);
    }
  }

  for(auto& itr : topSort) {
    printf("%d ", itr);
  }
}

int main() {
  ReadInput();

  TopologicalSort();

  return 0;
}
