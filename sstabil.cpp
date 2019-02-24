#include <cstdio>
#define MaxN 1000013

using namespace std;

FILE *fin=freopen("sstabil.in","r",stdin);
FILE *fout=freopen("sstabil.out","w",stdout);

int v[MaxN], v2[MaxN];
int n;


int main()
{
    int i, pos = 0, r, aux, sum, term;

    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++i )
        scanf("%d", &v[i]);

    v[0] = v[n + 1] = v2[0] = 9;

    r = n;

    while( r > 0 )
    {
        aux = r, sum = 0;

        do
        {
            sum += v[aux];
            --aux;
        }while( sum < 10 );

        aux = r, term =  v[r];

        while( term + v2[pos] < 10 || sum - term > 9 )
        {
            --aux;
            term += v[aux];
        }

        v2[++pos] = term;
        r = aux - 1;
    }

    for(int i = pos ; i > 0 ; --i )
        printf("%d", v2[i]);

    return 0;
}
