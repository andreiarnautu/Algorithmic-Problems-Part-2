#include <cstdio>
#include <stack>
#include <algorithm>

FILE *fin = freopen("secv6.in", "r", stdin); FILE *fout = freopen("secv6.out", "w", stdout);

const int DIM = 8200;

using namespace std;

int n;
int x[DIM];
stack<int > stk;

int main() {
  scanf("%d", &n);

  int m = min(8192, n);
  for(int i = 0; i < m; i++) {
    scanf("%d", &x[i]);
  }

  long long sol = 0;
  for(int i = 0; i < n; i++) {
    int a = i + x[i / 8192] + x[i % 8192];

    //  Vrem sa scoatem elementele din stiva mai mici decat a
    while(!stk.empty() && a >= stk.top()) {
      stk.pop();
      sol++;
    }

    if(!stk.empty()) {
      sol++;
    }
    stk.push(a);
  }

  printf("%lld", sol);

  return 0;
}