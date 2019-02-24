/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("pscnv.in", "r", stdin); FILE *fout = freopen("pscnv.out", "w", stdout);

const int kMaxK = 1000;
const int kBufferSize = 100000;

/*-------- Input Reader --------*/
class InputReader {
private:
  char buffer[kBufferSize];
  int pos;

  bool Digit(char c) {
    return('0' <= c && c <= '9');
  }

public:
  void GetBuffer() {
    fread(buffer, 1, kBufferSize, stdin);
    pos = 0;
  }

  InputReader& operator >>(int &nr) {
    nr = 0;
    char c = '+';
    while(!Digit(buffer[pos])) {
      c = buffer[pos];
      if(++pos == kBufferSize) {
        GetBuffer();
      }
    }
    while(Digit(buffer[pos])) {
      nr = nr * 10 + buffer[pos] - '0';
      if(++pos == kBufferSize) {
        GetBuffer();
      }
    }
    if(c == '-') {
      nr = -nr;
    }
    return *this;
  }
} cin;
/*-------- Data --------*/
int N, M, X, Y;
std::vector<std::pair<int, int > > edges[kMaxK + 1];
std::vector<std::vector<std::pair<int, int > > > graph;

std::queue<int > list[kMaxK + 1];
/*-------- --------*/

int main() {
  cin >> N >> M >> X >> Y; X--; Y--;
  graph.resize(N);
  for(int i = 0; i < M; i++) {
    int x, y, k; cin >> x >> y >> k; x--; y--;
    graph[x].push_back({k, y});
  }

  std::vector<int > best(N, -1);
  list[0].push(X);

  int cursor = 0;
  while(cursor <= kMaxK) {
    if(list[cursor].empty()) {
      cursor ++; continue;
    }

    int node = list[cursor].front(); list[cursor].pop();
    if(best[node] != -1) continue;

    if(node == Y) {
      printf("%d\n", cursor); return 0;
    }

    best[node] = cursor;
    for(auto& edge : graph[node]) {
      if(best[edge.second] == -1) {
        list[std::max(cursor, edge.first)].push(edge.second);
      }
    }
  }
    return 0;
}
