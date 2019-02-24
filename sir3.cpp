/**
  *  Worg
  */
#include <map>
#include <cstdio>
#include <vector>
#include <algorithm>

#define leftSon (node * 2)
#define rightSon (node * 2 + 1)
#define mid ((left + right) / 2)

FILE *fin = freopen("sir3.in", "r", stdin); FILE *fout = freopen("sir3.out", "w", stdout);

const int maxN = 2e5 + 5;

/*-------- Data --------*/
int n, s;
int v[maxN];
std::map<int, int > pos;

std::pair<int, int > aint[maxN * 4];

int sol, idxLeft, idxRight;
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &s);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &v[i]); pos[v[i]] = i;
  }
}

void Build(int node, int left, int right) {
  if(left == right) {
    aint[node].first = aint[node].second = pos[s - v[left]];
    return;
  }

  Build(leftSon, left, mid); Build(rightSon, mid + 1, right);

  aint[node].first = std::min(aint[leftSon].first, aint[rightSon].first);
  aint[node].second = std::max(aint[leftSon].second, aint[rightSon].second);
}

void Query(int node, int left, int right, int first, int last, int &minIdx, int &maxIdx) {
  if(first <= left && right <= last) {
    minIdx = std::min(minIdx, aint[node].first); maxIdx = std::max(maxIdx, aint[node].second);
    return;
  }

  if(first <= mid) {
    Query(leftSon, left, mid, first, last, minIdx, maxIdx);
  }
  if(mid < last) {
    Query(rightSon, mid + 1, right, first, last, minIdx, maxIdx);
  }
}

void Solve() {
  Build(1, 1, n);

  for(int i = 1; i <= n; i++) {
    if(pos[s - v[i]] > i) {
      int j = pos[s - v[i]];

      int minIdx = n + 1, maxIdx = 0;
      Query(1, 1, n, i, j, minIdx, maxIdx);

      if(i <= minIdx && maxIdx <= j && j - i + 1 > sol) {
        sol = j - i + 1; idxLeft = i; idxRight = j;
      }
    }
  }
}

int main() {
  ReadInput();

  Solve();

  printf("%d %d %d\n", sol, idxLeft, idxRight);
  return 0;
}
