/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("sabotaj.in", "r", stdin); FILE *fout = freopen("sabotaj.out", "w", stdout);

const int maxN = 1 + 200;
const int inf = 1e9;

/*-------- Data --------*/
int n, m;
std::pair<int, int > a[maxN][maxN];
std::vector<int > graph[maxN];

int cap[maxN][maxN];
int prev[maxN], seen[maxN];
std::queue<int > q;

std::vector<int > cut;
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= m; i++) {
    int u, v, t; scanf("%d%d%d", &u, &v, &t);
    graph[u].push_back(v); graph[v].push_back(u);
    a[u][v] = a[v][u] = {t, i};
  }
}

bool BFS(int beg, int fin) {
  for(int i = 1; i <= n; i++) {
    prev[i] = 0;
  }

  std::queue<int > q;
  prev[beg] = beg; q.push(beg);

  while(!q.empty()) {
    int node = q.front(); q.pop();

    if(node == fin) return true;

    for(auto& nxt : graph[node]) {
      if(!prev[nxt] && cap[node][nxt]) {
        prev[nxt] = node; q.push(nxt);
      }
    }
  }

  return false;
}

int MinCut(int beg, int fin, int current) {
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= n; j++) {
      cap[i][j] = a[i][j].first;
    }
  }

  int flow = 0;
  while(BFS(beg, fin) && flow < current) {
    for(auto& x : graph[fin]) {
      if(prev[x] != 0 && cap[x][fin]) {
        prev[fin] = x;

        int flowHere = inf;
        for(int i = fin; i != beg && flowHere != 0; i = prev[i]) {
          flowHere = std::min(flowHere, cap[prev[i]][i]);
        }
        for(int i = fin; i != beg && flowHere != 0; i = prev[i]) {
          cap[prev[i]][i] -= flowHere; cap[i][prev[i]] += flowHere;
        }

        flow += flowHere;
      }
    }
  }

  return flow;
}

void DFS(int node) {
  seen[node] = true;
  for(auto& nxt : graph[node]) {
    if(seen[nxt] || cap[node][nxt] == 0) continue;

    DFS(nxt);
  }
}

int Solve() {
  int ans = inf;
  for(int i = 2; i <= n; i++) {
    int x = MinCut(1, i, ans);

    if(x < ans) {
      ans = x;
      for(int j = 1; j <= n; j++) {
        seen[j] = false;
      }
      DFS(1);

      cut.clear();
      for(int j = 1; j <= n; j++) {
        for(int k = 1; k <= n; k++) {
          if(seen[j] && !seen[k] && a[j][k].first != 0) {
            cut.push_back(a[j][k].second);
          }
        }
      }
    }
  }

  return ans;
}

int main() {
  ReadInput();

  printf("%d ", Solve()); printf("%d\n", (int)cut.size());
  std::sort(cut.begin(), cut.end());
  for(auto& x : cut) {
    printf("%d\n", x);
  }

  return 0;
}
