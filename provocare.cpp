/**
  *  Worg
  *  Mar 13, 2018
  *  12:49:47 PM
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("provocare.in", "r", stdin); FILE *fout = freopen("provocare.out", "w", stdout);

const long long inf = 1e16;
const int limit = 102;
/*-------- Data --------*/
long long comb[limit][limit];
/*-------- --------*/

void Precompute() {
  for(int i = 0; i < limit; i++) {
    comb[i][0] = 1;
    for(int j = 1; j <= i; j++) {
      comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
      if(comb[i][j] > inf) comb[i][j] = inf;
    }
  }
}

long long Comb(long long n, long long k) {
  if(k > n || n < 0 || k < 0) return 0;

  if(n < limit && k < limit) {
    return comb[n][k];
  }

  if(k > 6 && n - k > 6) return inf;

  k = std::min(k, n - k);
  long long ans = 1;
  for(long long i = n - k + 1; i <= n; i++) {
    ans *= i;
  }
  for(long long i = 1; i <= k; i++) {
    ans /= i;
  }

  return ans;
}

bool Check(long long value, long long n, long long a, long long b) {
  long long total = 0;

  for(long long i = 0; i * b <= value; i++) {
    long long x = (value - i * b) / a;

    long long here = Comb(x + i + 1, i + 1);

    if(here == inf || total + here >= n) {
      return true;
    }
    total += here;
  }

  return total >= n;
}

void SolveTest() {
  long long n, a, b; scanf("%lld%lld%lld", &n, &a, &b);

  if(a > b) std::swap(a, b);

  long long left = 0, right = n * a, sol = 0;

  while(left <= right) {
    long long mid = (left + right) / 2;

    if(Check(mid, n, a, b)) {
      sol = mid; right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  printf("%lld\n", sol);
}

int main() {
  Precompute();

  int t; scanf("%d", &t);
  for(int i = 0; i < t; i++) {
    SolveTest();
  }

  return 0;
}
