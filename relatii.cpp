#include <cstdio>
using namespace std;
FILE *fin=freopen("relatii.in","r",stdin);
FILE *fout=freopen("relatii.out","w",stdout);

int n, m;
char S[4], c;
int low[15][100];
int ok, g;
int F[15], V[15];

void Read()
{
    scanf("%d %d ", &n, &m);
    int i, j;

    for(i = 1; i <= m; ++i)
    {
        gets(S);
        if( S[1] == '>' )
        {
            c = S[2];
            S[2] = S[0];
            S[0] = c;
        }

        ++low[S[2] - 'a'][0];
        low [S[2] - 'a'] [ low[S[2] - 'a'][0] ] = S[0] - 'a';
    }
}

void Gen(int nr)
{
    if( ok )
        return;

    if( nr == n + 1 )
    {
        ok = 1;
        for(int i = 1; i <= n; ++i)
            printf("%c", V[i] + 'a');
        return;
    }

    for(int i = 0; i < n; ++i)
        if( !F[i] )
        {
            g = 1;
            for(int j = 1; j <= low[i][0]; ++j)
                if( !F[low[i][j]] )
                {
                    g = 0;
                    break;
                }
            if( g )
            {
                V[nr] = i;
                F[i] = 1;
                Gen(nr + 1);
                F[i] = 0;
            }
        }
}

int main()
{
    Read();
    Gen(1);

    return 0;
}
