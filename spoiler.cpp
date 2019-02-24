/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin=freopen("spoiler.in","r",stdin);
FILE *fout=freopen("spoiler.out","w",stdout);

int n, k, a, b;
long long dp[501][501], sus, jos, p = 1;

void readData() {

    scanf("%d %d ", &n, &k);
    a = (n + 1) / 2, b = k - a;
}

void runDp() {

    dp[0][0] = 1;
    for(int i = 1; i <= b; ++i) {

        dp[i][0] = 1;
        for(int j = 1; j < i; ++j)
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        dp[i][i] = dp[i][i - 1] * 2;
    }
    jos = 2 * b;

}

int main() {

    readData();
    runDp();
    return 0;
}
