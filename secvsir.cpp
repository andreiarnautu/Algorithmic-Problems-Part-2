#include <cstdio>
#include <cstring>
using namespace std;
FILE *fin=freopen("secvsir.in","r",stdin);
FILE *fout=freopen("secvsir.out","w",stdout);
int N, A[6];
char Sir[2000], Aux[10];

void Check(int x)
{
    memset( Aux , NULL , 6);
    A[0] = 0;
    while( x > 0 )
    {
        A[++A[0]] = x % 10;
        x /= 10;
    }
    for(int i = A[0] ; i > 0 ; --i )
        Aux[A[0] - i] = A[i] + 48;
    if( strstr(Sir, Aux) == NULL )
        strcat(Sir, Aux);
}

int main()
{
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
        Check( i );
    printf("%s", Sir);
    return 0;
}
