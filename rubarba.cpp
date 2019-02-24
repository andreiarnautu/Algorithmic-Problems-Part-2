/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

#define x first
#define y second

FILE *fin = freopen("rubarba.in", "r", stdin); FILE *fout = freopen("rubarba.out", "w", stdout);

const long double eps = 1e-17;
const long double maxC = 1e9;

/*--------- Data --------*/
int N;
std::vector<std::pair<int, int > > points;
/*--------- --------*/

long double Compute(long double alfa) {
  long double sin = std::sin(alfa), cos = std::cos(alfa);
  long double maxX = -maxC, maxY = -maxC, minX = maxC, minY = maxC;

  for(auto& p : points) {
    long double x = p.x * cos - p.y * sin;
    long double y = p.x * sin + p.y * cos;

    minX = std::min(minX, x); maxX = std::max(maxX, x);
    minY = std::min(minY, y); maxY = std::max(maxY, y);
  }

  return (maxY - minY) * (maxX - minX);
}

int main() {
  scanf("%d", &N);
  for(int i = 0; i < N; i++) {
    int a, b; scanf("%d%d", &a, &b);
    points.emplace_back(a, b);
  }

  long double left = 0, right = acos(-1.0) * 0.5, mid;

  while(right - left > eps) {
    mid = (left + right) * 0.5;

    if(Compute(mid) > Compute(mid + eps)) {
      left = mid;
    } else {
      right = mid;
    }
  }

  printf("%.2Lf", Compute(left));

  return 0;
}
