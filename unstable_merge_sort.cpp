/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

const int kMaxN = 600 + 10;

/*-------- Data --------*/
int N;
int v[kMaxN];
double prob[kMaxN][kMaxN];

std::vector<std::pair<int, int > > ranges;

double sol[kMaxN];
/*-------- --------*/

int Count(int left, int right, int value) {
  int ans = 0;
  for(int i = left; i <= right; i++) {
    ans += (v[i] == value) ? 1 : 0;
  }

  return ans;
}

void SolveElement(int pos) {
  int sz = (int)ranges.size();

  std::vector<std::vector<double > > probPos(2, std::vector<double >(N + 5, 0.0));
  probPos[0][1] = 1.0;

  for(int i = sz - 2; i >= 0; i--) {
    int left = ranges[i].first, right = ranges[i].second;

    int mid = (left + right) / 2;
    int cntLeft = Count(left, mid, v[pos]);
    int cntRight = Count(mid + 1, right, v[pos]);

    if(pos > mid) {
      std::swap(cntLeft, cntRight);
    }

    if(!cntRight) {
      continue;
    }

    //  Compute prob
    for(int j = 1; j <= cntLeft + 1; j++) {
      for(int k = 1; k <= cntRight + 1; k++) {
        prob[j][k] = 0.0;
      }
    }
    prob[1][1] = 1.0;
    for(int j = 1; j <= cntLeft + 1; j++) {
      for(int k = 1; k <= cntRight + 1; k++) {
        if(j <= cntLeft && k <= cntRight) {
          prob[j + 1][k] += prob[j][k] * 0.5;
          prob[j][k + 1] += prob[j][k] * 0.5;
        } else if(j <= cntLeft) {
          prob[j + 1][k] += prob[j][k];
        } else if(k <= cntRight) {
          prob[j][k + 1] += prob[j][k];
        }
      }
    }

    for(int j = 1; j <= cntLeft; j++) {
      double probHere = probPos[0][j];

      for(int k = 1; k <= cntRight + 1; k++) {
        if(k <= cntRight) {
          probPos[1][j + k - 1] += probHere * prob[j][k] * 0.5;
        } else {
          probPos[1][j + k - 1] += probHere * prob[j][k];
        }
      }

    }

    probPos[0] = probPos[1];
    probPos[1] = std::vector<double >(N + 5, 0.0);
  }

  int cntLower = 0, cntHere = 0;
  for(int i = 1; i <= N; i++) {
    cntLower += (v[i] < v[pos]) ? 1 : 0;
    cntHere += (v[i] == v[pos]) ? 1 : 0;
  }

  sol[pos] = cntLower;
  for(int i = 1; i <= cntHere; i++) {
    sol[pos] += probPos[0][i] * i;
  }
}

void Divide(int left, int right) {
  ranges.emplace_back(left, right);

  if(left == right) {
    SolveElement(left);
  } else {
    Divide(left, (left + right) / 2);
    Divide((left + right) / 2 + 1, right);
  }

  ranges.pop_back();
}

int main() {
  scanf("%d", &N);
  for(int i = 1; i <= N; i++) {
    scanf("%d", &v[i]);
  }

  Divide(1, N);

  for(int i = 1; i <= N; i++) {
    printf("%.12f\n", sol[i]);
  }
  return 0;
}
