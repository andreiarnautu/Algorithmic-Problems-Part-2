#include <cstdio>
#define DIM 100100
using namespace std;
FILE *fin=freopen("vector.in","r",stdin);
FILE *fout=freopen("vector.out","w",stdout);

int V[DIM];
int n;

void Read()
{
    scanf("%d", &n);
    for(int i = 1; i < n; ++i)
        scanf("%d", &V[i]);
}

void Solve()
{
    int i, xorsum = 0;
    int maxbit = 0, it = 1;

    if((n - 1) % 2 == 1)
        i = n - 1;
    else
        i = n - 2;
    for(; i > 0; i -= 2)
        xorsum ^= V[i];

    if( !xorsum )
    {
        printf("0\n");
        return;
    }
    printf("1\n");

    for(; it <= xorsum; it <<= 1 )
        if( it & xorsum )
            maxbit = it;

    i = 1;

    int start = i, val;

    for(; i < n; i++)
    {
        if( i % 2 == 1 )
            val = V[i] - (V[i] ^ xorsum);
        else
            val = (V[i - 1] ^ xorsum) - V[i - 1];
        if( 0 < val && val <= V[i] )
        {
            printf("%d %d", i, val);
            return;
        }

    }
}

int main()
{
    Read();
    Solve();
    return 0;
}
