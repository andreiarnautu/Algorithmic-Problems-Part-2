#include <cstdio>
using namespace std;
FILE *fin=freopen("vot2.in","r",stdin);
FILE *fout=freopen("vot2.out","w",stdout);

char S[210];
int n, m, validCount, F[210];

int main()
{
    int i, j, vot, ok;
    scanf("%d %d ", &n, &m);
    for( i = 1; i <= m; ++i)
    {
        gets(S);
        vot = 0, ok = 1;
        for( j = 0; j < n; ++j)
            if( S[j] == '+' )
            {
                if( vot )
                {
                    ok = 0; break;
                }
                vot = j + 1;
            }
        if( ok )
        {
            ++validCount;
            ++F[vot];
        }
    }

    for(int i = 1; i <= n; ++i)
        if( F[i] * 20 >= validCount )
            printf("%d ", i);
    return 0;
}
