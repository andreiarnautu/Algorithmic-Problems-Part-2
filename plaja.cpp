#include <cstdio>
using namespace std;
FILE *fin=freopen("plaja.in","r",stdin);
FILE *fout=freopen("plaja.out","w",stdout);
int a, b, U, N, M, k;
struct {int v, w;} u[101];
struct {int X1, Y1, X2, Y2;} V[100001];
void Read()
{
    int x, y, x1, y1;
    scanf("%d%d%d",&a,&b,&U);
    for(int i=1; i<=U ; ++i)
    {
        scanf("%d%d",&x,&y);
        u[i].v = x;
        u[i].w = y;
      //  A[x][y] = -1;
    }
    scanf("%d",&N);
    bool ok;
    for(int i=1 ; i<=N ; ++i)
    {
        scanf("%d%d%d%d",&x,&y,&x1,&y1);
        ok = 1;
        for(int j=1 ; j<=U ; ++j)
            if( x <= u[j].v && u[j].v <= x1 && y <= u[j].w && u[j].w <= y1 )
            {
                ok = 0;
                break;
            }
        if( ok )
        {
            ++k;
            V[k].X1 = x;
            V[k].Y1 = y;
            V[k].X2 = x1;
            V[k].Y2 = y1;
        }
    }
    printf("%d\n",k);
    for(int i=1 ; i<=k ; ++i)
        printf("%d %d %d %d\n",V[i].X1,V[i].Y1,V[i].X2,V[i].Y2);
}
void Solve()
{
    int x, y, x1, y1, nr=0, a, b, c, d;
    bool ok;
    scanf("%d",&M);
    for(int i=1; i<=M ; ++i)
    {
        scanf("%d%d%d%d",&x,&y,&x1,&y1);
        ok = 1;
        for(int j=1 ; j<=U ; ++j)
            if( ( x <= u[j].v && u[j].v <= x1) && ( y <= u[j].w && u[j].w <= y1 ) )
            {
                ok = 0;
                break;
            }
        if( !ok )
            for(int j=1 ; j<=k ; ++j)
            {
                a = V[j].X1;
                b = V[j].Y1;
                c = V[j].X2;
                d = V[j].Y2;
                if( ( x <= a  && a <= x1 && y<=b && b<=y1) || ( x <= c && c<= x1 && y <= b && b <= y1)  || ( x <= a && a <= x1 && y <=d && d <= y1) || ( x <= c && c<= x1 && y <= d && d <= y1))
                {
                    ok = 0;
                    break;
                }
            }
        if( ok )
            ++nr;
    }
    printf("%d\n",nr);
}
int main()
{
    Read();
    Solve();
    return 0;
}
