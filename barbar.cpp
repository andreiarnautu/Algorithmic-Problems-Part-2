/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <utility>
#include <cstring>

#define fi          first
#define se          second
#define mp          make_pair
#define MAX_R       1 + 1000 + 10

using namespace std;

FILE *fin=freopen("barbar.in","r",stdin);
FILE *fout=freopen("barbar.out","w",stdout);

const int dx[] = {-1, 1, 0, 0};
const int dy[] = { 0, 0,-1, 1};

queue < pair<int,int> > Q;
bool viz[MAX_R][MAX_R];
char a[MAX_R][MAX_R];
int dmin[MAX_R][MAX_R], sol[MAX_R][MAX_R];
int r, c, x1, y1, x2, y2;

void readData() {
  scanf("%d %d ", &r, &c);
  for(int i = 1; i <= r; ++i)
    scanf("%s", a[i] + 1);
}

void setMinDist() {
  for(int i = 1; i <= r; ++i)
    for(int j = 1; j <= c; ++j) {
      if(a[i][j] == 'D') {
        viz[i][j] = 1;
        Q.push(mp(i, j));
      }
      else if(a[i][j] == '*') {
        dmin[i][j] = -1;
        viz[i][j] = 1;
      }

      else if(a[i][j] == 'I') {
        x1 = i, y1 = j;
      }
      else if(a[i][j] == 'O') {
        x2 = i, y2 = j;
      }
    }
  int x, y, X, Y;

  while(!Q.empty()) {
    x = Q.front().fi, y = Q.front().se;
    Q.pop();

    for(int i = 0; i < 4; ++i) {
      X = x + dx[i];
      Y = y + dy[i];
      if(X && Y && X <= r && Y <= c && !viz[X][Y]) {
        dmin[X][Y] = dmin[x][y] + 1;
        Q.push(mp(X, Y));
        viz[X][Y] = 1;
      }
    }
  }
}

bool check(int dist) {
  if(dmin[x1][y1] < dist)
    return 0;

  memset(viz, 0, sizeof(viz));
  viz[x1][y1] = 1;
  Q.push(mp(x1, y1));

  int x, y, X, Y;

  while(!Q.empty()) {
    x = Q.front().fi, y = Q.front().se;
    Q.pop();

    if(x == x2 && y == y2) {
      while(!Q.empty())
        Q.pop();
      return 1;
    }

    for(int i = 0; i < 4; ++i) {
      X = x + dx[i];
      Y = y + dy[i];
      if(X && Y && X <= r && Y <= c && !viz[X][Y] && dmin[X][Y] >= dist) {
        Q.push(mp(X, Y));
        viz[X][Y] = 1;
      }
    }
  }
  return 0;
}

int main() {
  readData();
  setMinDist();
  int low = 0, high = r + c, mid, sol = 0;

  while(low <= high) {
    mid = (high + low) >> 1;
    if(check(mid))
      sol = mid, low = mid + 1;
    else
      high = mid - 1;
  }

  if(!sol)
    printf("-1");
  else
    printf("%d", sol);
  return 0;
}