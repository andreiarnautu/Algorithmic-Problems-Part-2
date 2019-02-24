/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("trotuar.in", "r", stdin); FILE *fout = freopen("trotuar.out", "w", stdout);

const int kMaxN = 1e5 + 5;
const int kMaxL = 260;
const int kMaxK = 260;
const int inf = 1e8;
const int mod = 666013;

/*-------- Data --------*/
int n, l, k, m;
int a[kMaxK];

int aux[kMaxL], dp[kMaxN];

std::vector<int > bump[kMaxL];
std::vector<int >::iterator itr[kMaxL];

int start[kMaxL];

std::vector<int > zones;
int cnt[kMaxL];
/*-------- --------*/

int Mod(long long x) {return (x % mod);}

void ReadInput() {
  scanf("%d%d%d%d", &n, &l, &k, &m);
  for(int i = 1; i <= k; i++) {
    scanf("%d", &a[i]);
  }

  for(int i = 1; i <= m; i++) {
    int x, y; scanf("%d%d", &x, &y);
    bump[y].push_back(x);
  }
  for(int i = 1; i <= l; i++) {
    bump[i].push_back(n + 1);
  }

  for(int i = 1; i <= l; i++) {
    std::sort(bump[i].begin(), bump[i].end());
    itr[i] = bump[i].begin();
  }
}

void PrecomputeDp() {
  aux[0] = 1;
  for(int i = 1; i <= l; i++) {
    for(int j = 1; j <= k; j++) {
      if(a[j] > i) continue;
      aux[i] = Mod(aux[i] + aux[i - a[j]]);
    }
  }

  //  Check the case where there is a lxl piece which should not be counted twice
  for(int i = 1; i <= k; i++) {
    if(a[i] == l) {
      --aux[l]; aux[l] = Mod(aux[l] + mod);
    }
  }

  dp[0] = 1;
  for(int i = 1; i <= n; i++) {
    if(i >= l) {
      dp[i] = Mod(1LL * dp[i - l] * aux[l]);
    }

    for(int j = 1; j <= k; j++) {
      if(i < a[j]) continue;
      dp[i] = Mod(dp[i] + dp[i - a[j]]);
    }
  }
}

bool Alligned() {
  for(int i = 2; i <= l; i++) {
    if(start[i] != start[1]) {
      return false;
    }
  }
  return true;
}

int MinStart() {
  int ans = inf;
  for(int i = 1; i <= l; i++) {
    ans = std::min(ans, start[i]);
  }
  return ans;
}

bool Finished() {
  for(int i = 1; i <= l; i++) {
    if(start[i] != n + 1) {
      return false;
    }
  }
  return true;
}

void FindZones() {
  for(int i = 1; i <= l; i++) {
    start[i] = 1;
  }

  while(!Finished()) {
    if(Alligned()) {
      int nxt = inf;
      for(int i = 1; i <= l; i++) {
        nxt = std::min(nxt, *itr[i]);
      }

      if(nxt > start[1]) {
        zones.push_back(nxt - start[1]);
      }

      for(int i = 1; i <= l; i++) {
        start[i] = nxt;
        while(*itr[i] == start[i] && start[i] <= n) {
          ++itr[i]; ++start[i];
        }
      }
    } else {
      int minStart = MinStart();

      for(int l1 = 1, l2 = 1; l1 <= l; l1 = ++l2) {
        while(l2 < l && start[l1] == start[l2 + 1]) {
          l2++;
        }
        if(start[l1] - minStart < l && start[l1] < n + 1) {
          ++cnt[l2 - l1 + 1];
        }
      }

      for(int i = 1; i <= l; i++) {
        if(start[i] - minStart < l) {
          start[i] += l;

          while(*itr[i] == start[i] && start[i] <= n) {
            ++itr[i]; ++start[i];
          }
        }
      }
    }
  }
}

int main() {
  ReadInput();

  PrecomputeDp();

  FindZones();

  long long sol = 1;
  for(int i = 1; i < l; i++) {
    for(int j = 1; j <= cnt[i]; j++) {
      sol = Mod(sol * aux[i]);
    }
  }
  for(auto& x : zones) {
    sol = Mod(sol * dp[x]);
  }

  printf("%lld\n", sol);
	return 0;
}
