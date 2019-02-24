/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

#define x first
#define y second

typedef std::pair<double, double > Point;

FILE *fin = freopen("popandai.in", "r", stdin); FILE *fout = freopen("popandai.out", "w", stdout);

const double kMaxInf = 1e17;
const double eps = 1e-8;

/*-------- Data --------*/
int n, k;
std::vector<Point > pts;

std::vector<std::vector<int > > under;

double sol = kMaxInf;
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &k);
  for(int i = 0; i < n; i++) {
    double a, b; scanf("%lf%lf", &a, &b); pts.emplace_back(a, b);
  }
}

double CrossProduct(Point A, Point B, Point C) {
  return (B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y);
}

void ComputeDp() {
  //  under[i][j] = how many points are under the [i, j] segment
  under = std::vector<std::vector<int > >(n, std::vector<int >(n, 0));

  std::sort(pts.begin(), pts.end());

  for(int i = 0; i < n; i++) {
    for(int j = i + 1; j < n; j++) {
      for(int act = 0; act < n; act++) {
        if(CrossProduct(pts[i], pts[j], pts[act]) < -eps && pts[i].x <= pts[act].x && pts[act].x <= pts[j].x) {
          under[i][j]++;
        }
      }
    }
  }
}

double Area(Point A, Point B, Point C) {
  return 0.5 * std::fabs(A.x * B.y + B.x * C.y + C.x * A.y - B.x * A.y - A.x * C.y - C.x * B.y);
}

int CountInside(int a, int b, int c) {
  if(CrossProduct(pts[a], pts[c], pts[b]) > 0) {
    return under[a][b] + under[b][c] - under[a][c];
  } else {
    return under[a][c] - under[a][b] - under[b][c] - 1;
  }
}

void Solve() {
  std::vector<double > up, down; up.resize(k + 1); down.resize(k + 1);

  for(int i = 0; i < n; i++) {
    for(int j = i + 1; j < n; j++) {
      for(int itr = 0; itr <= k; itr++) {
        up[itr] = down[itr] = kMaxInf;
      }

      //  Check all triangles
      for(int act = 0; act < n; act++) {
        if(act == i || act == j) continue;

        int here;
        if(pts[act].x < pts[i].x) {
          here = CountInside(act, i, j);
        } else if(pts[act].x < pts[j].x) {
          here = CountInside(i, act, j);
        } else {
          here = CountInside(i, j, act);
        }

        if(here > k) here = k;

        if(CrossProduct(pts[i], pts[j], pts[act]) > 0) {  //  up
          up[here] = std::min(up[here], Area(pts[i], pts[j], pts[act]));
        } else {  //  down
          down[here] = std::min(down[here], Area(pts[i], pts[j], pts[act]));
        }
      }

      //  Update solution
      double dp = kMaxInf;
      for(int here = 0; here <= k; here++) {
        dp = std::min(dp, down[k - here]);
        sol = std::min(sol, up[here] + dp);
      }
    }
  }
}

int main() {
  ReadInput();

  ComputeDp();

  Solve();

  printf("%.1f\n", sol);
	return 0;
}
