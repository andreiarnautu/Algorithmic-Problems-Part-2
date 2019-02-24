/**
  *  Worg
  */
#include <map>
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

const int mod = 1e9 + 7;

/*-------- Data --------*/
int n, m;
long long seed, vmax;

std::map<int, long long> map;
/*-------- --------*/

int Rand() {
  int ret = seed;
  seed = 1LL * (1LL * seed * 7 + 13) % mod;
  return ret;
}

void First(int l, int r, int x) {
  auto beg = map.upper_bound(l); beg--;
  if(beg->first != l) {
    map[l] = beg->second; ++beg;
  }
  auto end = map.upper_bound(r + 1); end--;
  if(end->first != r + 1) {
    map[r + 1] = end->second; ++end;
  }

  while(beg != end) {
    (beg++)->second += x;
  }
}

void Second(int l, int r, int x) {
  auto beg = map.upper_bound(l); beg--;
  if(beg->first != l) {
    map[l] = beg->second; ++beg;
  }
  auto end = map.upper_bound(r + 1); end--;
  if(end->first != r + 1) {
    map[r + 1] = end->second; ++end;
  }

  while(beg != end) {
    map.erase(beg++);
  }
  map[l] = x;
}

void Third(int l, int r, int x) {
  auto beg = map.upper_bound(l); beg--;
  if(beg->first != l) {
    map[l] = beg->second; ++beg;
  }
  auto end = map.upper_bound(r + 1); end--;
  if(end->first != r + 1) {
    map[r + 1] = end->second; ++end;
  }

  std::vector<std::pair<long long, int > > vec;
  while(beg != end) {
    auto nxt = beg; nxt++;
    vec.emplace_back(beg->second, nxt->first - beg->first);
    beg = nxt;
  }

  std::sort(vec.begin(), vec.end());
  for(auto& itr : vec) {
    if(x <= itr.second) {
      printf("%lld\n", itr.first); return;
    }
    x -= itr.second;
  }
}

long long Power(long long base, long long exp, long long y) {
  long long ans = 1, aux = base % y;
  for(long long i = 1; i <= exp; i <<= 1) {
    if(i & exp) {
      ans = (ans * aux) % y;
    }
    aux = (aux * aux) % y;
  }
  return ans;
}

void Fourth(int l, int r, int x, int y) {
  auto beg = map.upper_bound(l); beg--;
  if(beg->first != l) {
    map[l] = beg->second; ++beg;
  }
  auto end = map.upper_bound(r + 1); end--;
  if(end->first != r + 1) {
    map[r + 1] = end->second; ++end;
  }

  long long sol = 0;

  while(beg != end) {
    auto nxt = beg; nxt++;
    long long p = Power(beg->second % y, x, y);
    sol = (sol + (p * (nxt->first - beg->first) % y)) % y;
    beg = nxt;
  }

  printf("%lld\n", sol);
}

int main() {
  scanf("%d%d%lld%lld", &n, &m, &seed, &vmax);

  for(int i = 1; i <= n; i++) {
    int x = (Rand() % vmax) + 1;
    map[i] = x;
  }

  for(int i = 1; i <= m; i++) {
    int op = (Rand() % 4) + 1;
    int l = (Rand() % n) + 1;
    int r = (Rand() % n) + 1;

    if(l > r) std::swap(l, r);

    int x, y;

    if(op == 3) {
      x = (Rand() % (r - l + 1)) + 1;
    } else {
      x = (Rand() % vmax) + 1;
    }

    if(op == 1) {
      First(l, r, x);
    } else if(op == 2) {
      Second(l, r, x);
    } else if(op == 3) {
      Third(l, r, x);
    } else {
      y = (Rand() % vmax) + 1;
      Fourth(l, r, x, y);
    }
  }
	return 0;
}
