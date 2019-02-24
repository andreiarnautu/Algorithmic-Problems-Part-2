// RMQ - Range minimum query
#include <cstdio>
#define Dim 100002
#define Min(x,y) ((x < y) ? x : y)
using namespace std;
FILE *fin=freopen("rmq.in","r",stdin);
FILE *fout=freopen("rmq.out","w",stdout);

int  N, M, A[20][Dim], lg[Dim], x, y, Diff;

int main()
{
    scanf("%d%d", &N, &M);
    for(int i=1 ; i <= N ; ++i )
        scanf("%d", &A[0][i]);

    lg[1] = 0;
    for(int i=2; i <= N ; ++i)
        lg[i] = lg[i/2] + 1;

    for(int i=1 ; i <= lg[N] ; ++i)
        for(int j=1 ; j <= N - ( 1 << (i-1) ) ; ++j)
            A[i][j] = Min( A[i - 1][j] , A[i - 1][ j + (1 << (i - 1))] );

    for(int i=1 ; i <= M ; ++i)
    {
        scanf("%d%d", &x, &y);
        Diff = lg[y - x + 1];
        printf("%d\n", Min( A[Diff][x] , A[Diff][y - (1 << Diff) + 1]));
    }

    return 0;
}
