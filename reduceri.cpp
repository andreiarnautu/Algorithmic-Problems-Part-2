#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin=freopen("reduceri.in","r",stdin);
FILE *fout=freopen("reduceri.out","w",stdout);
int N, V[101], A[101][101];

void Read()
{
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
        scanf("%d", &V[i]);
}

void Solve()
{
    for(int i = 1 ; i <= N ; ++i )
        A[i][i] = V[i];
    for(int i = 1 ; i < N  ; ++i )
    {
        for(int j = 1 ; j + i <= N ; ++j )
        {
            A[j][j + i] = (i + 1) * abs( V[j] - V[j + i] );
            for(int l = 0; l < i ; ++l )
                if( A[j][j + i] < A[j][j + l] + A[j + l + 1][j + i] )
                    A[j][j + i] = A[j][j + l] + A[j + l + 1][j + i];
        }
    }
    printf("%d", A[1][N]);
}

int main()
{
    Read();
    Solve();
    return 0;
}
