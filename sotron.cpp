#include <cstdio>
#include <algorithm>
#define Nmax 242
using namespace std;
FILE *fin = freopen( "sotron.in", "r", stdin );
FILE *fout= freopen( "sotron.out", "w", stdout);

int A[Nmax][Nmax], N, Max = -100000;

void Read()
{
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
        for(int j = 1 ; j <= N ; ++j )
            scanf("%d", &A[i][j]);

}

void Solve()
{

    for(int i = N  ; i >= 1 ; i-- )
        for(int j = 1 ; j <= N ; ++j )
        {
            if(( i + j ) % 2 == 0)
                A[i][j] += max( 0 , A[i][j - 1] );
            else
                A[i][j] += max( 0 , A[i + 1][j] );
            if( A[i][j] > Max )
                Max = A[i][j];
        }
    printf("%d", Max);
}

int main()
{
    Read();
    Solve();
    return 0;
}
