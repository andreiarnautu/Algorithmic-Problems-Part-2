/**
  *  Worg
  *  Mar 11, 2018
  *  8:17:58 PM
  */
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

FILE *fin = freopen("smooth2.in", "r", stdin); FILE *fout = freopen("smooth2.out", "w", stdout);

const int maxN = 1e5 + 5;
const int sigma = 26;

/*-------- Data --------*/
int n;
int a[maxN];
char s[maxN];
int help[sigma];
/*-------- --------*/

int Try(const int size) {
  for(int i = 0; i < sigma; i++) {
    help[i] = 0;
  }

  for(int i = 1; i <= n; i += size) {
    std::vector<int > seen(sigma, false);

    for(int j = i; j <= n && j < i + size; j++) {
      if(seen[a[j]]) continue;

      seen[a[j]] = true; help[a[j]]++;
    }
  }

  std::sort(help, help + sigma);

  int ans = n;
  for(int i = 1; i <= size; i++) {
    ans -= help[sigma - i];
  }

  return ans;
}

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);

  for(int i = 1 ; i <= n; i++) {
    a[i] = s[i] - 'a';
  }

  int sol = n;
  for(int i = 1; i <= 26; i++) {
    sol = std::min(sol, Try(i));
  }
  printf("%d\n", sol);
}
