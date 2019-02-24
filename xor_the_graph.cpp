/**
  *  Worg
  */
#include <cstdio>
#include <vector>

FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

/*-------- Data --------*/
int N, M;
std::vector<int > has, seen, deg, used, s, ans, act;
std::vector<std::vector<int > > sol;
std::vector<std::vector<std::pair<int, int > > > graph;

int cursor;
/*-------- --------*/

void AddEdge(int u, int v) {
  graph[u].emplace_back(v, cursor); graph[v].emplace_back(u, cursor);
  cursor++;
}

void DFS(int node) {
  seen[node] = 1;
  for(auto& nxt : graph[node]) {
    if(seen[nxt.first]) continue;
    DFS(nxt.first);
  }
}

int main() {
  scanf("%d%d", &N, &M); has.resize(N + 5); graph.resize(N + 5); deg.resize(N + 5); seen.resize(N + 5);
  for(int i = 0; i < M; i++) {
    int u, v, c; scanf("%d%d%d", &u, &v, &c);

    AddEdge(u, v);
    if(c == 0) {
      AddEdge(u, v);
    } else {
      has[u] = has[v] = 1;
    }
  }

  for(int i = 1; i <= N + 1; i++) {
    if(graph[i].size() % 2 == 1) {
      AddEdge(i, N + 1);
      DFS(i);
    }
    deg[i] = (int)graph[i].size();
  }

  for(int i = 1; i <= N + 1; i++) {
    if(!seen[i] && has[i]) {
      DFS(i);
      AddEdge(i, N + 1); AddEdge(i, N + 1);
    }
    deg[i] = (int)graph[i].size();
  }

  used.resize(cursor);
  s.push_back(N + 1);

  while(!s.empty()) {
    int node = s.back();

    if(deg[node]) {
      if(!used[graph[node].back().second]) {
        used[graph[node].back().second] = 1;
        s.push_back(graph[node].back().first);
      }
      graph[node].pop_back();
      deg[node]--;
    } else {
      ans.push_back(node); s.pop_back();
    }
  }

  for(int i = 1; i < (int)ans.size(); i++) {
    if(ans[i] == N + 1) {
      sol.push_back(act); act.clear();
    } else {
      act.push_back(ans[i]);
    }
  }

  printf("%d\n", (int)sol.size());
  for(auto& vec : sol) {
    printf("%d ", (int)vec.size());
    for(auto& itr : vec) {
      printf("%d ", itr);
    }
    printf("\n");
  }

  return 0;
}
