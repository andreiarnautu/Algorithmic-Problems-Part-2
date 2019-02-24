#include <cstdio>
using namespace std;
FILE *fin=freopen("roci.in","r",stdin);
FILE *fout=freopen("roci.out","w",stdout);
int N, F[10007], Max;
void Read()
{
    scanf("%d",&N);
    int x;
    for(int i=0; i<N ; ++i)
    {
        scanf("%d",&x);
        ++F[x];
    }
}
void Solve()
{
    int i, j, Nr=0;
    for( i=1; i<=10000 ; ++i)
        if( F[i] > 0 && ( F[i] < F[i-1] && F[i] < F[i+1]) )
        {
         //   printf("%d ",i);
            Nr += F[i];
            for( j=i-1 ; j>0 ; j--)
            {
                if( F[j] < F[i] )
                    break;
                F[j] -= F[i];
            }
            for( j=i+1 ; j<=10000 ; j++)
            {
                if( F[j] < F[i] )
                    break;
                F[j] -= F[i];
            }
        }
    for( i=1; i<=10000 ; ++i)
    {
        if( F[i] )
        {
         //   printf("%d ",i);
            Max = F[i];
            while( F[i] > 0 )
            {
                if( F[i] > Max)
                    Max = F[i];
                ++i;
            }
            Nr += Max;
        }
    }
    printf("%d",Nr);
}
int main()
{
    Read();
    Solve();
    return 0;
}
