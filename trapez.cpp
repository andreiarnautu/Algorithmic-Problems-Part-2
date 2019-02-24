#include <cstdio>
#include <algorithm>
#define MaxN 1003
#define magic_number 6969
using namespace std;

FILE *fin=freopen("trapez.in","r",stdin);
FILE *fout=freopen("trapez.out","w",stdout);

double V[MaxN * MaxN];
int pos;
int X[MaxN], Y[MaxN];
int n;

void Read()
{
    scanf("%d", &n);

    for(int i = 1; i <= n ; ++i)
        scanf("%d %d", &X[i], &Y[i]);

    for(int i = 1; i < n ; ++i)
        for(int j = i + 1; j <= n ; ++j)
        {
            if( Y[i] == Y[j] )
                V[++pos] = magic_number;
            else
                V[++pos] =(long double) (X[i] - X[j]) / (Y[i] - Y[j]);
        }

    sort(V + 1, V + pos + 1);
}

void Solve()
{
    int i, cnt = 1, ret = 0;

    for(i = 2; i <= pos; ++i)
    {
        if( V[i] != V[i - 1] )
            ret += cnt * (cnt - 1) / 2, cnt = 1;
        else
            ++cnt;
    }

    if( cnt )
        ret += cnt * (cnt - 1) / 2;

    printf("%d", ret);
}

int main()
{
    Read();
    Solve();
    return 0;
}
