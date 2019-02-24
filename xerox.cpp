#include <cstdio>
using namespace std;
FILE *fin=freopen("xerox.in","r",stdin);
FILE *fout=freopen("xerox.out","w",stdout);

void Solve()
{
    int xorsum = 0, n, m, dx, dy, i, j;
    scanf("%d %d %d", &n, &dx, &dy);
    for(i = 1; i <= n; ++i)
    {
        scanf("%d", &m); xorsum ^= m;
        for(j = 1; j <= m; ++j)
            scanf("%d%d", &dx, &dy);
    }
    if( xorsum )
        printf("1\n");
    else
        printf("0\n");
}

int main()
{
    int teste;
    for( scanf("%d", &teste); teste > 0; --teste )
        Solve();
    return 0;
}
