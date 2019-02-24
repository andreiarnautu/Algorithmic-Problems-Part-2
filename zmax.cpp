#include <cstdio>
#include <algorithm>
#define DIM 505
#define INF 2000000000
using namespace std;
FILE *fin=freopen("zmax.in","r",stdin);
FILE *fout=freopen("zmax.out","w",stdout);

int DP[DIM][DIM][5], A[DIM][DIM];
int m, n;

void Read()
{
    scanf("%d %d ", &m, &n);
    int i, j;

    for(i = 1; i <= m; ++i)
        for(j = 1; j <= n; ++j)
            scanf("%d ", &A[i][j]);
}

void Solve()
{
    int i, j, best = -INF + 1;

    for(i = 1; i <= m; ++i)
        for(j = 1; j <= n; ++j)
        {
            DP[i][j][0] = max( DP[i][j - 1][0], 0 ) + A[i][j];

            if( j > 1 )
                DP[i][j][1] = DP[i][j - 1][0] + A[i][j];
            else
                DP[i][j][1] = -INF;

            if( i > 1 && j < n )
                DP[i][j][2] = max( DP[i - 1][j + 1][1], DP[i - 1][j + 1][2] ) + A[i][j];
            else
                DP[i][j][2] = -INF;

            if(i >= 3 && j <= n - 2)
                DP[i][j][3] = DP[i - 1][j + 1][2] + A[i][j];
            else
                DP[i][j][3] = -INF;

            if( i >= 3 && j >= 2 )
            {
                DP[i][j][4] = max( DP[i][j - 1][3], DP[i][j - 1][4] ) + A[i][j];
                if( DP[i][j][4] > best )
                    best = DP[i][j][4];
            }
            else
                DP[i][j][4] = -INF;

        }

    printf("%d", best);
}

int main()
{
    Read();
    Solve();
    return 0;
}
