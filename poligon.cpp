/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

#define x first
#define y second

FILE *fin = freopen("poligon.in", "r", stdin);
FILE *fout = freopen("poligon.out", "w", stdout);

typedef std::pair<double, double > Point;

const int kMaxN = 1 + 800;
const double eps = 1e-8;

/*-------- Structures --------*/
struct Line {
    double a, b, c;
    Line() {}
    Line(const double _a, const double _b, const double _c) {
        a = _a; b = _b; c = _c;
    }
};
/*-------- Polygon data --------*/
int N;
Point points[kMaxN];
Line lines[kMaxN];
std::vector<int > xCoords;
std::vector<std::pair<double, int > > segments[kMaxN];
/*-------- Query data --------*/
int M;
/*-------- --------*/

double CrossProduct(Point O, Point A, Point B) {
    return (A.x - O.x) * (B.y - O.y) - (B.x - O.x) * (A.y - O.y);
}

Line GetLine(Point A, Point B) {
    Line d;
    d.a = B.y - A.y;
    d.b = A.x - B.x;
    d.c = A.y * B.x - A.x * B.y;
    return d;
}

void ProcessPolygon() {
    scanf("%d%d", &N, &M);
    for(int i = 0; i < N; i++) {
        scanf("%lf%lf", &points[i].x, &points[i].y);
        xCoords.push_back((int)points[i].x);
    }
    points[N] = points[0];
    for(int i = 0; i < N; i++) {
        if(points[i] <= points[i + 1]) {
            lines[i] = GetLine(points[i], points[i + 1]);
        } else {
            lines[i] = GetLine(points[i + 1], points[i]);
        }
    }

    std::sort(xCoords.begin(), xCoords.end());
    xCoords.erase(std::unique(xCoords.begin(), xCoords.end()), xCoords.end());

    for(int i = 0; i < (int)xCoords.size() - 1; i++) {
        double x1 = xCoords[i], x2 = xCoords[i + 1];
        for(int j = 0; j < N; j++) {
            if(lines[j].b == 0.0) continue;
            Point P1, P2;
            P1.x = x1; P2.x = x2;
            P1.y = (-lines[j].c - lines[j].a * P1.x) / lines[j].b;
            P2.y = (-lines[j].c - lines[j].a * P2.x) / lines[j].b;
            if((points[j].x <= x1 + eps && x2 <= points[j + 1].x + eps) || (points[j + 1].x <= x1 + eps && x2 <= points[j].x + eps)) {
                segments[i].push_back({(P1.y + P2.y) / 2, j});
            }
        }
        std::sort(segments[i].begin(), segments[i].end());
    }
}

void ProcessQueries() {
    int solution = 0;

    for(int query = 1; query <= M; query++) {
        Point Q; scanf("%lf%lf", &Q.x, &Q.y);
        if(Q.x >= xCoords[0] - eps && Q.x <= xCoords.back() + eps) {
            int left = 0, right = (int)xCoords.size() - 2, answer = 0;
            while(left <= right) {
                int mid = (left + right) >> 1;
                if(xCoords[mid] - eps <= Q.x && Q.x <= xCoords[mid + 1] + eps) {
                    answer = mid; break;
                } else if(Q.x <= xCoords[mid] + eps) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }

            left = 0, right = (int)segments[answer].size() - 1;
            int above = 0;
            while(left <= right) {
                int mid = (left + right) >> 1;
                Line line = lines[segments[answer][mid].second];
                if(-eps <= line.a * Q.x + line.b * Q.y + line.c && line.a * Q.x + line.b * Q.y + line.c <= eps) {
                    above = 1; break;
                }
                else if(line.a * Q.x + line.b * Q.y + line.c < 0) {
                    above = mid + 1;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            solution += (above % 2 == 1);
        }
    }
    printf("%d\n", solution);
}

int main() {
    ProcessPolygon();
    ProcessQueries();
    return 0;
}
