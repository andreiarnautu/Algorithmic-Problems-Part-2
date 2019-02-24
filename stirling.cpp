/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("stirling.in", "r", stdin);
FILE *fout = freopen("stirling.out", "w", stdout);

const int MAX_N = 1 + 200;
const int MOD = 98999;

int s[MAX_N][MAX_N]; /* speta 1 */
int S[MAX_N][MAX_N]; /* speta 2 */

void preProcessate() {
    s[1][1] = S[1][1] = 1;
    for(int i = 2; i < MAX_N; ++i) {
        for(int j = 1; j <= i; j++) {
            s[i][j] = (s[i - 1][j - 1] - (i - 1) * s[i - 1][j]) % MOD;
            S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j]) % MOD;
        }
    }
}

int main() {
    preProcessate();
    int T;
    for(scanf("%d", &T); T; T--) {
        int kind, n, m; scanf("%d%d%d", &kind, &n, &m);
        if(kind == 1) {
            printf("%d\n", s[n][m]);
        } else {
            printf("%d\n", S[n][m]);
        }
    }
    return 0;
}
