// RMQ - matrice
#include <cstdio>
#define Nmax 501
using namespace std;
FILE *fin=freopen("plantatie.in","r",stdin);
FILE *fout=freopen("plantatie.out","w",stdout);
int A[10][Nmax][Nmax];
int log[Nmax], N, M;

void Read()
{
    scanf("%d%d", &N, &M);
    for(int i = 1 ; i <= N ; ++i )
        for(int j = 1 ; j <= N ; ++j )
            scanf("%d", &A[0][i][j] );
}

void Process()
{
    log[1] = 0;
    for(int i = 2 ; i <= 500 ; ++i )
        log[i] = log[i / 2] + 1;
}

int Max(int a, int b, int c, int d)
{
    if( a >= b && a >= c && a >= d )
        return a;
    if( b >= a && b >= c && b >= d )
        return b;
    if( c >= a && c >= b && c >= d )
        return c;
    return d;
}

void Build()
{
    for(int k = 1 ; k <= 9 ; ++k )
    {
        for(int i = 1 ; i + (1 << k) - 1 <= N ; ++i )
            for(int j = 1 ; j + (1 << k) - 1 <= N ; ++j )
                A[k][i][j] = Max( A[k - 1][i][j], A[k - 1][i + (1 << k - 1)][j], A[k - 1][i][j + (1 << k - 1)], A[k - 1][i + (1 << k - 1 )][j + (1 << k - 1)]);
    }
}

void Solve()
{
    int x, y, k, p;
    for(int i = 1 ; i <= M ; ++i )
    {
        scanf("%d%d%d", &x, &y, &k);
        p = log[k];
        printf("%d\n", Max( A[p][x][y] , A[p][x + k - (1 << p )][y] , A[p][x][y + k - (1 << p)], A[p][x + k - (1 << p)][y + k - (1 << p)]));
    }
}

int main()
{
    Read();
    Process();
    Build();
    Solve();
    return 0;
}
