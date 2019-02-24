#include <cstdio>
using namespace std;
FILE *fin=freopen("pitag.in","r",stdin);
FILE *fout=freopen("pitag.out","w",stdout);

long long B, C;

int main()
{
    long long A;
    scanf("%lld", &A);
    for(long long i = A - 1 ; i > 0 ; --i )
    {
        if( (A * A - i * i) % ( 2 * i ) == 0 )
        {
            B = ( A * A - i * i) / (2 * i);
            C = B + i;
            printf("%lld %lld\n", B, C);
        }
    }
    return 0;
}
