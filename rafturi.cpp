#include <cstdio>
using namespace std;
FILE *fin=freopen("rafturi.in","r",stdin);
FILE *fout=freopen("rafturi.out","w",stdout);
int N, C, R, Col[10001], E[10001];
void Read()
{
    int x, y;
    scanf("%d%d",&C,&N);
    for(int i=1; i<=N ; ++i)
    {
        scanf("%d%d",&x,&y);
        if( Col[x] < y )
            Col[x] = y;
    }
}
int Max(int a, int b)
{
    if(a >= b)
        return a;
    return b;
}
int Maxx(int a, int b, int c)
{
    if( a>=b && a>=c)
        return a;
    if(b>=a && b>=c)
        return b;
    return c;
}
int Min(int a, int b, int c)
{
    if( a <= b && a <= c )
        return a;
    if( b <= a && b <= c )
        return b;
    return c;
}
void Solve()
{
    for(int i=1; i<=C ; ++i)
        E[i] = Min( E[i-1] + Col[i] , E[i-2] + Max(Col[i], Col[i-1]), E[i-3] + Maxx( Col[i-2],Col[i-1], Col[i]) );
    printf("%d",E[C]);
}
int main()
{
    Read();
    Solve();
    return 0;
}
