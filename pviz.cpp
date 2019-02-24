/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("pviz.in", "r", stdin);
FILE *fout = freopen("pviz.out", "w", stdout);

const int MAX_N = 1 + 2000;
const int MOD = 10007;

/*-----------------------*/
int N, M;
int elem[MAX_N];
/*-----------------------*/
int dp[MAX_N][MAX_N];
/*-----------------------*/

void readInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= M; i++) {
        scanf("%d", &elem[i]);
    }
}

void runDP() {
    dp[1][1] = 1;
    for(int i = 2; i <= N; i++) {
        const int Limit = min(i, M);
        for(int j = 1; j <= Limit; j++) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] * (elem[j] - i + 1);
            dp[i][j] %= MOD;
        }
    }
}

void writeOutput() {
    printf("%d", dp[N][M]);
}

int main() {
    readInput();
    if(elem[M] != N) {
        printf("0"); return 0;
    }
    runDP();
    writeOutput();
    return 0;
}
