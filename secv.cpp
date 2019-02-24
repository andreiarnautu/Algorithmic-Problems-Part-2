#include <cstdio>
#include <algorithm>
#define Dim 5003

using namespace std;

FILE *fin=freopen("secv.in","r",stdin);
FILE *fout=freopen("secv.out","w",stdout);

int V[Dim], Aux[Dim], Numbers[Dim], n, cnt, best = Dim, len;

int main()
{
    int i, j;

    scanf("%d", &n);
    for(i = 1 ; i <= n ; ++i)
    {
        scanf("%d", &V[i]);
        Aux[i] = V[i];
    }

    sort(Aux + 1 , Aux + n + 1);

    Aux[0] = -1;

    for(i = 1 ; i <= n ; ++i)
        if(Aux[i] != Aux[i - 1])
            Numbers[++cnt] = Aux[i];

    if(cnt == 1)
    {
        printf("1");
        return 0;
    }

    for(i = 1 ; i <= n ; ++i)
        if( V[i] == Numbers[1] )
        {
            len = 1;
            for(j = i + 1 ; j <= n ; ++j)
            {
                if( V[j] == Numbers[len + 1] )
                    ++len;
                if(len == cnt)
                {
                    if(j - i + 1 < best)
                        best = j - i + 1;
                    break;
                }
            }
        }
    if( best != Dim )
        printf("%d", best);

    else
        printf("-1");
    return 0;
}
