/**
  *  Worg
  */
#include <cstdio>

FILE *fin = freopen("lgput.in", "r", stdin); FILE *fout = freopen("lgput.out", "w", stdout);

const int MOD = 1999999973;

int Power(long long base, long long exp) {
  int ans = 1, aux = base;

  for(long long i = 1; i <= exp; i <<= 1) {
    if(i & exp) {
      ans = 1LL * ans * aux % MOD;
    }
    aux = 1LL * aux * aux % MOD;
  }

  return ans;
}

int main() {
  int base, exp; scanf("%d%d", &base, &exp);

  printf("%d\n", Power(base, exp));

  return 0;
}
