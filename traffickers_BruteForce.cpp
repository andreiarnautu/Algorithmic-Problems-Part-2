/**
  *  Worg
  * 
  *  Brute Force Algorithm
  * 
  *  Complexity: O(K * D + Q * N * D^2)
  */
#include <cstdio>
#include <vector>

FILE *fin = freopen("traffickers.in", "r", stdin); FILE *fout = freopen("traffickers.out", "w", stdout);

static const int MAX_N = 30000 + 5;
static const int MAX_D = 20;

/*-------- Data --------*/
int n;
std::vector<std::vector<int > > graph;

int depth[MAX_N], father[MAX_N];
int lhs[MAX_D], rhs[MAX_D];

int count[MAX_N][MAX_D + 1][MAX_D + 1];
int arr[MAX_N];
/*-------- --------*/

void ReadGraph() {
  scanf("%d", &n); graph.resize(n + 1);

  for(int i = 1; i < n; i++) {
    int u, v; scanf("%d%d", &u, &v);

    graph[u].push_back(v); graph[v].push_back(u);
  }
}

void DFS(int node, int dad = 0) {
  depth[node] = depth[dad] + 1;
  father[node] = dad;

  for(auto& son : graph[node]) {
    if(son == dad) continue;

    DFS(son, node);
  }
}

void AddTrafficker(int u, int v, int add) {
  int p1 = 0, p2 = 0;

  while(u != v) {
    if(depth[u] > depth[v]) {
      lhs[p1++] = u; u = father[u];
    } else {
      rhs[p2++] = v; v = father[v];
    }
  }
  lhs[p1++] = u;

  int dist = p1 + p2, x = 0;

  //printf("Traficant cu dist = %d\n", dist);

  for(int i = 0; i < p1; i++) {
    count[lhs[i]][dist][x] += add;
    //printf("Nodul %d, restul %d\n", lhs[i], x);
    x++;
  }
  for(int i = p2 - 1; i >= 0; i--) {
    count[rhs[i]][dist][x] += add;
    //printf("Nodul %d, restul %d\n", rhs[i], x);
    x++;
  }
}

void AddInitialTraffickers() {
  int k; scanf("%d", &k);

  for(int i = 0; i < k; i++) {
    int u, v; scanf("%d%d", &u, &v);

    AddTrafficker(u, v, +1);
  }
}

long long Compute(int u, int v, int t) {
  if(t < 0) return 0;

  int p = 0;
  while(u != v) {
    if(depth[u] > depth[v]) {
      arr[p++] = u; u = father[u];
    } else {
      arr[p++] = v; v = father[v];
    }
  }
  arr[p++] = u;
/*
  printf("Query pe nodurile: ");
  for(int i = 0; i < p; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
*/
  long long answer = 0;
  for(int d = 1; d <= MAX_D; d++) {
    int rest = t % d, complete_cycles = t / d;

    for(int i = 0; i < p; i++) {
      int node = arr[i];

      for(int j = 0; j <= rest; j++) {
        answer += count[node][d][j];
      }
      for(int j = 0; j < d; j++) {
        answer += 1LL * complete_cycles * count[node][d][j];
      }
    }
  }

  return answer;
}

void ProcessOperations() {
  int q; scanf("%d", &q);
  
  for(int i = 0; i < q; i++) {
    int type; scanf("%d", &type);

    if(type == 1) {
      int u, v; scanf("%d%d", &u, &v);
      AddTrafficker(u, v, +1);
    } else if(type == 2) {
      int u, v; scanf("%d%d", &u, &v);
      AddTrafficker(u, v, -1);
    } else {
      int u, v, t1, t2; scanf("%d%d%d%d", &u, &v, &t1, &t2);

      long long answer = Compute(u, v, t2) - Compute(u, v, t1 - 1);
      printf("%lld\n", answer);
    }
  }
}

int main() {
  ReadGraph();
  DFS(1);
  AddInitialTraffickers();
  ProcessOperations();
  return 0;
}