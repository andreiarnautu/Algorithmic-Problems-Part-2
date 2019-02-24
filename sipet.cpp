/*
    How about a coding trick?
*/
#include <cstdio>
#include <utility>
#define DIM 10000010
#define PII pair<int,int>
#define fi first
#define se second
using namespace std;
FILE *fin=freopen("sipet.in","r",stdin);
FILE *fout=freopen("sipet.out","w",stdout);

PII v[DIM]; // fi -> nr, se -> last elem
int p[3], cnt[3];
int N;

inline int findPrime(int val)
{
    int i, j;
    bool ok;

    for(i = val; ;++i)
    {
        ok = 1;
        if(i % 2 == 0 && i > 2)
            continue;

        for(j = 3; j * j <= i; j += 2)
            if( i % j == 0 )
            {
                ok = 0; break;
            }
        if( ok )
            return i;
    }
}

void Solve()
{
    int n, a, b, c, i, j;
    scanf("%d%d", &n, &a);
    b = findPrime(a + 1);
    c = findPrime(b + 1);
    //printf("%d %d %d ", a, b, c);

    v[a].fi = 1, v[a].se = 0;
    v[b].fi = 1, v[b].se = 1;
    v[c].fi = 1, v[c].se = 2;

    p[0] = a, p[1] = b, p[2] = c;
    for(i = 0; i < 3; ++i)
    {
        for(j = 0; j + p[i] <= n; ++j)
            if( v[j].fi && v[ j + p[i] ].fi <= v[j].fi + 1 )
                v[ j + p[i] ].fi = v[j].fi + 1, v[ j + p[i] ].se = i;
    }
    for(i = n; i > 0; --i)
        if( v[i].fi )
        {
            j = i;
            cnt[0] = cnt[1] = cnt[2] = 0;
            while( v[i].fi )
            {
                ++cnt[ v[i].se ];
                i -= p[ v[i].se ];
            }
            printf( "%d %d %d %d %d\n", cnt[0] + cnt[1] + cnt[2], cnt[0], cnt[1], cnt[2], n - j );
            N = n;
            return;
        }

}

void Clean()
{
    for(int i = 0; i < 3; ++i)
        p[i] = cnt[i] = 0;

    PII aux;
    aux.fi = 0, aux.se = 0;

    for(int i = 0; i <= N + 10; ++i)
        v[i] = aux;
}

int main()
{
    int teste;
    for(scanf("%d", &teste); teste; --teste)
    {
        Solve();
        Clean();
    }
    return 0;
}
