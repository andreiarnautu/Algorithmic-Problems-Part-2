#include <cstdio>
#include <unordered_map>
#include <vector>
#define DIM (1 << 20) + 3
using namespace std;
FILE *fin=freopen("secv5.in","r",stdin);
FILE *fout=freopen("secv5.out","w",stdout);

unordered_map <unsigned int,unsigned int> HASH;
unsigned int v[DIM];
long long int n, L, U;

void Read()
{
    int i;
    scanf("%lld%lld%lld", &n, &L, &U);
    for(i = 1; i <= n; ++i)
        scanf("%ud", &v[i]);
}

inline long long int Secv(long long int nr)
{
    long long int ret = 0;
    int i, p1;

    for(i = 1, p1 = 1; i <= n; ++i)
    {
        ++HASH[v[i]];
        while( HASH.size() > nr )
        {
            --HASH[v[p1]];
            if( HASH[v[p1]] == 0 )
                HASH.erase(v[p1]);
            ++p1;
        }
        ret += ( i - p1 + 1 );
    }
    return ret;

}

void Solve()
{
    long long int a, b;
    a = Secv(U); HASH.clear();
    b = Secv(L - 1);
    printf("%lld", a - b);
}

int main()
{
    Read();
    Solve();
    return 0;
}
