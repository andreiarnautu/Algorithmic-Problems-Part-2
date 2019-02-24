/**
  *  Worg
  */
#include <cstdio>

#define DIM 1000100

using namespace std;
FILE *fin=freopen("reguli.in","r",stdin);
FILE *fout=freopen("reguli.out","w",stdout);

long long int V[DIM];
int pi[DIM];
int n;

void Set()
{
    int i;
    long long int current, last = 0;
    scanf("%d", &n);

    for(i = 1; i <= n; ++i)
    {
        scanf("%lld", &current);
        V[i - 1] = current - last;
        last = current;
    }
}

void Prefix()           // construct the "pi" array
{
    int i = 2, k = 0;
    for(; i < n; ++i)
    {
        while( k && V[k + 1] != V[i] )
            k = pi[k];
        if( V[k + 1] == V[i] )
            ++k;
        pi[i] = k;
    }
}

int main()
{
    Set();
    Prefix();

    int i, ans = n - 1 - pi[n - 1];
    printf("%d\n", ans);
    for(i = 1; i <= ans; ++i)
        printf("%lld\n", V[i]);
    return 0;
}
