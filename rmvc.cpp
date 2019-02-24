/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("rmvc.in", "r", stdin); FILE *fout = freopen("rmvc.out", "w", stdout);

/*-------- Data --------*/
int N, M;

std::vector<int > seen, act, sol;
std::vector<std::pair<int, int > > edges;
/*-------- --------*/

void Back(int idx) {
  if((int)act.size() > 18) return;

  if(idx == M) {
    if(act.size() < sol.size()) {
      sol = act;
    }
  } else {
    seen[edges[idx].first] = true;
    act.push_back(edges[idx].first);
    for(int i = idx + 1; i < M; i++) {
      if(!seen[edges[i].first] && !seen[edges[i].second]) {
        Back(i); break;
      }
      if(i == M - 1) {
        Back(M);
      }
    }

    seen[edges[idx].first] = false; act.pop_back();

    seen[edges[idx].second] = true; act.push_back(edges[idx].second);
    for(int i = idx + 1; i < M; i++) {
      if(!seen[edges[i].first] && !seen[edges[i].second]) {
        Back(i); break;
      }
      if(i == M - 1) {
        Back(M);
      }
    }

    seen[edges[idx].second] = false; act.pop_back();
  }
}

int main() {
  scanf("%d%d", &N, &M);
  for(int i = 0; i < M; i++) {
    int u, v; scanf("%d%d", &u, &v);
    edges.emplace_back(u, v);
  }

  seen = std::vector<int >(N + 1, false);
  for(int i = 1; i <= N; i++) {
    sol.push_back(i);
  }

  Back(0);

  printf("%d\n", (int)sol.size());
  for(auto& itr : sol) {
    printf("%d ", itr);
  }
	return 0;
}
