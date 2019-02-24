/**
  *  Worg
  *  Mar 18, 2018
  *  10:35:48 PM
  */
#include <set>
#include <deque>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>

FILE *fin = freopen("ramen.in", "r", stdin); FILE *fout = freopen("ramen.out", "w", stdout);

const int maxN = 1e5 + 5;

/*-------- Data --------*/
int n, d;
int t[maxN], p[maxN];
std::unordered_map<int, int > norm;
/*-------- Solving data --------*/
std::multiset<std::pair<int, int > > mset;
std::multiset<int > mset2;

std::deque<int > sol[maxN];
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &d);
  for(int i = 0, idx = 0; i < n; i++) {
    scanf("%d%d", &t[i], &p[i]);

    if(norm.find(p[i]) == norm.end()) {
      norm[p[i]] = ++idx;
    }
  }
}

void Solve() {
  for(int i = 0; i < n; i++) {
    mset.insert({t[i] - p[i], p[i]});
  }

  for(int i = 0; i < n; i++) {
    while(!mset.empty() && mset.begin()->first <= t[i] + d) {
      mset2.insert(mset.begin()->second); mset.erase(mset.begin());
    }

    sol[norm[*mset2.begin()]].push_back(t[i] + d + *mset2.begin());

    mset2.erase(mset2.begin());
  }
}

void WriteOutput() {
  for(int i = 0; i < n; i++) {
    printf("%d\n", sol[norm[p[i]]].front()); sol[norm[p[i]]].pop_front();
  }
}

int main() {
  ReadInput();

  Solve();

  WriteOutput();
  return 0;
}
