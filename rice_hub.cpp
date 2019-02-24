/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

const int maxR = 1e5 + 5;

/*-------- Data --------*/
long long r, l, b;
long long x[maxR], sum[maxR];
/*-------- --------*/

void ReadInput() {
  scanf("%lld%lld%lld", &r, &l, &b);
  for(int i = 1; i <= r; i++) {
    scanf("%lld", &x[i]);
    sum[i] = sum[i - 1] + x[i];
  }
}

long long Partial(int left, int right) {
  if(left > right) return 0;
  return sum[right] - sum[left - 1];
}

bool Affordable(int left, int right) {
  int m = (left + right) / 2;
  long long cost = 0;

  cost = 1LL * (m - left + 1) * x[m] - Partial(left, m) + Partial(m + 1, right) - 1LL * (right - m) * x[m];

  return cost <= b;
}

bool Check(int k) {
  for(int i = k; i <= r; i++) {
    if(Affordable(i - k + 1, i)) {
      return true;
    }
  }
  return false;
}

long long BinarySearch() {
  int left = 1, right = r, ans = 1;

  while(left <= right) {
    int mid = (left + right) / 2;

    if(Check(mid)) {
      ans = mid; left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return ans;
}

int main() {
  ReadInput();

  printf("%lld\n", BinarySearch());

  return 0;
}
