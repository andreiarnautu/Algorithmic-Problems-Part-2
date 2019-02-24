#include <cstdio>
#define MaxN 153
#define Inf -2000000000
using namespace std;
FILE *fin=freopen("rland.in","r",stdin);
FILE *fout=freopen("rland.out","w",stdout);

int n, p, q, A[MaxN][MaxN], Sum[MaxN][MaxN], SCol[MaxN][MaxN];

void Read()
{
    scanf("%d %d %d", &n, &p, &q);
    for(int i = 1; i <= n ; ++i)
        for(int j = 1; j <= n ; ++j)
            scanf("%d", &A[i][j]);
}

void Compute()
{
    for(int i = 1; i <= n ; ++i)
        for(int j = 1; j <= n ; ++j)
        {
            Sum[i][j] = Sum[i - 1][j] + Sum[i][j - 1] - Sum[i - 1][j - 1] + A[i][j];
            SCol[i][j] = SCol[i - 1][j] + A[i][j];
        }
}

void Solve_first()
{
    int i, j, best = Inf, val;

    for(i = p; i <= n ; ++i)
        for(j = q; j <= n ; ++j)
        {
            val = Sum[i][j] - Sum[i - p][j] - Sum[i][j - q] + Sum[i - p][j - q];
            if( val > best )
                best = val;
        }
    printf("%d\n", best);

}

void Solve_second()
{
    int i, j, l, best = Inf, val;

    for(i = 0; i < n ; ++i)
        for(l = i + 1; l <= n && l - i <= p ; ++l)
        {
            val = Sum[l][q] - Sum[i][q];
            if( val > best )
                best = val;
            for(j = q + 1; j <= n ; ++j)
            {
                val -= (SCol[l][j - q] - SCol[i][j - q]);
                val += (SCol[l][j] - SCol[i][j]);
                if( val > best )
                    best = val;
            }
        }
    printf("%d",best);
}

int main()
{
    Read();
    Compute();
    Solve_first();
    Solve_second();
    return 0;
}
