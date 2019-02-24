/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

FILE *fin = freopen("nrtri.in", "r", stdin); FILE *fout = freopen("nrtri.out", "w", stdout);

const int MAX_N = 800 + 5;

int n;
int v[MAX_N];
int max_bit;

int BinarySearch(int value) {
  int k = 0;
  for(int step = max_bit; step > 0; step >>= 1) {
    if(k + step <= n && v[k + step] <= value) {
      k += step;
    }
  }

  return k;
}

int GetTriangleNumber() {
  int answer = 0;

  for(max_bit = 1; max_bit <= n; max_bit <<= 1);

  for(int i = 1; i <= n; i++) {
    for(int j = i + 1; j <= n; j++) {
      int idx = BinarySearch(v[i] + v[j]);
      answer += idx - j;
    }
  }

  return answer;
}

int main() {
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &v[i]);
  }
  std::sort(v + 1, v + n + 1);

  printf("%d\n", GetTriangleNumber());
  return 0;
}