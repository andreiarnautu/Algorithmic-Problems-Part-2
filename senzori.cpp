/**
  *  Worg
  *  Mar 22, 2018
  *  10:20:28 AM
  */
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

FILE *fin = freopen("senzori.in", "r", stdin); FILE *fout = freopen("senzori.out", "w", stdout);

const int maxN = 2000 + 5;
const int maxT = 2000;

/*-------- Data --------*/
int n;
int t1[maxN], t2[maxN], d[maxN], v[maxN];

int take[3][maxN], pref[3][maxN], suff[3][maxN];
int pass[3];
/*-------- --------*/

void ReadInput() {
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    scanf("%d%d%d%d", &t1[i], &t2[i], &d[i], &v[i]);
  }
}

void ComputePartials(int take[maxN], int pref[maxN], int suff[maxN]) {
  pref[0] = take[0];
  for(int i = 1; i <= maxT; i++) {
    pref[i] = std::max(take[i], pref[i - 1]);
  }

  suff[maxT] = take[maxT];
  for(int i = maxT - 1; i >= 0; i--) {
    suff[i] = std::max(take[i], suff[i + 1]);
  }
}

void RunDp() {
  //  Just start off by having steps 0 and 1 solved
  for(int i = t1[1]; i + d[1] <= t2[1]; i++) {
    take[1][i] = v[1];
  }

  ComputePartials(take[1], pref[1], suff[1]);


  //  Now move on to the actual dp
  for(int i = 2; i <= n; i++) {
    //  Compute pass[2]
    pass[2] = std::max(pass[1], pref[1][maxT]);

    //  Compute take[2][]
    for(int j = t1[i]; j + d[i] <= t2[i]; j++) {
      take[2][j] = pass[1];

      if(j >= d[i - 1]) take[2][j] = std::max(take[2][j], pref[1][j - d[i - 1]]);

      if(j + d[i] + d[i - 1] <= t2[i - 1]) take[2][j] = std::max(take[2][j], suff[1][j + d[i]]);

      take[2][j] += v[i];  //  Add current value
    }

    memcpy(take[0], take[1], sizeof(take[0]));
    memcpy(take[1], take[2], sizeof(take[2]));
    pass[0] = pass[1]; pass[1] = pass[2];

    memset(take[2], 0, sizeof(take[2])); pass[2] = 0;
    memset(pref[0], 0, sizeof(pref[0])); memset(suff[0], 0, sizeof(suff[0]));
    memset(pref[1], 0, sizeof(pref[1])); memset(suff[1], 0, sizeof(suff[1]));

    ComputePartials(take[1], pref[1], suff[1]);
  }

  int sol = std::max(pass[1], pref[1][maxT]);

  printf("%d\n", sol);
}

int main() {
  ReadInput();

  RunDp();

  return 0;
}
