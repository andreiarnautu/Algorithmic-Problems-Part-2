/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

#define x first
#define y second
#define leftSon (node * 2)
#define rightSon (node * 2 + 1)

typedef std::pair<int, int > Point;

FILE *fin = freopen("zoo.in", "r", stdin); FILE *fout = freopen("zoo.out", "w", stdout);

const int maxN = 16000 + 5;

/*-------- Data --------*/
int n;
Point pts[maxN];

std::vector<int > coords[maxN * 4];
/*-------- --------*/

void ReadInput() {
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    scanf("%d%d", &pts[i].x, &pts[i].y);
  }
  std::sort(pts + 1, pts + n + 1);
}

void Build(int node, int left, int right) {
  for(int i = left; i <= right; i++) {
    coords[node].push_back(pts[i].y);
  }
  std::sort(coords[node].begin(), coords[node].end());

  if(left < right) {
    int mid = (left + right) / 2;

    Build(leftSon, left, mid); Build(rightSon, mid + 1, right);
  }
}

int Query(int node, int left, int right, int first, int last, int y1, int y2) {
  if(first <= left && right <= last) {
    return std::upper_bound(coords[node].begin(), coords[node].end(), y2) - std::lower_bound(coords[node].begin(), coords[node].end(), y1);
  }

  int ans = 0, mid = (left + right) / 2;

  if(first <= mid) {
    ans += Query(leftSon, left, mid, first, last, y1, y2);
  }
  if(mid < last) {
    ans += Query(rightSon, mid + 1, right, first, last, y1, y2);
  }

  return ans;
}

void ProcessQueries() {
  int m; scanf("%d", &m);
  for(int i = 0; i < m; i++) {
    int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

    int left = std::lower_bound(pts + 1, pts + n + 1, std::make_pair(x1, y1)) - pts;
    int right = std::upper_bound(pts + 1, pts + n + 1, std::make_pair(x2, y2)) - pts - 1;

    if(left > right) {
      printf("0\n");
    } else {
      printf("%d\n", Query(1, 1, n, left, right, y1, y2));
    }
  }
}

int main() {
  ReadInput();

  Build(1, 1, n);

  ProcessQueries();
  return 0;
}
