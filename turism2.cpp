/**
  *  Worg
  *  Mar 21, 2018
  *  7:23:05 PM
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("turism2.in", "r", stdin); FILE *fout = freopen("turism2.out", "w", stdout);

const int testCount = 12;
const int maxN = 1e5 + 5;
const int kBufferSize = 1e5;

class InputReader {
public:
    char buffer[kBufferSize];
    int cursor;

    void getBuffer() {
      cursor = 0; fread(buffer, 1, kBufferSize, stdin);
    }

    InputReader() {
      getBuffer();
    }

    bool digit(char c) {
      return '0' <= c && c <= '9';
    }

    InputReader& operator >>(int &number) {
      char sgn = '+';
      while(!digit(buffer[cursor])) {
        sgn = buffer[cursor];
        if(++cursor == kBufferSize) {
          getBuffer();
        }
      }

      number = 0;
      while(digit(buffer[cursor])) {
        number = number * 10 + buffer[cursor] - '0';
        if(++cursor == kBufferSize) {
          getBuffer();
        }
      }

      number = (sgn == '-') ? -number : number;

      return *this;
    }
} cin;
/*-------- Data --------*/
int n;
int cost[maxN];
std::vector<std::vector<int > > graph;

int chainDown[maxN][3], bestDown[maxN];
int vec[4];
int sol;
/*-------- --------*/

void ReadData() {
  cin >> n;
  for(int i = 1; i <= n; i++) {
    cin >> cost[i];
  }

  graph = std::vector<std::vector<int > >(n + 1);

  for(int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    graph[u].push_back(v); graph[v].push_back(u);
  }
}

void DFS1(int node, int dad) {
  bestDown[node] = 0;
  chainDown[node][0] = chainDown[node][1] = chainDown[node][2] = 0;

  for(auto& nxt : graph[node]) {
    if(nxt == dad) continue;

    DFS1(nxt, node);

    int x = chainDown[nxt][0] + cost[nxt];
    if(x >= chainDown[node][0]) {
      chainDown[node][2] = chainDown[node][1]; chainDown[node][1] = chainDown[node][0]; chainDown[node][0] = x;
    } else if(x >= chainDown[node][1]) {
      chainDown[node][2] = chainDown[node][1]; chainDown[node][1] = x;
    } else if(x >= chainDown[node][2]) {
      chainDown[node][2] = x;
    }

    bestDown[node] = std::max(bestDown[node], bestDown[nxt]);
  }

  bestDown[node] = std::max(bestDown[node], cost[node] + chainDown[node][0] + chainDown[node][1]);
}

void DFS2(int node, int dad, int chainUp, int bestUp) {
  sol = std::max(sol, bestUp + bestDown[node]);

  int down1 = 0, down2 = 0;
  for(auto& nxt : graph[node]) {
    if(nxt == dad) continue;

    if(bestDown[nxt] > down1) {
      down2 = down1; down1 = bestDown[nxt];
    } else if(bestDown[nxt] > down2) {
      down2 = bestDown[nxt];
    }
  }

  for(auto& nxt : graph[node]) {
    if(nxt == dad) continue;

    int x = chainDown[nxt][0] + cost[nxt];

    int newChainUp = cost[node] + std::max(chainUp, (x == chainDown[node][0]) ? chainDown[node][1] : chainDown[node][0]);

    vec[0] = chainUp;
    if(x == chainDown[node][0]) {
      vec[1] = chainDown[node][1]; vec[2] = chainDown[node][2];
    } else if(x == chainDown[node][1]) {
      vec[1] = chainDown[node][0]; vec[2] = chainDown[node][2];
    } else {
      vec[1] = chainDown[node][0]; vec[2] = chainDown[node][1];
    }

    std::sort(vec, vec + 3);

    int newBestUp = std::max(bestUp, vec[1] + vec[2] + cost[node]);
    if(bestDown[nxt] == down1) {
      newBestUp = std::max(newBestUp, down2);
    } else {
      newBestUp = std::max(newBestUp, down1);
    }

    DFS2(nxt, node, newChainUp, newBestUp);
  }
}

int main() {
  for(int i = 0; i < testCount; i++) {
    ReadData();

    DFS1(1, 0);

    sol = 0;
    DFS2(1, 0, 0, 0);
    printf("%d\n", sol);
  }

  return 0;
}
