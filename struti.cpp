/**
  *  Worg
  */
#include <deque>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("struti.in", "r", stdin); FILE *fout = freopen("struti.out", "w", stdout);

const int kMaxN = 1e3 + 1;
const int kMaxInf = 1e9;

/*-------- Data --------*/
int N, M, P;
int a[kMaxN][kMaxN];

int dx, dy;
int best, cnt;

int min[kMaxN][kMaxN], max[kMaxN][kMaxN];
/*-------- --------*/

void ComputePartials() {
  for(int j = 1; j <= M; j++) {
    std::deque<int > dqmin, dqmax;

    for(int i = 1; i <= N; i++) {
      while(!dqmin.empty() && a[i][j] <= a[dqmin.back()][j]) {
        dqmin.pop_back();
      }
      dqmin.push_back(i);

      while(!dqmax.empty() && a[i][j] >= a[dqmax.back()][j]) {
        dqmax.pop_back();
      }
      dqmax.push_back(i);

      if(i - dqmin.front() == dx) {
        dqmin.pop_front();
      }
      if(i - dqmax.front() == dx) {
        dqmax.pop_front();
      }

      min[i][j] = a[dqmin.front()][j];
      max[i][j] = a[dqmax.front()][j];
    }
  }
}

void ComputeAnswer() {
  for(int i = dx; i <= N; i++) {
    std::deque<int > dqmin, dqmax;

    for(int j = 1; j <= M; j++) {
      while(!dqmin.empty() && min[i][j] <= min[i][dqmin.back()]) {
        dqmin.pop_back();
      }
      dqmin.push_back(j);

      while(!dqmax.empty() && max[i][j] >= max[i][dqmax.back()]) {
        dqmax.pop_back();
      }
      dqmax.push_back(j);

      if(j - dqmin.front() == dy) {
        dqmin.pop_front();
      }
      if(j - dqmax.front() == dy) {
        dqmax.pop_front();
      }

      if(j >= dy) {
        int crt = max[i][dqmax.front()] - min[i][dqmin.front()];

        if(crt < best) {
          best = crt; cnt = 1;
        } else if(crt == best) {
          cnt++;
        }
      }
    }
  }
}

int main() {
  scanf("%d%d%d", &N, &M, &P);
  for(int i = 1; i <= N; i++) {
    for(int j = 1; j <= M; j++) {
      scanf("%d", &a[i][j]);
    }
  }

  for(int t = 0; t < P; t++) {
    scanf("%d%d", &dy, &dx);
    best = kMaxInf; cnt = 0;

    ComputePartials();
    ComputeAnswer();

    if(dx != dy) {
      std::swap(dy, dx);

      ComputePartials();
      ComputeAnswer();
    }
    printf("%d %d\n", best, cnt);
  }
	return 0;
}
