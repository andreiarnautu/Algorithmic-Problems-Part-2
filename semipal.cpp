#include <cstdio>
using namespace std;
FILE *fin=freopen("semipal.in","r",stdin);
FILE *fout=freopen("semipal.out","w",stdout);

long long int V[100], n, k;

void Solve()
{
    scanf("%lld %lld ", &n, &k);
    --k;
    for(int i = 2; i <= n ; ++i)
    {
        if( (1LL << (i - 2)) & k )
            V[i] = 1;
        else
            V[i] = 0;
    }
    V[1] = V[n];
    for(int i = n; i > 0; --i)
    {
        if( V[i] )
            printf("b");
        else
            printf("a");
    }
    printf("\n");
}

int main()
{
    int t;
    for( scanf("%d", &t); t > 0 ; --t )
        Solve();
    return 0;
}
