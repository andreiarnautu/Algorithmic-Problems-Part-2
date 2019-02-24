#include <cstdio>
#define DIM 20
using namespace std;
FILE *fin=freopen("zebughil.in","r",stdin);
FILE *fout=freopen("zebughil.out","w",stdout);

struct duo  {
                int nr, rest;
            };

int n, G;
int E[DIM];
duo DP[1 << DIM], aux;

void Read()
{
    scanf("%d%d", &n, &G);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &E[i]);
}

inline duo MIN( duo a, duo b )
{
    if( a.nr < b.nr )
        return a;
    if( a.nr > b.nr )
        return b;
    if( a.rest < b.rest )
        return a;
    return b;
}

void Solve()
{
    DP[0].nr = DP[0].rest = 0;

    int i, val = 1 << n, j;
    for(i = 1; i < val; ++i)
    {
        DP[i].nr = n + 1, DP[i].rest = 0;
        for(j = 1; j <= n; ++j)
            if( i & (1 << (j - 1)) )
            {
                aux = DP[i - (1 << (j - 1))];
                if( E[j] + aux.rest <= G )
                    aux.rest += E[j];
                else
                    ++aux.nr, aux.rest = E[j];
                DP[i] = MIN( DP[i], aux );
            }
    }
    printf("%d\n", 1 + DP[val - 1].nr);
}

int main()
{
    int teste = 3;
    for(; teste; --teste)
    {
        Read();
        Solve();
    }
}
