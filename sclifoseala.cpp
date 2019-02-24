/**
  *  Worg
  *  Mar 12, 2018
  *  12:12:32 PM
  */
#include <map>
#include <stack>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

FILE *fin = freopen("sclifoseala.in", "r", stdin); FILE *fout = freopen("sclifoseala.out", "w", stdout);

const int maxN = 3e4 + 5;
const int limitSize = 8;

/*-------- Data --------*/
int n, m;
std::vector<int > graph[maxN];
std::map<std::pair<int, int >, int > edgeMap;
/*-------- Biconnected --------*/
int lvl[maxN], dp[maxN];
std::stack<std::pair<int, int > > stk;

std::vector<int > nodes;

long long sol;
int edge[limitSize][limitSize];

int conex[1 << limitSize];
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &m);
  for(int i = 0; i < m; i++) {
    int u, v; scanf("%d%d", &u, &v);

    graph[u].push_back(v); graph[v].push_back(u);

    edgeMap[{u, v}] = edgeMap[{v, u}] = 1;
  }
}

int Bits(int value) {
  int ans = 0;
  for(int i = 0; i <= limitSize; i++) {
    if(value & (1 << i)) {
      ans++;
    }
  }
  return ans;
}

void SolveComponent() {
  if((int)nodes.size() > limitSize) {
    sol += 1LL * nodes.size() * (nodes.size() - 1); return;
  }

  memset(edge, 0, sizeof(edge));
  memset(conex, 0, sizeof(conex));

  for(int i = 0; i < (int)nodes.size(); i++) {
    for(int j = i + 1; j < (int)nodes.size(); j++) {
      if(edgeMap[{nodes[i], nodes[j]}]) {
        edge[i][j] = edge[j][i] = true;
      }
    }
  }

  int limit = (1 << (int)nodes.size()) - 1;

  for(int msk = 1; msk <= limit; msk++) {
    if(Bits(msk) == 1) {
      conex[msk] = true; continue;
    }

    for(int i = 0; i < (int)nodes.size(); i++) {
      if((msk & (1 << i)) && conex[msk - (1 << i)]) {
        bool ok = false;

        for(int j = 0; j < (int)nodes.size(); j++) {
          if(j != i && (msk & (1 << j)) && edge[i][j]) {
            ok = true; break;
          }
        }

        if(ok) {
          conex[msk] = true; break;
        }
      }
    }
  }

  for(int msk = 1; msk < limit; msk++) {
    if(conex[msk] && conex[limit - msk]) {
      sol++;
    }
  }
}

void NewComponent(std::pair<int, int > stop) {
  std::pair<int, int > act;
  do {
    act = stk.top(); stk.pop();
    nodes.push_back(act.first); nodes.push_back(act.second);
  }while(act != stop);

  std::sort(nodes.begin(), nodes.end());
  nodes.erase(std::unique(nodes.begin(), nodes.end()), nodes.end());

  SolveComponent();
  nodes.clear();
}

void DFS(int node, int father) {
  dp[node] = lvl[node];

  for(auto& nxt : graph[node]) {
    if(lvl[nxt]) continue;

    stk.emplace(node, nxt);
    lvl[nxt] = lvl[node] + 1;
    DFS(nxt, node);

    if(dp[nxt] >= dp[node]) {
      NewComponent({node, nxt});
    }
  }

  for(auto& nxt : graph[node]) {
    if(nxt == father) continue;

    dp[node] = std::min(dp[node], dp[nxt]);
  }
}

void Clear() {
  for(int i = 1; i <= n; i++) {
    graph[i].clear();
  }
  edgeMap.clear();
  memset(lvl, 0, sizeof(lvl)); memset(dp, 0, sizeof(dp));
  sol = 0;
}

int main() {
  int t; scanf("%d", &t);

  for(int i = 0; i < t; i++) {
    ReadInput();

    lvl[1] = 1; DFS(1, 0);

    printf("%lld\n", sol);

    Clear();
  }

  return 0;
}
