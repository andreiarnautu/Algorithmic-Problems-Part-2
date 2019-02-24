#include <cstdio>
#include <algorithm>
#define MOD 1000003
#define DIM 100010
using namespace std;
FILE *fin=freopen("subsir100.in","r",stdin);
FILE *fout=freopen("subsir100.out","w",stdout);

int DP[DIM], V[DIM];
int n;

void Read()
{
    int i;
    scanf("%d", &n);
    for(i = 1; i <= n; ++i)
        scanf("%d", &V[i]);
    sort(V + 1, V + n + 1);
}

inline int F(int x)
{
    if( x >= MOD )
        x -= MOD;
    return x;
}

void Solve()
{
    int i, j = n + 1;

    for(i = n; i > 0; --i)
    {
        if( V[i + 1] != V[i] )
            j = i + 1;
        DP[i] = F( DP[i + 1] + DP[j] + 1 );
    }
    printf("%d", DP[1]);
}

int main()
{
    Read();
    Solve();
    return 0;
}
