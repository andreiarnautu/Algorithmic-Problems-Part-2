#include <cstdio>
using namespace std;
FILE *fin=freopen("sir7.in","r",stdin);
FILE *fout=freopen("sir7.out","w",stdout);
long S, k;
int main()
{
    long N;
    scanf("%d",&N);
    for(int i=1; i<=N/2 ; ++i)
    {
        k = N - 2 * i;
        while( k > 0 )
        {
            S += k;
            k -= i;
        }
    }
    printf("%d",S);
    return 0;
}
