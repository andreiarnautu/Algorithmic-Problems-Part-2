/**
  *  Worg
  */
#include <cstdio>
using namespace std;

FILE *f = freopen("xnumere.in", "r", stdin);
FILE *g = freopen("xnumere.out", "w", stdout);

const long long MOD = 666013;

long long k, x, n;
long long semn;

long long pow(long long base, long long exp, long long MOD)
{
    long long a = base, ans = 1;

    for (long long i=1; i <= exp; i<<=1)
    {
        if (exp & i)
        {
            ans *= a;
            ans %= MOD;
        }

        a = (a * a) % MOD;
    }

    return ans;
}


void read()
{
    scanf("%lld %lld %lld", &k, &x, &n);

    if ((x - 1)% 2 == 0)
        semn = -1;
    else
        semn = 1;

    long long comb = 1, s = 0;

    for (long long j=1; j<=x; j++)
    {
        long long put2 = pow(j, n, MOD);

        comb = (1LL * comb * (x - j + 1)) % MOD;
        comb = (1LL * comb * pow(j, MOD-2, MOD)) % MOD;

        semn *= -1;

        long long now = (comb * put2) % MOD;

        s += semn * now;

        if (s < 0)
            s += MOD;
        else
        if (s >= MOD)
            s -= MOD;

    }

    for (long long j=2; j<=x; j++)
    {
        s = (1LL * s * pow(j, MOD-2, MOD)) % MOD;
    }

    for (long long j = k - x + 1; j<=k; j++) /// aranjamente de k luate cate x
    {
        s *= (j % MOD);
        s %= MOD;
    }

    printf("%d\n", s);
}

int main()
{
    read();
    return 0;
}
