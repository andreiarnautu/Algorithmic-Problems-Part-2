#include <cstdio>
using namespace std;
FILE *fin=freopen("vapoare.in","r",stdin);
FILE *fout=freopen("vapoare.out","w",stdout);

long long int gcd(long long int a, long long int b)
{
    long long int r;

    while(b)
    {
        r = a % b;
        a = b;
        b = r;
    }

    return a;
}

int main()
{
    long long int p, cmmdc, d1, d2, x, y, z1, z2;
    scanf("%lld%lld%lld%lld", &x, &y, &z1, &z2);

    d1 = 14 * x + z1, d2 = 14 * y + z2;
    p = d1 * d2;
    cmmdc = gcd(d1, d2);
    printf("%lld", p / cmmdc);

    return 0;

}
