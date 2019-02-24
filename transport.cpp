#include <cstdio>
#define MaxN 1 << 14
using namespace std;

FILE *fin=freopen("transport.in","r",stdin);
FILE *fout=freopen("transport.out","w",stdout);

int n, MaxG = MaxN * MaxN, k;
int v[MaxN];


void Read()
{
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n ; ++i)
        scanf("%d", &v[i]);
}

inline int Check(int x)
{
    int cnt = 0, s = 0;

    for(int i = 1; i <= n; ++i)
    {
        if( v[i] > x )
            return 0;
        if( v[i] + s <= x )
            s += v[i];
        else
        {
            ++cnt;
            --i;
            s = 0;
        }
    }
    if( cnt < k )
        return 1;
    return 0;
}

void Solve()
{
    int left = 0, right = MaxG, m, rez = MaxN * MaxN;

    while( left <= right )
    {
        m = (left + right) >> 1;
        if( Check(m) )
        {
            if( rez > m )
                rez = m;
            right = m - 1;
        }

        else
            left = m + 1;
    }

    printf("%d", rez);
}

int main()
{
    Read();
    Solve();
}
