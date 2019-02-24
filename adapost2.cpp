/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <vector>

#define x first
#define y second

typedef std::pair<double, double > Point;

FILE *fin = freopen("adapost2.in", "r", stdin); FILE *fout = freopen("adapost2.out", "w", stdout);

const int MAX_N = 50000 + 5;
const std::vector<int > dx = {-1, -1, -1,  0, 0,  1, 1, 1};
const std::vector<int > dy = {-1,  0,  1, -1, 1, -1, 0, 1};

//-------- Data --------
int n;
Point pts[MAX_N];
//-------- --------


void ReadInput() {
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    scanf("%lf %lf", &pts[i].x, &pts[i].y);
  }
}

double PointDistance(Point A, Point B) {
  return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

double ComputeTotalDistance(Point shelter) {
  double total_distance = 0.0;

  for (int i = 0; i < n; i++) {
    total_distance += PointDistance(pts[i], shelter);
  }

  return total_distance;
}

Point GetShelter() {
  Point shelter = {0.0, 0.0};
  double dist = 500;
  double current_distance = ComputeTotalDistance(shelter);

  for (int step = 0; step < 20; step++) {
    Point current_shelter = shelter;

    for (int i = 0; i < (int)dx.size(); i++) {
      Point new_shelter = shelter;

      new_shelter.x += dist * dx[i]; new_shelter.y += dist * dy[i];

      double total_distance = ComputeTotalDistance(new_shelter);

      if (total_distance < current_distance) {
        current_distance = total_distance;
        current_shelter = new_shelter;
      }
    }

    shelter = current_shelter;
    dist *= 0.5;
  }

  return shelter;
}

int main() {
  ReadInput();

  Point shelter_location = GetShelter();

  printf("%.6f %.6f\n", shelter_location.x, shelter_location.y);

  return 0;
}