#include <cstdio>
#define DIM 1003
#define MOD 1000003
using namespace std;
FILE *fin=freopen("poveste.in","r",stdin);
FILE *fout=freopen("poveste.out","w",stdout);

int n, m;
char S[DIM];
int A[DIM][DIM];
int E[MOD + 3];
int M[DIM][DIM];
int del[DIM];


void Solve()
{
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= m; ++j)
            A[i][j] = M[i][j] = 0;
    }

    scanf("%d %d ", &n, &m);
    int i, j, best = 0, pow = 1, l, val;

    for(i = 1; i <= n; ++i)
    {
        gets(S);

        for(j = 0; j < m; ++j)
        {
            A[i][j + 1] = S[j] - 48;
            M[i][j + 1] = ( M[i - 1][j + 1] + A[i][j + 1] * pow ) % MOD;
        }

        pow = (pow * 2) % MOD;
    }

    for(i = 1; i < n; ++i)
        for(j = i + 1; j <= n; ++j)
        {
            for(l = 1; l <= m; ++l)
            {
                val = M[j][l] - M[i - 1][l];
                if( val < 0 )
                    val += MOD;

                if( !E[val] )
                {
                    E[val] = l;
                    del[l] = val;
                }

                else
                {
                    if( best < (j - i + 1) * (l - E[val] + 1) )
                        best = (j - i + 1) * (l - E[val] + 1);
                }
            }
            for(l = 1; l <= m; ++l)
                E[del[l]] = 0;
        }


    printf("%d\n", best);
}

int main()
{
    int t;
    for(scanf("%d", &t); t > 0; --t)
        Solve();
    return 0;
}
