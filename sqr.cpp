#include <cstdio>
using namespace std;
FILE *fin=freopen("sqr.in","r",stdin);
FILE *fout=freopen("sqr.out","w",stdout);
int N;
bool Viz[100001];
int V[20000], k, F[20000], Nr[1003];

void Ciur()
{
    int i, j;
    V[0] = 2;
    for( i = 3 ; i * i <= 100000 ; i +=2 )
        if( !Viz[i] )
        {
            for( j = i * i ; j <= 100000 ; j += 2 * i )
                Viz[j] = 1;
        }
    for( i = 3 ; i <= 100000 ; i += 2 )
        if( !Viz[i] )
            V[++k] = i;
 //   for(int i = 0 ; i <= k ; ++i )
   //     printf("%d ",V[i]);
}

void Div(int x)
{
    int p = 0;
    while( p <= k && x )
    {
        while( x % V[p] == 0 )
        {
            x /= V[p];
            F[p] ++;
        }
        ++p;
    }
}

void Read()
{
    scanf("%d", &N);
    int x;
    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%d", &x);
     //   printf("%d",x);
        Div(x);
    }
}

void Raise(int q)
{
    int i, t = 0;
    for( i = 1 ; i <= Nr[0] || t ; i++, t /= 10 )
        Nr[i] = ( t += Nr[i] * q ) % 10;
    Nr[0] = i - 1;
}

void Solve()
{
    for(int i = 0 ; i <= k ; ++i )
        if( F[i] % 2 == 1 )
            Raise( V[i] );
  //  for(int i = 0 ; i <= 10 ; ++i )
    //    printf("%d ",F[i]);
    for(int i = Nr[0] ; i > 0 ; --i )
        printf("%d",Nr[i]);
}

int main()
{
    Nr[0] = 1, Nr[1] = 1;
    Ciur();
    Read();
    Solve();
}
