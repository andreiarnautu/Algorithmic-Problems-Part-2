/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("rick.in", "r", stdin); FILE *fout = freopen("rick.out", "w", stdout);

const int maxVal = 500500;
const int mod = 1e9 + 7;

/*-------- Data --------*/
int n;
int cnt[maxVal];
int pow2[maxVal];
int dp[maxVal];
/*-------- --------*/

void ReadInput() {
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    int x; scanf("%d", &x);
    cnt[x]++;
  }
}

int Mod(int x) {
  if(x >= mod) {
    return x - mod;
  } else if(x < 0) {
    return x + mod;
  }
  return x;
}

int Solve() {
  //  Precompute pow
  pow2[0] = 1;
  for(int i = 1; i < maxVal; i++) {
    pow2[i] = Mod(pow2[i - 1] * 2);
  }

  for(int i = 1; i < maxVal; i++) {
    for(int j = 2 * i; j < maxVal; j += i) {
      cnt[i] += cnt[j];
    }
  }

  int sol = 1;
  for(int i = maxVal - 1; i >= 1; i--) {
    dp[i] = Mod(pow2[cnt[i]] - 1);

    for(int j = i * 2; j < maxVal; j += i) {
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
