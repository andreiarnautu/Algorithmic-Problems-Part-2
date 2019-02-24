#include <cstdio>
using namespace std;

FILE *fin=freopen("sah3.in","r",stdin);
FILE *fout=freopen("sah3.out","w",stdout);

int m, n;
int A[1003][1003], cnt;
short Col[1003][1003], Lin[1003][1003], Best[1003][1003];
bool B[1003][1003];

void Read()
{
    int i, j;
    scanf("%d%d", &n, &m);

    for(i = 1; i <= n ; ++i)
        for(j = 1; j <= m ; ++j)
            scanf("%d", &A[i][j]);
}

int min(short a, short b)
{
    if(a < b)
        return a;
    return b;
}

void Solve()
{
    int i, j, val;

    for(i = 2 ; i <= n ; ++i)
        for(j = 2 ; j <= m ; ++j)
        {
            if( A[i][j] == A[i - 1][j - 1] && A[i - 1][j] == A[i][j - 1] && A[i][j] != A[i - 1][j] )
                B[i][j] = 1;
            else
                B[i][j] = 0;
        }

    for(i = 1 ; i <= n ; ++i)
        for(j = 1; j <= m ; ++j)
        if(B[i][j])
        {
            Col[i][j] = Col[i - 1][j] + 1;
            Lin[i][j] = Lin[i][j - 1] + 1;
        }
    cnt = m * n;

    for(i = 1; i <= n ; ++i)
        for(j = 1; j <= m ; ++j)
            if(B[i][j])
                {
                    val = min( Best[i - 1][j - 1] + 1, min(Lin[i][j], Col[i][j]) );
                    Best[i][j] = val;
                    cnt += val;
                }

    printf("%d", cnt);
}

int main()
{
    Read();
    Solve();
    return 0;
}
