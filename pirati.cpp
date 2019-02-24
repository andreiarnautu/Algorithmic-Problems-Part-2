/**
  *  Worg
  */
#include <vector>
#include <string>
#include <fstream>

std::ifstream fin("pirati.in"); std::ofstream fout("pirati.out");

std::vector<int > dx = {-1, -1, -1,  0, 0,  1, 1, 1};
std::vector<int > dy = {-1,  0,  1, -1, 1, -1, 0, 1};

bool Valid(const int &n, const int &m, const int x, const int y) {
  return 0 <= x && x < n && 0 <= y && y < m;
}

void Fill(std::vector<std::string > &map, std::vector<std::vector<int > > &zone, std::vector<int > &parent, std::vector<int > &height, const int &n, const int &m, const int x, const int y, const int &value, const int &zone_id) {
  if (zone[x][y] != -1) {
    if (zone[x][y] != zone_id) {
      parent.back() = zone[x][y];
      height.back() = height[zone[x][y]] + 1;
    }
    return;
  }

  if (map[x][y] != value) return;

  zone[x][y] = zone_id;

  for (int i = 0; i < 8; i++) {
    int new_x = x + dx[i], new_y = y + dy[i];

    if (Valid(n, m, new_x, new_y)) {
      Fill(map, zone, parent, height, n, m, new_x, new_y, value, zone_id);
    }
  }
}

int GetLCA(std::vector<int > &parent, std::vector<int > &height, int u, int v) {
  while (u != v) {
    if (height[u] > height[v]) {
      u = parent[u];
    } else {
      v = parent[v];
    }
  }

  return u;
}

int main() {
  int n, m, q; fin >> n >> m >> q;
  std::vector<std::string > map(n);
  for (auto& line : map) {
    fin >> line;
  }

  std::vector<std::vector<int > > zone(n, std::vector<int >(m, -1));
  std::vector<int > parent, height;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (zone[i][j] == -1) {
        parent.push_back(-1); height.push_back(0);

        Fill(map, zone, parent, height, n, m, i, j, map[i][j], (int)parent.size() - 1);
      }
    }
  }

  for (int i = 0; i < q; i++) {
    int x1, y1, x2, y2; fin >> x1 >> y1 >> x2 >> y2;
    x1--; y1--; x2--; y2--;

    int lca = GetLCA(parent, height, zone[x1][y1], zone[x2][y2]);

    fout << (height[zone[x1][y1]] + height[zone[x2][y2]] - 2 * height[lca]) / 2 << '\n';
  }
  return 0;
}