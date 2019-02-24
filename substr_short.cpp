/**
  *  Worg
  *  Mar 13, 2018
  *  10:46:54 PM
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("substr.in", "r", stdin); FILE *fout = freopen("substr.out", "w", stdout);

const int maxN = 17000;
const int maxLog = 16;

/*-------- Data --------*/
int n, k;
char s[maxN];

int val[maxLog][maxN];
int which[maxN];
/*-------- --------*/

void ComputeSA() {
  for(int i = 1; i <= n; i++) {
    val[0][i] = s[i];
  }

  for(int i = 1, lg = 1; i < maxLog; i++, lg *= 2) {
    std::vector<std::pair<std::pair<int, int >, int > > vec;

    for(int j = 1; j <= n; j++) {
      int a = val[i - 1][j];
      int b = (j + lg <= n) ? val[i - 1][j + lg] : -1;

      vec.push_back({{a, b}, j});
    }

    std::sort(vec.begin(), vec.end());

    val[i][vec[0].second] = 0;
    for(int j = 1; j < (int)vec.size(); j++) {
      if(vec[j - 1].first == vec[j].first) {
        val[i][vec[j].second] = val[i][vec[j - 1].second];
      } else {
        val[i][vec[j].second] = val[i][vec[j - 1].second] + 1;
      }
    }
  }

  for(int j = 1; j <= n; j++) {
    which[val[maxLog - 1][j]] = j;
  }
}

int LCP(int x, int y) {
  int ans = 0;
  int maxVal = std::min(n - x + 1, n - y + 1);
  for(int step = maxLog - 1, lg = (1 << (maxLog - 1)); step >= 0 && x <= n && y <= n; step--, lg /= 2) {
    if(val[step][x] == val[step][y]) {
      x += lg; y += lg; ans += lg;
    }
  }

  return std::min(ans, maxVal);
}

int Solve() {
  int ans = (k == 1) ? n : 0;
  for(int i = 0; i + k - 1 < n; i++) {
    ans = std::max(ans, LCP(which[i], which[i + k - 1]));
  }
  return ans;
}

int main() {
  scanf("%d%d", &n, &k);
  scanf("%s", s + 1);

  ComputeSA();

  printf("%d\n", Solve());

  return 0;
}
