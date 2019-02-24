/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("secvmax.in", "r", stdin); FILE *fout = freopen("secvmax.out", "w", stdout);

static const int MAX_N = 1e5 + 5;
static const int MAX_M = 1e5 + 5;

/*-------- Data --------*/
int n, m;
std::vector<std::pair<int, int > > sequence_numbers, queries;

int max_size;
int father[MAX_N], size[MAX_N], query_answer[MAX_M];
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; i++) {
    int x; scanf("%d", &x);
    sequence_numbers.emplace_back(x, i);
  }
  for(int i = 1; i <= m; i++) {
    int x; scanf("%d", &x);
    queries.emplace_back(x, i);
  }
}

int Group(int node) {
  if(node != father[node]) {
    father[node] = Group(father[node]);
  }
  return father[node];
}

void Unite(int u, int v) {
  int root_u = Group(u), root_v = Group(v);

  if(size[root_u] < size[root_v]) {
    size[root_v] += size[root_u];
    father[root_u] = root_v;
  } else {
    size[root_u] += size[root_v];
    father[root_v] = root_u;
  }

  max_size = std::max(max_size, std::max(size[root_u], size[root_v]));
}

void Solve() {
  std::sort(sequence_numbers.begin(), sequence_numbers.end());
  std::sort(queries.begin(), queries.end());

  int i = 0, j = 0;

  while(i < (int)sequence_numbers.size() && j < (int)queries.size()) {
    if(sequence_numbers[i].first <= queries[j].first) {
      int idx = sequence_numbers[i].second;
      //  Initialize its set
      father[idx] = idx; size[idx] = 1;
      max_size = std::max(max_size, 1);

      //  Check for connections with the adjacent elements
      if(father[idx - 1] != 0) {
        Unite(idx, idx - 1);
      }
      if(father[idx + 1] != 0) {
        Unite(idx, idx + 1);
      }
      i++;
    } else {
      query_answer[queries[j].second] = max_size;
      j++;
    }
  }

  while(j < (int)queries.size()) {
    query_answer[queries[j].second] = max_size;
    j++;
  }
}

void PrintAnswer() {
  for(int i = 1; i <= m; i++) {
    printf("%d\n", query_answer[i]);
  }
}

int main() {
  ReadInput();
  Solve();
  PrintAnswer();
  return 0;
}