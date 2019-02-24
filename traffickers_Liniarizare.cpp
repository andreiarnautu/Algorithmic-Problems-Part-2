/**
  *  Worg
  * 
  *  Solution using a 2D Fenwick-Tree on the tree's linearization
  * 
  *  Complexity: O((K + Q) * log(N) * D * log(D))
  */
#include <cstdio>
#include <vector>

#define lsb(x) (x & (-x))

FILE *fin = freopen("traffickers.in", "r", stdin); FILE *fout = freopen("traffickers.out", "w", stdout);

static const int MAX_N = 30000 + 5;
static const int MAX_D = 20;
static const int MAX_LOG = 17;

/*-------- Data --------*/
int n;
std::vector<std::vector<int > > graph;

int cursor = 0;
int first_app[MAX_N], second_app[MAX_N], depth[MAX_N], father[MAX_N];

int euler_pos[MAX_N], euler_depth[MAX_N * 2], euler_list[MAX_N * 2], log2[MAX_N * 2];
int rmq[MAX_LOG][MAX_N * 2];

int rhs[MAX_D], lhs[MAX_D];
/*-------- Structures --------*/
struct Fenwick {
public:
  int f[MAX_D + 1][MAX_N * 2];
  int d;

  void Set(const int d) {
    this->d = d;
  }
  
  void Add(int x, int y, int add) {
    x++;
    for(int i = x; i <= d; i += lsb(i)) {
      for(int j = y; j <= 2 * n; j += lsb(j)) {
        f[i][j] += add;
      }
    }
  }

  long long Query(int x, int y) {
    long long answer = 0;

    x++;
    for(int i = x; i > 0; i -= lsb(i)) {
      for(int j = y; j > 0; j -= lsb(j)) {
        answer += f[i][j];
      }
    }

    return answer;
  }
} fenwick[MAX_D + 1];
/*-------- --------*/  

void ReadGraph() {
  scanf("%d", &n); graph.resize(n + 1);
  for(int i = 1; i < n; i++) {
    int u, v; scanf("%d%d", &u, &v);

    graph[u].push_back(v); graph[v].push_back(u);
  }
}

void LinearizationDFS(int node, int dad = 0) {
  cursor++; first_app[node] = cursor; depth[node] = depth[dad] + 1;
  father[node] = dad;

  for(auto& son : graph[node]) {
    if(son == dad) continue;

    LinearizationDFS(son, node);
  }

  cursor++; second_app[node] = cursor;
}

void EulerDFS(int node, int dad = 0) {
  cursor++;

  euler_list[cursor] = node;
  euler_depth[cursor] = depth[node];
  euler_pos[node] = cursor;

  for(auto& son : graph[node]) {
    if(son == dad) continue;

    EulerDFS(son, node);
    cursor++;

    euler_list[cursor] = node;
    euler_depth[cursor] = depth[node];
  }
}

void ComputeRMQ() {
  for(int i = 2; i <= cursor; i++) {
    log2[i] = log2[i >> 1] + 1;
  }
  for(int i = 1; i <= cursor; i++) {
    rmq[0][i] = i;
  }

  for(int i = 1; (1 << i) <= cursor; i++) {
    int last_index = cursor - (1 << i) + 1;
    int offset = 1 << (i - 1);

    for(int j = 1; j <= last_index; j++) {
      if(euler_depth[rmq[i - 1][j]] < euler_depth[rmq[i - 1][j + offset]]) {
        rmq[i][j] = rmq[i - 1][j];
      } else {
        rmq[i][j] = rmq[i - 1][j + offset];
      }
    }
  }
}

int LCA(int u, int v) {
  int a = euler_pos[u], b = euler_pos[v];
  if(a > b) std::swap(a, b);

  int level = log2[b - a + 1];
  int offset = (1 << level) - 1;
  
  if(depth[rmq[level][a]] < depth[rmq[level][b - offset]]) {
    return euler_list[rmq[level][a]];
  } else {
    return euler_list[rmq[level][b - offset]];
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

  for(int i = 0; i < p1; i++) {
    int node = lhs[i];

    fenwick[dist].Add(x, first_app[node], +1);
    fenwick[dist].Add(x, second_app[node], -1);

    x++;
  }
  for(int i = p2 - 1; i >= 0; i--) {
    int node = rhs[i];

    fenwick[dist].Add(x, first_app[node], +1);
    fenwick[dist].Add(x, second_app[node], -1);

    x++;
  }
}

void AddInitialTraffickers() {
  for(int i = 1; i <= MAX_D; i++) {
    fenwick[i].Set(i);
  }

  int k; scanf("%d", &k);

  for(int i = 0; i < k; i++) {
    int u, v; scanf("%d%d", &u, &v);
    AddTrafficker(u, v, +1);
  }
}

long long QueryPrefix(int d, int idx, int rest, int complete_cycles) {
  long long answer = complete_cycles * fenwick[d].Query(d - 1, idx);
  answer += fenwick[d].Query(rest, idx);

  return answer;
}

long long Compute(int u, int v, int t) {
  if(t < 0) return 0;

  int lca = LCA(u, v);

  long long answer = 0;
  for(int i = 1; i <= MAX_D; i++) {
    int rest = t % i, complete_cycles = t / i;

    long long query_u = QueryPrefix(i, first_app[u], rest, complete_cycles);
    long long query_v = QueryPrefix(i, first_app[v], rest, complete_cycles);
    long long query_lca = QueryPrefix(i, first_app[lca], rest, complete_cycles);
    long long query_prev = QueryPrefix(i, first_app[lca] - 1, rest, complete_cycles);

    long long here = query_u + query_v - 2 * query_lca + (query_lca - query_prev);
    answer += here;
  }

  return answer;
}

void ProcessOperations() {
  int q; scanf("%d", &q);

  for(int i = 0; i < q; i++) {
    int type, u, v; scanf("%d%d%d", &type, &u, &v);

    if(type == 1) {
      AddTrafficker(u, v, +1);
    } else if(type == 2) {
      AddTrafficker(u, v, -1);
    } else {
      int t1, t2; scanf("%d%d", &t1, &t2);

      long long answer = Compute(u, v, t2) - Compute(u, v, t1 - 1);
      printf("%lld\n", answer);
    }
  }
}

int main() {
  ReadGraph();
  cursor = 0; LinearizationDFS(1);
  cursor = 0; EulerDFS(1);
  ComputeRMQ();
  AddInitialTraffickers();
  ProcessOperations();
  return 0;
}