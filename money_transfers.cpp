/**
  *  Worg
  */
#include <map>
#include <cstdio>
#include <algorithm>

std::map<long long, int > count;

int main() {
  int n; scanf("%d", &n);

  long long sum = 0;
  int answer = n - 1;

  for (int i = 1; i <= n; i++) {
    int x; scanf("%d", &x);

    sum += x;
    count[sum]++;

    answer = std::min(answer, n - count[sum]);
  }

  printf("%d\n", answer);
  return 0;
}
