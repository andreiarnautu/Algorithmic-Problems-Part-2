/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("sobo.in", "r", stdin);
FILE *fout = freopen("sobo.out", "w", stdout);

const int MAX_N = 15,
          MAX_L = 1000,
          MAX_INF = 0x3fffffff;

char sir[MAX_N][MAX_L];
bool s[MAX_N][MAX_L];
int cost[MAX_L];
int n, l;   /* general variables */

char bit[1 << MAX_N]; /* for dp */
int dp[1 << MAX_N];
int limit;

void readData() {

    scanf("%d%d ", &n, &l);
    for(int i = 0; i < n; ++i)
        gets(sir[i]);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < l; ++j) {

            if(sir[i][j] == '0')
                s[i][j] = 0;
            else
                s[i][j] = 1;
        }
    for(int i = 0; i < l; ++i)
        scanf("%d", &cost[i]);
    limit = (1 << n);
}

void initializeDp() {

    for(int i = 0; i < limit; ++i)
        dp[i] = MAX_INF;
    for(int i = 0; i < n; ++i) {

        dp[1 << i] = 0;
        bit[1 << i] = i;
    }
}

int getDp(int mask) {

    int ret;
    if(dp[mask] != MAX_INF)
        ret = dp[mask];
    else {

        for(int i = 0; i < l; ++i) {

            int leftMask = 0, rightMask = 0;
            int tmpMask = mask;
            while(tmpMask) {

                int newMask = tmpMask & (tmpMask - 1);
                int nr = bit[newMask ^ tmpMask];
                tmpMask = newMask;

                if(!s[nr][i])
                    leftMask ^= (1 << nr);
                else
                    rightMask ^= (1 << nr);
            }
            if(leftMask && rightMask)
                dp[mask] = min(dp[mask], max(getDp(leftMask),getDp(rightMask)) + cost[i]);
        }
        ret = dp[mask];
    }

    return ret;
}

int main() {

    readData();
    initializeDp();
    printf("%d", getDp(limit - 1));
    return 0;
}
