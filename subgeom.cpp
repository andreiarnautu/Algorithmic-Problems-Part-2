/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("subgeom.in", "r", stdin); FILE *fout = freopen("subgeom.out", "w", stdout);

const int kMaxValue = 1e5 + 5;

int n;
std::vector<int > v;

int valMax;
int seen[kMaxValue], best[kMaxValue];

int SolveOverSqrt() {
  for(auto& x : v) {
    for(int i = 1; i * i <= x; i++) {
      if(x % i == 0) {
        if(seen[i] && i != x) return 2;
        if(seen[x / i] && x != x / i) return 2;
      }
    }

    seen[x] = 1;
  }

  for(auto& x : v) {
    seen[x] = 0;
  }

  return 1;
}

int SolveUnderSqrt() {
  int ans = 1;

  for(int ratio = 2; ratio * ratio <= valMax; ratio++) {
    for(auto& x : v) {
      if(x % ratio != 0) {
        best[x] = 1;
      } else {
        best[x] = best[x / ratio] + 1;
      }

      ans = std::max(ans, best[x]);
    }

    for(auto& x : v) {
      best[x] = 0;
    }

    if(ans >= 3 && ratio >= 47) break;
    if(ans >= 4 && ratio >= 18) break;
  }

  return ans;
}

int main() {
  int testCount; scanf("%d", &testCount);

  for(int i = 0; i < testCount; i++) {
    //  read
    scanf("%d", &n); v.resize(n); valMax = 0;
    for(auto& itr : v) {
      scanf("%d", &itr); valMax = std::max(valMax, itr);
    }

    //  solve
    int sol = SolveUnderSqrt();
    if(sol == 1) {
      sol = SolveOverSqrt();
    }
    printf("%d\n", sol);

    for(auto& itr : v) {
      seen[itr] = best[itr] = 0;
    }
  }
	return 0;
}
