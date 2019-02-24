/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("strazi.in", "r", stdin); FILE *fout = freopen("strazi.out", "w", stdout);

/*-------- Data --------*/
int N, M;
std::vector<std::vector<int > > graph;

std::vector<int > left, right, checked;

int match;
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &N, &M); graph.resize(N);

  for(int i = 0; i < M; i++) {
    int u, v; scanf("%d%d", &u, &v); u--; v--;
    graph[u].push_back(v);
  }
}

int PairUp(int node) {
  if(checked[node]) return 0;

  checked[node] = 1;

  for(auto& u : graph[node]) {
    if(right[u] == -1) {
      left[node] = u; right[u] = node; match++;
      return 1;
    }
  }

  for(auto& u : graph[node]) {
    if(PairUp(right[u])) {
      left[node] = u; right[u] = node;
      return 1;
    }
  }

  return 0;
}

void Match() {
  left = right =  std::vector<int >(N, -1);
  checked = std::vector<int >(N, 0);

  bool ok;
  do {
    for(int i = 0; i < N; i++) {
      checked[i] = 0;
    }

    ok = false;
    for(int i = 0; i < N; i++) {
      if(left[i] == -1) {
        ok |= PairUp(i);
      }
    }
  }while(ok);
}

void WriteOutput() {
  printf("%d\n", N - 1 - match);

  std::vector<std::vector<int > > paths;

  for(int i = 0; i < N; i++) {
    if(right[i] == -1) {
      std::vector<int > path;

      int x = i;
      while(left[x] != -1) {
        path.push_back(x); x = left[x];
      }
      path.push_back(x);

      paths.push_back(path);
    }
  }

  for(int i = 0; i < (int)paths.size() - 1; i++) {
    printf("%d %d\n", paths[i].back() + 1, paths[i + 1][0] + 1);
  }

  for(auto& path : paths) {
    for(auto& node : path) {
      printf("%d ", node + 1);
    }
  }
}

int main() {
  ReadInput();

  Match();

  WriteOutput();
	return 0;
}
