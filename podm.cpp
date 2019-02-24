/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("podm.in", "r", stdin); FILE *fout = freopen("podm.out", "w", stdout);

/*-------- Data --------*/
int N;
std::vector<int > d;
std::vector<std::vector<long long > > dp;
/*-------- --------*/

void ReadData() {
    scanf("%d", &N);
    d = std::vector<int >(N + 1, 0);
    dp = std::vector<std::vector<long long > >(N, std::vector<long long >(N, 1e15));

    for(auto& x : d) {
        scanf("%d", &x);
    }
}

void RunDP() {
    for(int i = N - 1; i >= 0; i--) {
        dp[i][i] = 0;
        for(int j = i + 1; j < N; j++) {
            for(int k = i; k < j; k++) {
                dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k + 1][j] + 1LL * d[i] * d[k + 1] * d[j + 1]);
            }
        }
    }
}

int main() {
    ReadData();

    RunDP();

    printf("%lld\n", dp[0][N - 1]);
	return 0;
}
