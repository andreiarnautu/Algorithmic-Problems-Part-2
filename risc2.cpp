/*
    Worg
*/
#include <cstdio>
#include <bitset>
#include <algorithm>

#define DIM 100100

using namespace std;
FILE *fin=freopen("risc2.in","r",stdin);
FILE *fout=freopen("risc2.out","w",stdout);

bitset < DIM > F;
int hsort[DIM], h[DIM], k, DP[DIM];
int n, op, pos, maxelem;

void Read()
{
    int x;
    scanf("%d %d", &op, &n);
    for(int i = 1; i <= n; ++i)
    {
        scanf("%d", &x);
        F[x] = 1, h[i] = x;;
        if( x > maxelem )
            pos = i, maxelem = x;
    }
    for(int i = 1; i <= 100000; ++i)
        if( F[i] )
            hsort[ ++k ] = i;
}

void Solve_1()
{
    int i;
    k = 1;

    for(i = 1; i < pos; ++i)
    {
        if( h[i] != hsort[k] )
        {
            printf("-1");
            return;
        }
        ++k;
    }
    for(i = n; i > pos; --i)
    {
        if( h[i] != hsort[k] )
        {
            printf("-1");
            return;
        }
        ++k;
    }
    printf("%d", pos);
}

void Solve_2()
{
    int i, lg = 0;
    k = 1;
    for(i = 1; i <= n; ++i)
    {
        k += ( h[i] == hsort[k] );
        DP[i] = k - 1;
    }

    k = n;
    for(i = pos; i <= n; ++i)
    {
        if(h[i] == hsort[k])
            ++lg, --k;
    }

    printf("%d", n - max( DP[pos] + lg , DP[n] ) );
}

int main()
{
    Read();
    if( op == 1 )
        Solve_1();
    else
        Solve_2();
    return 0;
}
