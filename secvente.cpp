#include <cstdio>
using namespace std;
FILE *fin=freopen("secvente.in","r",stdin);
FILE *fout=freopen("secvente.out","w",stdout);
int N, M;
int V[100001], Nr[100001], F[100001], S[100001], q;

void Solve()
{
    int last = 0, k = 1;
    for(int i = 1 ; i <= q ; ++i )
    {
        k = S[i];
        for(int j = S[i - 1] + 1 ; j <= S[i] ; ++j )
        {

            if( ! Nr[j] )
            {
                while( F[k] )
                    k--;
                Nr[j] = k;

                --k;
            }
        }
    }
    for(int i = 1 ; i <= N ; ++i )
        printf("%d ",Nr[i]);
}

void Read()
{
    scanf("%d%d", &N, &M);
    int x, y;
    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%d", &x);
        if( x == 1 )
            S[++q] = i;
        V[i] = V[i - 1] + x;
    }
    for(int i = 1 ; i <= M ; ++i )
    {
        scanf("%d%d", &x, &y);
        F[y] = 1;
        Nr[x] = y;
        if( x > y )
        {
            if( V[x - 1] - V[y - 1] > 0 )
            {
                printf("IMPOSIBIL");
                return;
            }
        }
        else if ( x < y )
        {
            if( V[y - 1] - V[x - 1] > 0 )
            {
                printf("IMPOSIBIL");
                return;
            }
        }

    }
    Solve();
}

int main()
{
    Read();
}
