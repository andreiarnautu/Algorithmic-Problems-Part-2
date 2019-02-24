/**
  *  Worg
  */
#include <cstdio>
#include <vector>

#define pb push_back

using namespace std;

FILE *fin = freopen("lca.in", "r", stdin); FILE *fout = freopen("lca.out", "w", stdout);

const int MAX_N = 1 + 100000,
          MAX_LOG = 20,
          bufferDim = 10000;

class inputReader {

private:
  char buffer[bufferDim];
  int pos;

  bool digit(char c) {
    return('0' <= c && c <= '9');
  }

public:
  void getBuffer() {
    fread(buffer, 1, bufferDim, stdin);
    pos = 0;
  }

  void getInt(int &nr) {
    nr = 0;

    while(!digit(buffer[pos]))
      if(++pos == bufferDim)
        getBuffer();

    while(digit(buffer[pos])) {
      nr = nr * 10 + buffer[pos] - '0';
      if(++pos == bufferDim)
        getBuffer();
    }
  }
} cin;


vector < int > G[MAX_N];
int rmq[MAX_LOG][MAX_N << 1];
int pos[MAX_N], depth[MAX_N << 1], list[MAX_N << 1], log[MAX_N << 1];
int n, m, k;

void readData() {
  cin.getBuffer();
  cin.getInt(n); cin.getInt(m);

  for(int i = 2; i <= n; ++i) {
    int x;
    cin.getInt(x);
    G[x].pb(i);
  }
}

void dfs(int node, int level) {
  list[++k] = node;
  depth[k] = level;
  pos[node] = k;

  for(vector < int >::iterator it = G[node].begin(); it != G[node].end(); ++it) {
    dfs(*it, level + 1);
    list[++k] = node;
    depth[k] = level;
  }

}

void getRMQ() {
  for(int i = 2; i <= k; ++i)
    log[i] = log[i >> 1] + 1;

  for(int i = 1; i <= k; ++i)
    rmq[0][i] = i;

  for(int i = 1; (1 << i) < k; ++i) {
    int lastPos = k - (1 << i);
    for(int j = 1; j <= lastPos; ++j)
      rmq[i][j] = (depth[rmq[i - 1][j]] < depth[rmq[i - 1][j + (1 << (i - 1))]]) ? rmq[i - 1][j] : rmq[i - 1][j + (1 << (i - 1))];
  }
}

int LCA(int x, int y) {
  int a = pos[x], b = pos[y];
  if(a > b)
    swap(a, b);

  int level = log[b - a + 1];
  return (depth[rmq[level][a]] < depth[rmq[level][b - (1 << level) + 1]]) ? list[rmq[level][a]] : list[rmq[level][b - (1 << level) + 1]];
}

void answerQuery() {
  int x, y;
  cin.getInt(x); cin.getInt(y);
  printf("%d\n", LCA(x, y));
}

int main() {
  readData();
  depth[1] = 1;
  dfs(1, 1);
  getRMQ();
  for(int i = 1; i <= m; ++i)
    answerQuery();
  return 0;
}