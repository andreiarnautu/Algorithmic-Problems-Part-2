/**
  *  Worg
  */
#include <cstdio>

#define i64 long long int

using namespace std;
FILE *fin=freopen("planeta.in","r",stdin);
FILE *fout=freopen("planeta.out","w",stdout);

i64 dp[31];

void get(i64 x, i64 left, i64 right) {

    if( left > right )
        return;
    if( left == right ) {
        printf("%lld ", left); return;
    }

    i64 i, s = 0;
    for(i = left; i <= right; ++i) {

        s += dp[i - left] * dp[right - i];
        if( s >= x ) {
            s -= dp[i - left] * dp[right - i];
            break;
        }
    }

    printf("%lld ", i);
    get((x - s - 1) / dp[right - i] + 1, left, i - 1);
    get((x - s - 1) % dp[right - i] + 1, i + 1, right);
}

int main() {

    i64 n, k;
    scanf("%lld %lld", &n, &k);

    dp[0] = 1;
    for(i64 i = 1; i <= n; ++i)
        for(i64 j = 0; j < i; ++j)
            dp[i] += dp[j] * dp[i - j - 1];

    get(k, 1, n);
    return 0;
}
