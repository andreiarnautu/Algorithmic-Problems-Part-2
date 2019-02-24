/**
  *  Worg
  */
#include <cstdio>
#include <limits>
#include <vector>
#include <algorithm>

FILE *fin = freopen("tricolor.in", "r", stdin); FILE *fout = freopen("tricolor.out", "w", stdout);

static const int INF = std::numeric_limits<int >::max() / 3;
static const int MAX_N = 5000 + 5;

/*-------- Data --------*/
int n;
std::vector<std::vector<int > > graph;

int dp[MAX_N][MAX_N];

std::vector<int > subtree_size;
/*-------- --------*/

void ReadInput() {
  scanf("%d", &n); 
  
  subtree_size = std::vector<int >(n + 1, 0); graph = std::vector<std::vector<int > >(n + 1);

  for(int i = 1; i < n; i++) {
    int u, v; scanf("%d%d", &u, &v); 
    graph[u].push_back(v); graph[v].push_back(u);
  }
}

void UpdateDp(int node, int son) {
  //  If the current node is chosen to be black
  for(int total_white = subtree_size[node] + subtree_size[son] - 1; total_white >= 0; total_white--) {
      for(int son_white = std::max(0, total_white - subtree_size[node] + 1); son_white <= std::min(subtree_size[son], total_white); son_white++) {
        int node_white = total_white - son_white;

        dp[node][total_white] = std::max(dp[node][total_white], dp[node][node_white] + dp[son][son_white] + node_white * son_white);
      }
  }

  //  Update the subtree size
  subtree_size[node] += subtree_size[son];
}

void DFS(int node, int dad = 0) {
  int total_size = 1;
  for(auto& son : graph[node]) {
    if(son == dad) continue;

    DFS(son, node);

    total_size += subtree_size[son];
  }

  for(int i = 0; i <= total_size; i++) {
    dp[node][i] = -INF;
  }
  subtree_size[node] = 1;
  dp[node][0] = dp[node][1] = 0;

  //  If the current node is chosen to be black
  for(auto& son : graph[node]) {
    if(son == dad) continue;

    UpdateDp(node, son);
  }

  //  If the current node is chosen to be white
  int best = 0;
  for(auto& son : graph[node]) {
    if(son == dad) continue;

    int best_here = 0;
    for(int i = 0; i <= subtree_size[son]; i++) {
      best_here = std::max(best_here, dp[son][i] + i);
    }

    best += best_here;
  }
  dp[node][1] = std::max(dp[node][1], best);
}

int TestAnswer() {
  int ans = 0;
  for(int i = 0; i <= subtree_size[1]; i++) {
    ans = std::max(ans, dp[1][i]);
  }

  return ans;
}

int main() {
  int test_count; scanf("%d", &test_count);
  
  for(int i = 0; i < test_count; i++) {
    ReadInput();

    DFS(1);

    printf("%d\n", TestAnswer());
  }
  return 0;
}