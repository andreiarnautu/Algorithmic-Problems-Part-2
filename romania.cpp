/**
  *  Worg
  *  Mar 9, 2018
  *  2:06:36 PM
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("romania.in", "r", stdin); FILE *fout = freopen("romania.out", "w", stdout);

const int maxN = 1e5 + 5;

/*-------- Data --------*/
int n, k;
int cnt[maxN], left[maxN], right[maxN];

std::queue<int > q;
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &k);
  for(int i = 0; i < k; i++) {
    int x; scanf("%d", &x);
    cnt[x]++;
  }
}

void Solve() {
  for(int i = 1; i <= n; i++) {
    left[i] = i - 1; right[i] = i + 1;
  }
  left[1] = n; right[n] = 1;

  for(int i = 1; i <= n; i++) {
    if(!cnt[i] && cnt[right[i]]) {
      q.push(i);
    }
  }

  while(!q.empty()) {
    int node = q.front(); q.pop();

    printf("%d %d\n", right[node], left[node]);

    cnt[right[node]]--;

    int l = left[node], r = right[node];
    left[r] = l; right[l] = r;

    if(!cnt[l] && cnt[r]) {
      q.push(l);
    }
    if(!cnt[r] && cnt[right[r]]) {
      q.push(r);
    }
  }
}

int main() {
  ReadInput();

  Solve();
  return 0;
}
