#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
#define MOD 100003
#define BASE 31
#define DIM 1000010
#define DIM2 3000
using namespace std;
FILE *fin=freopen("radio2.in","r",stdin);
FILE *fout=freopen("radio2.out","w",stdout);

vector < vector<int> > HASH(MOD);
vector <int>::iterator it;

int n, m, l, k, len;
char S[DIM], T[DIM2];

void Read()
{
    scanf("%d %d %d %d ", &n, &m, &l, &k);
    scanf("%s", S);
}

void Build_Hash()
{
    len = l / (k + 1);
    int i, j, val = 0, p = 1;

    for(i = 1; i < len; ++i)
        p = (1LL * p * BASE) % MOD;

    for(i = 0; i < n; ++i)
    {
        val = (val * BASE + (S[i] - 'a')) % MOD;
        if( i >= len - 1 )
        {
            HASH[val].push_back(i - len + 1);

            val = (val - (S[i - len + 1] - 'a') * p ) % MOD;
            if( val < 0 )
                val += MOD;
        }
    }
}

inline int dist(int pos)
{
    int i, ret = 0;
    for(i = 0; i < l; ++i)
        if( T[i] != S[i + pos] )
        {
            ++ret;
            if( ret > k )
                return ret;
        }
    return ret;
}

inline int Check(int pos)
{
    if( pos < 0 || pos + l - 1 >= n )
        return 0;
    return ( dist(pos) <= k );
}

void Solve()
{
    if( l <= k )
    {
        for(int i = 1; i <= m; ++i)
            printf("1\n");
        return;
    }

    Build_Hash();
    int i, j, ans, val, q;

    for(i = 1; i <= m; ++i)
    {
        scanf("%s", T);
        for(ans = 0, j = 0; j + len <= l && !ans; j += len )
        {
            for(val = 0, q = 0; q < len; ++q)
                val = ( val * BASE + (T[q + j] - 'a') ) % MOD;
            if( HASH[val].size() != 0 )
                for( it = HASH[val].end() - 1; ; --it )
                {
                    ans = max(ans, Check(*it - j));
                    if( ans || it == HASH[val].begin())
                        break;
                }

        }
        printf("%d\n", ans);
    }
}

int main()
{
    Read();
    Solve();
    return 0;
}
