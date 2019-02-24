/*
    How about a coding trick?
*/
#include <cmath>
#include <cstdio>
#include <vector>
#define MOD 6007
using namespace std;
FILE *fin=freopen("ubercool.in","r",stdin);
FILE *fout=freopen("ubercool.out","w",stdout);

int cnt;
bool prim[1000100];
int list[100100], k;
vector <long long int> Hash[MOD];


inline void Add(long long int val)
{
    Hash[val % MOD].push_back(val);
}

void Gen()
{
    long long int i, j, x, MAX = 1000000000000000000;
    list[++k] = 2;

    for(i = 3; i <= 1000000; i += 2)
        if( !prim[i] )
        {
            list[++k] = i;
            for(j = i * i; j <= 1000000; j += 2 * i)
                prim[j] = 1;
        }

    for(i = 1; i <= k ; ++i)
    {
        x = 1LL * list[i] * list[i] * list[i];
        Add(x);
        while( MAX / x >  list[i] )
        {
            x *= 1LL * list[i];
            Add(x);
        }
    }
}

void Solve()
{
    long long int x, rad;
    bool ok = 0;
    scanf("%lld", &x);
    for(int i = 0; i < Hash[x % MOD].size(); ++i)
        if( x == Hash[x % MOD][i] )
            ok = 1;
    if( ok )
    {
        printf("DA\n");
        return;
    }
    rad = sqrt((long double)x);
    if( rad * rad != x || rad < 2 )
    {
        printf("NU\n");
        return;
    }

    for(int i = 1; i <= k && list[i] * list[i] <= rad; ++i)
        if( rad % list[i] == 0 )
        {
            printf("NU\n");
            return;
        }
    printf("DA\n");

}

int main()
{
    Gen();
    int n;
    /*long long int x, rad;
    x = 1000000000000000000;
    rad = sqrt((long double) x);
    printf("%lld", rad);*/
    for(scanf("%d", &n); n; --n)
        Solve();
}
