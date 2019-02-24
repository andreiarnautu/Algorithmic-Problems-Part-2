/**
  *  Worg
  */
#include <stack>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("ratway.in", "r", stdin); FILE *fout = freopen("ratway.out", "w", stdout);

const int maxN = 1e5 + 5;

/*-------- Data --------*/
int n, m;
std::vector<std::pair<int, int > > graph[maxN];

int deg[maxN];
int edgeCount;
/*-------- Euler --------*/
std::stack<int > st;
std::vector<int > cycle, seen;
/*-------- --------*/

void NewEdge(int u, int v) {
  edgeCount++;

  graph[u].emplace_back(v, edgeCount); graph[v].emplace_back(u, edgeCount);

  deg[u]++; deg[v]++;
}

void ReadInput() {
  scanf("%d%d", &n, &m);
  for(int i = 0; i < m; i++) {
    int u, v; scanf("%d%d", &u, &v);

    NewEdge(u, v);
  }

  int prev = -1;

  for(int i = 1; i <= n; i++) {
    if(deg[i] & 1) {
      if(prev == -1) {
        prev = i;
      } else {
        NewEdge(prev, i); prev = -1;
      }
    }
  }

  if(edgeCount & 1) {
    NewEdge(1, 1);
  }
}

int PopBack(int node) {
  while(!graph[node].empty() && seen[graph[node].back().second]) {
    graph[node].pop_back();
  }

  int nxt = graph[node].back().first; seen[graph[node].back().second] = true;

  deg[node]--; deg[nxt]--;

  return nxt;
}

void EulerianCycle() {
  seen = std::vector<int >(edgeCount + 1, false);

  st.push(1);
  while(!st.empty()) {
    int node = st.top();

    if(deg[node]) {
      int nxt = PopBack(node); st.push(nxt);
    } else {
      st.pop(); cycle.push_back(node);
    }
  }

  printf("%d\n", edgeCount);
  for(int i = 1; i < (int)cycle.size(); i += 2) {
    printf("%d %d\n", cycle[i], cycle[i - 1]);
    printf("%d %d\n", cycle[i], cycle[i + 1]);
  }
}

int main() {
  ReadInput();

  EulerianCycle();
  return 0;
}
