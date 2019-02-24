/**
  *  Worg
  *  Mar 13, 2018
  *  11:20:51 AM
  */
#include <map>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

FILE *fin = freopen("s2c.in", "r", stdin); FILE *fout = freopen("s2c.out", "w", stdout);

const int maxN = 2000 + 5;

/*-------- --------*/
int n;
int a[maxN], bst[maxN];
int dp[maxN][maxN];

int cursor;

std::map<int, int > map;
/*-------- --------*/

void ReadInput() {
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    map[a[i]] = 1;
  }

  //  Normalize data
  cursor = 0;
  for(auto& itr : map) {
    itr.second = ++cursor;
  }
  for(int i = 1; i <= n; i++) {
    a[i] = map[a[i]];
  }
}

void Solve() {
  memset(dp, 0, sizeof(dp));

  int sol = 0;

  for(int i = 1; i <= n; i++) {
    memset(bst, 0, sizeof(bst));

    for(int j = 1; j < i; j++) {
      bst[a[j]] = std::max(bst[a[j]], dp[j][i]);
    }

    for(int j = 1; j <= cursor; j++) {
      bst[j] = std::max(bst[j], bst[j - 1]);
    }

    for(int j = i + 1; j <= n; j++) {
      dp[i][j] = bst[a[j] - 1] + 1;

      sol = std::max(sol, dp[i][j]);
    }
  }

  printf("%d\n", sol + 1);
}

int main() {
  int t; scanf("%d", &t);

  for(int i = 0; i < t; i++) {
    ReadInput();
    Solve();
    map.clear();
  }
  return 0;
}
