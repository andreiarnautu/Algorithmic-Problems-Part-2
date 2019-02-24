/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

int n;
int a[2005];

int Gcd(int a, int b) {
  int r;
  while(b != 0) {
    r = a % b; a = b; b = r;
  }
  return a;
}

int main() {
  scanf("%d", &n);

  int gcd = 0, ones = 0;
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    gcd = Gcd(gcd, a[i]);

    ones += (a[i] == 1 ? 1 : 0);
  }

  if(gcd != 1) {
    printf("-1\n"); return 0;
  }

  if(ones) {
    printf("%d\n", n - ones); return 0;
  }

  int best = n;
  for(int i = 1; i < n; i++) {
    int gcd = a[i];
    for(int j = i + 1; j <= n; j++) {
      gcd = Gcd(gcd, a[j]);
      if(gcd == 1) {
        best = std::min(best, j - i); break;
      }
    }
  }

  printf("%d\n", n - 1 + best);
  return 0;
}
