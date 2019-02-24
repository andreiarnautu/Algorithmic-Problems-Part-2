#include <cstdio>
#include <bitset>
#define MOD 9973
using namespace std;
FILE *fin=freopen("ssnd.in","r",stdin);
FILE *fout=freopen("ssnd.out","w",stdout);
bitset <1000000> viz;
int Primes[300000], nr;
int Div[20], cnt;
int P[20];

void Ciur()
{
    long long int i, j;
    Primes[++nr] = 2;
    for(i = 3; i <= 1000000; i += 2)
        if( !viz[i] )
        {
            Primes[++nr] = i;
            for(j = i * i; j <= 1000000; j += 2 * i)
                viz[j] = 1;
        }

}

inline long long int POW(long long int x, long long int y)
{
    long long int ret = 1;
    for(long long int i = 1; i <= y; ++i)
        ret *= x;
    return ret;
}

inline void Query()
{
    long long int k;
    scanf("%lld", &k);
    if( k == 1 )
    {
        printf("1 1\n");
        return;
    }

    cnt = 0;
    int i;
    for(i = 1; i <= nr && k > 1 && Primes[i] * Primes[i] <= k; ++i)
        if( k % Primes[i] == 0 )
        {
            Div[++cnt] = Primes[i];
            P[cnt] = 0;
            while( k % Primes[i] == 0 )
            {
                ++P[cnt];
                k /= Primes[i];
            }
        }
    if(k > 1)
    {
        Div[++cnt] = k;
        P[cnt] = 1;
    }

    long long int sol1 = 1, sol2 = 1;
    for(i = 1; i <= cnt; ++i)
    {
        sol1 *= (P[i] + 1);
        sol2 *= (POW(Div[i], P[i] + 1) - 1) / (Div[i] - 1); sol2 %= MOD;
    }
    printf("%lld %lld\n", sol1, sol2);
}

int main()
{
    Ciur();
    int k;
    for(scanf("%d", &k); k > 0; --k)
        Query();
    return 0;
}
