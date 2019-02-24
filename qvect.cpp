# include <cstdio>
# include <algorithm>
# define inf 1000000000
using namespace std;

int a[102][5002];
int nr[102];

int q1(int x, int y)
{
    int i = 1, j = 1, n = a[x][0], m = a[y][0], Min = 2*inf, z;
    while ( i <= n && j <= m )
    {
        if (a[x][i] > a[y][j]) z = a[x][i] - a[y][j];
                          else z = a[y][j] - a[x][i];
        if (z == 0) return 0;
        if (z < Min) Min = z;
        if (a[x][i] < a[y][j]) ++i;
                          else ++j;
    }
    return Min;
}

int q2(int x, int y, int p)
{
    int i, j, s, d, val, nr, k, ok, nr0, rez, sol;
    s = -inf, d = inf;
    while ( s <= d )
    {
        val = (s + d) >> 1 ;
        nr = 0; ok = 0;
        for (k = x; k<=y; ++k)
        {
            i = 1; j = a[k][0];
            nr0 = upper_bound(a[k] + 1, a[k] + j + 1, val) - a[k] - 1;
            if (a[k][nr0] == val)
            {
                sol = val; ok = 1;
            }
            nr += nr0;
        }
        if (nr >= p)
        {
             if (ok)
             {
                rez = sol;
                if (nr == p) return sol;
             }
             d = val - 1;
        }
        else s = val + 1;
    }
    return rez;
}

int main()
{
    int n, q, op, i, j, x, y, m;

    freopen("qvect.in", "r", stdin);
    freopen("qvect.out","w", stdout);

    scanf("%d%d", &n, &q);
    for (i=1; i<=n; ++i)
    {
        scanf("%d", &x);
        a[i][0] = x;
        nr[i] = nr[i-1] + x;
        for (j=1; j<=x; ++j)
            scanf("%d", &a[i][j]);
    }

    while ( q-- )
    {
        scanf("%d%d%d", &op, &x, &y);
        switch (op)
        {
            case 1: {
                        printf("%d\n", q1(x, y));
                        break;
                    };
            case 2: {
                        m = (nr[y] - nr[x-1]) >> 1;
                        printf("%d\n", q2(x, y, m));
                        break;
                    };
        }
    }
    return 0;
}
