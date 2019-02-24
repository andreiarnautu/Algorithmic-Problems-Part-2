// How about a coding trick?
#include <cstdio>
#include <vector>
#define INF 2000000000
#define DIM 55
#define PII pair<int,int>
#define fi first
#define se second
using namespace std;
FILE *fin=freopen("rfinv.in","r",stdin);
FILE *fout=freopen("rfinv.out","w",stdout);

int A[DIM][DIM], Sol[DIM][DIM];
vector < PII > V;

void Solve()
{
    int i, j, n, m, l;
    scanf("%d %d", &n, &m);
    for(i = 1; i <= n; ++i)
        for(j = 1; j <= n; ++j)
            A[i][j] = 0;

    V.clear();
    for(i = 1; i <= m; ++i)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        V.push_back( make_pair(x, y) );
    }

    for(i = 1; i <= n; ++i)
        for(j = 1; j <= n; ++j)
            scanf("%d", &Sol[i][j]);

    for(i = 0; i < V.size(); ++i)
    {
        PII aux = V[i];
        A[aux.se][aux.fi] = A[aux.fi][aux.se] = Sol[aux.fi][aux.se];
    }

    for(l = 1; l <= n; ++l)
        for(i = 1; i <= n; ++i)
            for(j = 1; j <= n; ++j)
                if( i != j )
                {
                    if( A[i][l] && A[l][j] && (!A[i][j] || A[i][j] > A[i][l] + A[l][j]))
                        A[i][j] = A[i][l] + A[l][j];
                }

    for(i = 1; i <= n; ++i)
        for(j = 1; j <= n; ++j)
            if( A[i][j] != Sol[i][j] )
            {
                printf("NU\n");
                return;
            }
    printf("DA\n");
}

int main()
{
    int t;
    for(scanf("%d", &t); t; --t)
        Solve();
    return 0;
}
