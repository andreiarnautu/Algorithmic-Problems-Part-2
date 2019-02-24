// It's not the load that breaks you down, it's the way you carry it.
#include <cstdio>
#include <algorithm>
#define DIM 55
using namespace std;
FILE *fin=freopen("purice2.in","r",stdin);
FILE *fout=freopen("purice2.out","w",stdout);

int n, V[DIM], F[DIM * DIM];

inline int ABS(int x)
{
    return ((x > 0) ? x : -x);
}

void Solve()
{
    int i, j;

    scanf("%d", &n);
    for(i = 1; i <= n; ++i)
        scanf("%d", &V[i]);
    sort(V + 1, V + n + 1);

    for(i = 2; i <= n; ++i)
        if( V[i] - V[i - 1] == 1 )
        {
            printf("1\n");
            return;
        }


    printf("0\n");
}

int main()
{
    int t;
    for(scanf("%d", &t); t > 0; --t)
        Solve();
    return 0;
}
