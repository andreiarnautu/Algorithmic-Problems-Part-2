#include <cstdio>

using namespace std;

#define maxn 1000010
#define sigma 30

int n, k;
char c, s[maxn];
double a[maxn], b[maxn];
double pc[sigma], pi[sigma], pb[sigma];

int main()
{
    freopen("sms.in", "r", stdin);
    freopen("sms.out", "w", stdout);

    scanf("%d%d\n", &n, &k);
    scanf("%s", s);

    for(int i=0; i<k; ++i)
        scanf("%lf%lf%lf", &pc[i], &pi[i], &pb[i]);

    for(int i=1; i<=n; ++i)
    {
        c=s[i-1]-'a';
        b[i+1] = (b[i] - pi[c] * (2 + b[i]) - pb[c] * (1 + b[i-1]) - pc[c]) / pc[c];
    }

    printf("%.8f\n", -b[n+1]);

    return 0;
}
