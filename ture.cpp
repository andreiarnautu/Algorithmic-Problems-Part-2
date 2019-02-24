/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("ture.in", "r", stdin);
FILE *fout = freopen("ture.out", "w", stdout);

const int MIN_N = 16,
          MAX_N = 1 + 250;

long long int dp[2][1 << MIN_N];
bool M[MAX_N][MAX_N], A[MAX_N][MAX_N];
char bit[1 << MIN_N];

int n, m, k, p;
long long int posCount;

void readData() {

    scanf("%d%d%d", &n, &m, &k);
    scanf("%d", &p);
    for(int i = 1; i <= p; ++i) {

        int x, y; scanf("%d%d", &x, &y);
        M[x][y] = true;
    }

    if(n > m) {

        for(int i = 1; i <= m; ++i)
            for(int j = 1; j <= n; ++j)
                A[i][j] = M[j][m - i + 1];
        swap(m, n);
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                M[i][j] = A[i][j];
    }
}

void runDp() {

    int limit = (1 << (n));
    for(int i = 0; i <= n; ++i)
        bit[1 << i] = i;

    for(int i = 1; i <= n; ++i) /* initializam pentru coloana 1 */
        if(!M[i][1]) {

            dp[1][1 << (i - 1)] = dp[0][1 << (i - 1)] = 1;
        }

    dp[0][0] = 1;
    for(int i = 2; i <= m; ++i) {

        for(int mask = 0; mask < limit; ++mask) { /* calculam dp[i][mask] */

            dp[1][mask] = dp[0][mask];
            int tmpMask = mask, bitCount = 0;
            while(tmpMask) {

                int newMask = tmpMask & (tmpMask - 1);
                int lin = bit[newMask ^ tmpMask];
                tmpMask = newMask;

                if(!M[lin + 1][i])  /* daca casuta curenta nu e marcata */
                    dp[1][mask] += dp[0][mask ^ (1 << lin)];
                ++bitCount;
            }
        }
        for(int j = 0; j < limit; ++j)
            dp[0][j] = dp[1][j];
    }

    for(int mask = 0; mask < limit; ++ mask) {

        int tmpMask = mask;

        int bitCount = 0;
        while(tmpMask) {

            tmpMask = tmpMask & (tmpMask - 1);
            bitCount++;
        }
        if(bitCount == k)
            posCount += dp[1][mask];
    }
    printf("%lld", posCount);
}

int main() {

    readData();
    runDp();
    return 0;
}
