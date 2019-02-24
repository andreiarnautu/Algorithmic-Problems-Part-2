/**
  *  Worg
  *  Mar 14, 2018
  *  8:35:48 AM
  */
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("winter_is_here.in", "r", stdin); FILE *fout = freopen("winter_is_here.out", "w", stdout);

const int maxVal = 1e6 + 5;
const int mod = 1e9 + 7;

int cnt[maxVal], dp[maxVal], pow2[maxVal];

void ReadInput() {
  int n; scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    int x; scanf("%d", &x); cnt[x]++;
  }
}

int Mod(int x) {
  if(x < 0) return x + mod;
  if(x >= mod) return x - mod;
  return x;
}

int Solve() {
  pow2[0] = 1;
  for(int i = 1; i < maxVal; i++) {
    pow2[i] = Mod(pow2[i - 1] * 2);
  }

  for(int i = 1; i < maxVal; i++) {
    for(int j = i * 2; j < maxVal; j += i) {
      cnt[i] += cnt[j];
    }
  }

  int sol = 0;
  for(int i = maxVal - 1; i > 1; i--) {
    if(!cnt[i]) continue;

    dp[i] = 1LL * cnt[i] * pow2[cnt[i] - 1] % mod;

    for(int j = 2 * i; j < maxVal; j += i) {
      dp[i] = Mod(dp[i] - dp[j]);
    }

    sol = Mod(sol + 1LL * i * dp[i] % mod);
  }

  return sol;
}

int main() {
  ReadInput();

  printf("%d\n", Solve());

  return 0;
}
