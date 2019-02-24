#include <algorithm>
#include <cstdio>
using namespace std;
FILE *fin=freopen("secvente.in","r",stdin);
FILE *fout=freopen("secvente.out","w",stdout);

int d[3];

void Solve()
{
    int n, i, x, ans = 0, m;
    for(i = 0; i < 3; ++i)
        d[i] = 0;

    scanf("%d", &n);

    for(i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        ++d[x % 3];
    }

    ans += d[0];
    ans += 3 * (d[1] / 3) + 3 * (d[2] / 3);
    d[1] %= 3, d[2] %= 3;
    m = min(d[1], d[2]);
    ans += 2 * m;
    printf("%d\n", ans);
}

int main()
{
    for(int i = 0; i < 3; ++i)
        Solve();
    return 0;
}
