/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

#define x first
#define y second

typedef std::pair<double, double > Point;

const double eps = 1e-8;

FILE *fin = freopen("rubarba.in", "r", stdin); FILE *fout = freopen("rubarba.out", "w", stdout);

/*-------- Data --------*/
struct Line {
  double a, b, c;

  Line() {}

  Line(double _a, double _b, double _c) {a = _a; b = _b; c = _c;}
};

int N;
std::vector<Point > points;
/*-------- --------*/

void ReadInput() {
  scanf("%d", &N); points.resize(N);
  for(auto& itr : points) {
    scanf("%lf%lf", &itr.first, &itr.second);
  }
}

double CCW(Point A, Point B, Point C) {
  return (B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y);
}

std::vector<Point > ConvexHull(std::vector<Point > v) {
  for(int i = 1; i < N; i++) {
    if(v[i] < v[0]) {
      std::swap(v[0], v[i]);
    }
  }

  std::sort(v.begin() + 1, v.end(), [&](Point A, Point B) {
    return CCW(v[0], A, B) < 0;
  });

  std::vector<Point > stack;

  for(auto& act : v) {
    while((int)stack.size() > 1 && CCW(stack[(int)stack.size() - 2], stack[(int)stack.size() - 1], act) > -eps) {
      stack.pop_back();
    }
    stack.push_back(act);
  }

  return stack;
}

Line GetLine(Point A, Point B) {
  Line l = {B.y - A.y, A.x - B.x, A.y * B.x - A.x * B.y};
  double coef = 1 / std::sqrt(l.a * l.a + l.b * l.b);
  l.a *= coef; l.b *= coef; l.c *= coef;

  return l;
}

double Dist(Line l, Point A) {
  return l.a * A.x + l.b * A.y + l.c;
}

Line GetPerpendicular(Line l, Point A) {
  Line lp;
  lp.a = -l.b; lp.b = l.a;
  lp.c = -lp.a * A.x - lp.b * A.y;

  double coef = 1 / std::sqrt(lp.a * lp.a + lp.b * lp.b);
  lp.a *= coef; lp.b *= coef; lp.c *= coef;

  return lp;
}

double GetMinArea() {
  double ans = 1e14;

  int n = (int)points.size();

  if(n < 3) {
    return 0.0;
  }

  //!  Do first iteration separately

  Point A = points[0], B = points[1];
  Line L = GetLine(A, B);

  int cursor1 = 0, cursor2 = 0, cursor3 = 0;

  double dx = 0.0, dy1 = 0.0, dy2 = 0.0;
  for(int i = 0; i < n; i++) {
    double d = std::max(Dist(L, points[i]), -Dist(L, points[i]));

    if(d > dx) {
      cursor1 = i; dx = d;
    }
  }

  Line Lp = GetPerpendicular(L, A);
  for(int i = 0; i < n; i++) {
    if(Dist(Lp, points[i]) > dy1) {
      cursor2 = i; dy1 = Dist(Lp, points[i]);
    }
    if(Dist(Lp, points[i]) < dy2) {
      cursor3 = i; dy2 = Dist(Lp, points[i]);
    }
  }

  ans = dx * (dy1 - dy2);

  //!  Continue using existing cursors
  for(int i = 1; i < n; i++) {
    Point A = points[i], B = points[(i + 1 == n) ? 0 : (i + 1)];

    Line L = GetLine(A, B);
    Line Lp = GetPerpendicular(L, A);

    double dx = std::max(Dist(L, points[cursor1]), -Dist(L, points[cursor1]));

    int nxt = (cursor1 + 1) == n ? 0 : (cursor1 + 1);
    while(dx < std::max(Dist(L, points[nxt]), -Dist(L, points[nxt])) + eps) {
      cursor1 = nxt;
      dx = std::max(Dist(L, points[nxt]), -Dist(L, points[nxt]));
      nxt = (cursor1 + 1) == n ? 0 : (cursor1 + 1);
    }

    double dy1 = Dist(Lp, points[cursor2]);

    nxt = (cursor2 + 1) == n ? 0 : (cursor2 + 1);
    while(dy1 < Dist(Lp, points[nxt]) + eps) {
      cursor2 = nxt;
      dy1 = Dist(Lp, points[cursor2]);
      nxt = (cursor2 + 1) == n ? 0 : (cursor2 + 1);
    }

    double dy2 = Dist(Lp, points[cursor3]);

    nxt = (cursor3 + 1) == n ? 0 : (cursor3 + 1);
    while(dy2 > (Dist(Lp, points[nxt])) - eps) {
      cursor3 = nxt;
      dy2 = Dist(Lp, points[cursor3]);
      nxt = (cursor3 + 1) == n ? 0 : (cursor3 + 1);
    }

    ans = std::min(ans, dx * (dy1 - dy2));
  }

  return ans;
}

int main() {
  ReadInput();

  points = ConvexHull(points);

  printf("%.2f\n", GetMinArea());
  return 0;
}
