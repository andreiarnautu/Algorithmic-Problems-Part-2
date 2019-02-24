// How about a coding trick?
#include <cstdio>
#include <ctime>
#include <algorithm>
#define DIM 100100
#define INF 1LL * 1000000000000
using namespace std;

FILE *fin=freopen("stalpi.in","r",stdin);
FILE *fout=freopen("stalpi.out","w",stdout);
struct type
            {
                int x, s, d;
                long long int c;
            };
type A[DIM];
int n;
long long int DP[DIM];

inline bool comp( type a, type b )
{
    return a.x < b.x;
}

void Read()
{
    int i;
    scanf("%d", &n);
    for(i = 1; i <= n; ++i)
        scanf("%d %lld %d %d", &A[i].x, &A[i].c, &A[i].s, &A[i].d);
    sort( A + 1, A + n + 1, comp );
}

inline int min_binary(int val)
{
    int st = 1, dr = n, sol = 0, m;

    while( st <= dr )
    {
        m = (st + dr) / 2;
        if( val <= A[m].x )
        {
            sol = m;
            dr = m - 1;
        }
        else
            st = m + 1;
    }
    return sol;
}

inline int max_binary(int val)
{
    int st = 0, dr = n, sol = n, m;

    while( st <= dr )
    {
        m = (st + dr) / 2;
        if( val >= A[m].x )
        {
            sol = m;
            st = m + 1;
        }
        else
            dr = m - 1;
    }
    return sol;
}

inline long long int MIN(long long int a, long long int b)
{
    if( a > b )
        return b;
    return a;
}

void Solve()
{
    int i, st, dr, i1, i2, j;
    clock_t start, finish;
    start = clock();

    DP[0] = 1LL * 0;
    for(i = 1; i <= n; ++i)
        DP[i] = 1LL * INF;

    for(i = 1; i <= n; ++i)
    {
        st = A[i].x - A[i].s;
        dr = A[i].x + A[i].d;
        i1 = min_binary(st);
        i2 = max_binary(dr);
        //printf("%d %d ", i1, i2);

        DP[i2] = MIN( DP[i2], DP[i1 - 1] + A[i].c );
        for(j = i2 - 1; j && DP[i2] < DP[j]; --j)
            DP[j] = DP[i2];
        //for(j = 1; j <= 4; ++j)
            //printf("%lld ", DP[j]);
       // printf("\n");
    }
    finish = clock();
    //printf("%.3f ", (float)(finish - start) / CLOCKS_PER_SEC);
}

void Write()
{
    printf("%lld", DP[n]);
}

int main()
{
    Read();
    Solve();
    Write();
    return 0;
}
