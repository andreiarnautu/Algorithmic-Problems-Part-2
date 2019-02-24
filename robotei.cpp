/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("robotei.in", "r", stdin); FILE *fout = freopen("robotei.out", "w", stdout);

/*-------- Data --------*/
int N, M, X, Y, modX, modY, offsetX, offsetY;

std::vector<std::vector<int > > count, dist;
std::vector<std::vector<bool > > seen;
int cycleLength, oldX, oldY;

std::vector<int > ans;
/*-------- --------*/

void GetCount() {
  count = std::vector<std::vector<int > >(modX, std::vector<int >(modY, 0));

  std::vector<int > fx(modX), fy(modY);

  for(int i = 0; i < N; i++) {
    int x = (i * i + offsetX) % modX;
    int y = (i * i + offsetY) % modY;
    fx[x]++; fy[y]++;
  }

  for(int i = 0; i < modX; i++) {
    for(int j = 0; j < modY; j++) {
      count[i][j] = fx[i] * fy[j];
    }
  }

  if(X < modX && Y < modY) {
    count[(X * X + offsetX) % modX][(Y * Y + offsetY) % modY]--;
  }
}

void Next() {
  if(seen[oldX][oldY]) {
    if(oldX != X || oldY != Y) {
      cycleLength = -1;
    }
    return;
  }
  cycleLength++; seen[oldX][oldY] = 1;

  oldX = (oldX * oldX + offsetX) % modX; oldY = (oldY * oldY + offsetY) % modY;
  Next();
}

void CheckCycle() {
  seen = std::vector<std::vector<bool > >(modX, std::vector<bool >(modY, false));

  oldX = X; oldY = Y; Next();
}

void GetNextDist(int x, int y) {
  if(seen[x][y]) {
    return;
  }
  seen[x][y] = true;
  GetNextDist((x * x + offsetX) % modX, (y * y + offsetY) % modY);

  int d = dist[(x * x + offsetX) % modX][(y * y + offsetY) % modY];
  if(d == -1) {
    dist[x][y] = -1;
  } else {
    dist[x][y] = d + 1;
  }
}

void GetDistances() {
  seen = std::vector<std::vector<bool > >(modX, std::vector<bool >(modY, false));
  dist = std::vector<std::vector<int > >(modX, std::vector<int >(modY, -1));
  seen[X][Y] = true; dist[X][Y] = 0;

  for(int i = 0; i < modX; i++) {
    for(int j = 0; j < modY; j++) {
      if(!seen[i][j]) {
        GetNextDist(i, j);
      }
    }
  }
}

int main() {
  scanf("%d%d%d%d%d%d%d%d", &N, &M, &X, &Y, &modX, &modY, &offsetX, &offsetY);

  if(X >= modX || Y >= modY) {
    printf("0 %d\n", N * N - 1);
    printf("1 1\n");
    return 0;
  }

  GetCount();

  CheckCycle();

  GetDistances();

  std::vector<int > ans(M + 2, 0);
  for(int i = 0; i < modX; i++) {
    for(int j = 0; j < modY; j++) {
      if(dist[i][j] == -1) {ans[0] += count[i][j]; continue;}

      if(dist[i][j] < M) {
        int crt = 1;

        if(cycleLength != -1) {
          crt += (M - dist[i][j] - 1) / cycleLength;
        }
        ans[crt] += count[i][j];
      } else {
        ans[0] += count[i][j];
      }
    }
  }

  if(cycleLength != -1 && X < modX && Y < modY) {
    int crt = 1 + M / cycleLength;
    ans[crt]++;
  } else if(cycleLength == -1 && X < modX && Y < modY) {
    ans[1] ++;
  }

  for(int i = 0; i <= M; i++) {
    if(ans[i] == 0) continue;
    printf("%d %d\n", i, ans[i]);
  }

	return 0;
}
