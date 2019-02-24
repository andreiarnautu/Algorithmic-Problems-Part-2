/**
  *  Worg
  */
#include <ctime>
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

const int maxN = 1000 + 5;
const int steps = 100;
const int inf = 1e6;
const double eps = 1e-8;

/*-------- Data --------*/
struct Edge {
  int u, v;
  double cost, dist;

  Edge(const int _u, const int _v, const int _cost, const int _dist) {
    u = _u; v = _v; cost = (double)_cost; dist = (double)_dist;
  }
};

double minRatio, maxRatio;
int n, m;
std::vector<Edge > edg;

int father[maxN];
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &m);
  minRatio = inf; maxRatio = 0;

  for(int i = 0; i < m; i++) {
    int u, v, dist, cost; scanf("%d%d%d%d", &u, &v, &dist, &cost);
    edg.emplace_back(u, v, cost, dist);

    minRatio = std::min(minRatio, edg.back().cost / edg.back().dist);
    maxRatio = std::max(maxRatio, edg.back().cost / edg.back().dist);
  }


}

int Equal(double a, double b) {
  return -eps < a - b && a - b < eps;
}

int Group(int node) {
  if(node != father[node]) {
    father[node] = Group(father[node]);
  }
  return father[node];
}

void Unite(int u, int v) {
  father[Group(u)] = Group(v);
}

double Get(double x) {
  for(int i = 1; i <= n; i++) {
    father[i] = i;
  }

  std::sort(edg.begin(), edg.end(), [&](Edge a, Edge b) {
    return (a.cost - x * a.dist) < (b.cost - x * b.dist);
  });

  double mstCost = 0.0;
  for(int i = 0, cnt = 0; i < m && cnt < n - 1; i++) {
    auto e = edg[i];

    if(Group(e.u) != Group(e.v)) {
      Unite(e.u, e.v);

      mstCost += e.cost - x * e.dist;

      cnt++;
    }
  }

  return mstCost;
}

int main() {
  clock_t startTime = clock();

  ReadInput();

  double left = minRatio, right = maxRatio, sol = 0.0;

  //printf("%.12f\n", Get(500000.0));

  for(int i = 0; i < steps; i++) {
    //printf("%.10f; %.10f\n", left, right);
    double mid = (left + right) * 0.5;

    double result = Get(mid);

    if(result >= 0.0) {
      sol = mid; left = mid;
    } else {
      right = mid;
    }

    clock_t nowTime = clock();

    if((double)(nowTime - startTime) / CLOCKS_PER_SEC > 3.950) {
      break;
    }
  }

  printf("%.12f\n", sol);

  return 0;
}
