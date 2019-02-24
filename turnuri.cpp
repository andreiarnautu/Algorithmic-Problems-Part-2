/**
  *  Worg
  *  Mar 21, 2018
  *  1:10:10 PM
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("turnuri.in", "r", stdin); FILE *fout = freopen("turnuri.out", "w", stdout);

const int maxN = 1e6 + 5;
const int inf = 2e9 + 5;
/*-------- Data --------*/
int n;
int h[maxN];

int lft[maxN], rgh[maxN], cntRgh[maxN];
/*-------- --------*/

void ReadInput() {
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &h[i]);
  }

  h[0] = h[n + 1] = inf;
}

void Compute(int v[], int start, int add) {
  for(int i = start; 1 <= i && i <= n; i += add) {
    int j = i - add;

    while(h[i] > h[j]) {
      j = v[j];
    }
    v[i] = j;
  }
}

void ComputeRight() {
  for(int i = n; i >= 1; i--) {
    cntRgh[i] = cntRgh[rgh[i]] + 1;
  }
}

long long Count(int from, int to) {
  return from - to - (to == 0);
}

long long Solve() {
  long long sol = 0;
  long long total = 0;

  for(int i = 1; i <= n; i++) {
    total += Count(i, lft[i]);
  }

  for(int i = 1; i <= n; i++) {
    long long sum = total - Count(i, lft[i]) - cntRgh[rgh[i]];

    for(int p1 = i - 1, p2 = i + 1; p2 < rgh[i]; p2 = rgh[p2]) {
      while(h[p1] < h[p2]) {
        p1 = lft[p1];
      }

      sum += Count(p2, p1) - Count(p2, i) - 1;
    }

    sol += sum;
  }

  return sol;
}

int main() {
  ReadInput();

  Compute(lft, 1, +1); Compute(rgh, n, -1);

  ComputeRight();

  printf("%lld\n", Solve());

  return 0;
}
