/**
  *  Worg
  *  Mar 11, 2018
  *  10:10:19 AM
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("zoro.in", "r", stdin); FILE *fout = freopen("zoro.out", "w", stdout);

const int maxN = 1000 + 5;

/*-------- Data --------*/
int n, m;
std::pair<int, int > where[maxN * maxN];
int ldp[maxN], cdp[maxN];

int start, finish;
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      int x; scanf("%d", &x);

      where[x] = {i, j};

      if(i == 1 && j == 1) start = x;
      if(i == n && j == m) finish = x;
    }
  }
}

int Solve() {
  ldp[1] = 1; cdp[1] = 1;

  for(int i = start - 1; i >= finish; i--) {
    int x = where[i].first, y = where[i].second;

    int best = std::max(ldp[x], cdp[y]);

    if(best == 0) continue;

    best++;
    ldp[x] = std::max(ldp[x], best); cdp[y] = std::max(cdp[y], best);

    if(i == finish) return best;
  }

  return 0;
}
/*
void Generate() {
  printf("1000 1000\n");
  int v[1005];
  int cursor = 1000 * 1000;

  for(int i = 1; i <= 1000; i++) {


    if(i % 2 == 1) {
      for(int j = 1; j <= 1000; j++) {
        v[j] = cursor; cursor--;
      }
    } else {
      for(int j = 1000; j > 0; j--) {
        v[j] = cursor; cursor--;
      }
    }

    for(int j = 1; j <= 1000; j++) {
      printf("%d ", v[j]);
    }
    printf("\n");
  }
}
*/
int main() {
  //Generate();

  ReadInput();

  printf("%d\n", Solve());

  return 0;
}
