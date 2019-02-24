#include <cstdio>
using namespace std;
FILE *fin=freopen("uscat.in","r",stdin);
FILE *fout=freopen("uscat.out","w",stdout);
long long N, V[100002], X;
void Read()
{
    scanf("%lld",&N);
    for(long i=1; i<=N ; ++i)
        scanf("%lld",&V[i]);
    scanf("%lld",&X);
}
void Solve()
{
    long long m, st = 0, dr = 0, t;
    for(long i=1; i<=N ; ++i)
        if( dr < V[i] )
            dr = V[i];
    if( X == 1 )
    {
        printf("%lld",dr);
        return;
    }
    while( st + 1 < dr )
    {
        m = ( st + dr ) / 2;
        t = 0;
        for(long i=1; i<=N ; ++i)
            if( V[i] > m )
                t += ( V[i] - m + X - 2) / ( X - 1 );
        if( t <= m )
            dr = m;
        else
            st = m;
    }
    printf("%lld",dr);
}
int main()
{
    Read();
    Solve();
    return 0;
}
