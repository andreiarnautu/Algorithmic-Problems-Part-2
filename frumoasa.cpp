/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

FILE *fin = freopen("frumoasa.in", "r", stdin); FILE *fout = freopen("frumoasa.out", "w", stdout);

const int sigma = 26;
const int mod = 1e9 + 7;

int Power(const int base, const long long exp) {
  int answer = 1, aux = base;

  for(long long i = 1; i <= exp; i <<= 1) {
    if(i & exp) {
      answer = 1LL * answer * aux % mod;
    }
    aux = 1LL * aux * aux % mod;
  }

  return answer;
}

int main() {
  long long n, p; scanf("%lld%lld", &n, &p);

  int answer = 1;

  if(p >= sigma && n > sigma) {
    answer = 0;
  } else {
    int i;
    for(i = 1; i <= std::min(n, p); i++) {
      answer = 1LL * answer * (sigma - i + 1) % mod;
    }

    answer = 1LL * answer * Power(sigma - p, n - i + 1) % mod;
  }

  printf("%d\n", answer);
  return 0;
}