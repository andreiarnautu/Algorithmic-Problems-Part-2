/*
    Worg
*/
#include <cstdio>
#include <utility>
#include <algorithm>

#define zeros(x) ((x ^ (x - 1)) & x)
#define PII pair<int,int>
#define fi first
#define se second
#define DIM 1010
#define NMax 169

using namespace std;
FILE *fin=freopen("roboti2.in","r",stdin);
FILE *fout=freopen("roboti2.out","w",stdout);

PII v[DIM];
int N, M, T, op;
int AIB[ NMax ][ NMax ];

void Read()
{
    int i, x, y;
    scanf("%d", &op);
    scanf("%d %d %d", &N, &M, &T);

    for(i = 1; i <= T; ++i)
    {
        scanf("%d %d", &x, &y);
        y = M - y + 1;
        v[i] = make_pair(x, y);
    }
    sort(v + 1, v + T + 1);
}

inline void Add(int x, int y, int val)
{
    int i, j;
    for(i = x; i <= N; i += zeros(i))
        for(j = y; j <= M; j += zeros(j))
        {
            if( AIB[i][j] >= val )
                break;
            AIB[i][j] = max( AIB[i][j], val );
        }
}

inline int Query(int x, int y)
{
    int i, j, ret = 0;
    for(i = x; i; i -= zeros(i))
        for(j = y; j; j -= zeros(j))
            ret = max( ret, AIB[i][j] );
    return ret;
}

inline void Set(int x, int y)
{
    int i, j;
    for(i = x; i <= N; i += zeros(i))
        for(j = y; j <= M; j += zeros(j))
            AIB[i][j] = 0;
}

inline int robCount(int L)
{
    int ans = 1, curent, i, j;

    for(i = 1; i <= T; ++i)
    {
        curent = 1;

        if( v[i].first > L && v[i].second > L )
            curent += Query( v[i].first - L, v[i].second - L );
        ans = max(curent, ans);

        Add( v[i].first, v[i].second, curent );
    }
    for(i = 1; i <= T; ++i)
        Set( v[i].first, v[i].second );

    return ans;
}

int main()
{
    Read();
    if( op == 1 )
    {
        int L; scanf("%d", &L);
        printf("%d ", robCount( L ));
    }
    else
    {
        int q, k, st, dr, m, sol;
        for(scanf("%d", &q); q; --q)
        {
            scanf("%d", &k);
            st = 1, dr = N / k + 1;
            while(st <= dr)
            {
                m = (st + dr) >> 1;
                if( robCount(m) > k )
                    st = m + 1;
                else
                    sol = m, dr = m - 1;
            }
            printf("%d\n", sol);
        }
    }
}
