/**
  *  Worg
  */
#include <queue>
#include <bitset>
#include <cstdio>
 
FILE *fin = freopen("tsunami.in", "r", stdin); FILE *fout = freopen("tsunami.out", "w", stdout);
 
const int MAX_N = 1000 + 5;
const int dx[] = {-1, 1, 0,  0};
const int dy[] = { 0, 0, 1, -1};
 
int n, m, h;
short int mat[MAX_N][MAX_N];
std::bitset<MAX_N > affected[MAX_N];
 
 
 
void ReadInput() {
  scanf("%d%d%d", &n, &m, &h);
 
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      scanf("%d", &mat[i][j]);
    }
  }
}
 
bool Valid(int x, int y) {
  return 1 <= x && x <= n && 1 <= y && y <= m;
}
 
int Solve() {
  std::queue<std::pair<short int, short int > > q;
 
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      if(mat[i][j] == 0 || mat[i][j] >= h) continue;
 
      bool ok = false;
      for(int d = 0; d < 4; d++) {
        int x = i + dx[d], y = j + dy[d];
 
        if(Valid(x, y) && mat[x][y] == 0) {
          ok = true;
        }
      }
 
      if(ok) {
        q.emplace(i, j);
        affected[i][j] = true;
      }
    }
  }
 
  while(!q.empty()) {
    int x = q.front().first, y = q.front().second;
    q.pop();
 
    for(int d = 0; d < 4; d++) {
      int new_x = x + dx[d], new_y = y + dy[d];
 
      if(Valid(new_x, new_y) && !affected[new_x][new_y] && mat[new_x][new_y] < h & mat[new_x][new_y] != 0) {
        affected[new_x][new_y] = true;
        q.emplace(new_x, new_y);
      }
    }
  }
 
  int ans = 0;
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      ans += affected[i][j];
    }
  }
 
  return ans;
}
 
int main() {
  ReadInput();
 
  printf("%d\n", Solve());
 
  return 0;
}