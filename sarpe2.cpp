#include <cstdio>
#include <vector>
#define Max 100003
#define Mod 666013
using namespace std;

FILE *fin=freopen("sarpe2.in","r",stdin);
FILE *fout=freopen("sarpe2.out","w",stdout);

const int dx[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
const int dy[8] = {-1, 0, 1,-1, 1,-1, 0, 1};
vector <int> F(Max, 0), nr;
vector < vector<int> > A(1001), Cnt(1001);
int n, m;

void Read()
{
    int i, j, x;
    scanf("%d%d", &n, &m);

    nr.reserve(m + 1), F.reserve(Max);
    for(i = 1; i <= m ; ++i)
    {
        scanf("%d", &x);
        nr[i] = x;
        F[x] = i;
    }

    for(i = 1; i <= n ; ++i)
    {
        A[i].reserve(n + 1), Cnt[i].reserve(n + 1);

        for(j = 1; j <= n ; ++j)
            scanf("%d", &A[i][j]);
    }

    for(i = 1; i <= n ; ++i)
        for(j = 1; j <= n ; ++j)
            Cnt[i][j] = -1;
}

void Check(int x, int y)
{
    int i, j, val;
    if( F[A[x][y]] == 0 )
    {
        Cnt[x][y] = 0;
        return;
    }

    if( F[A[x][y]] == 1 )
    {
        Cnt[x][y] = 1;
        return;
    }

    val = nr[ F[A[x][y]] - 1 ];
    Cnt[x][y] = 0;

    for(i = 0; i < 8 ; ++i)
            if( x + dx[i] > 0 && y + dy[i] > 0 && x + dx[i] <= n && y + dy[i] <= n && A[x + dx[i]][y + dy[i]] == val )
            {
                if( Cnt[x + dx[i]][y + dy[i]] == -1 )
                    Check(x + dx[i], y + dy[i]);
                Cnt[x][y] = (Cnt[x + dx[i]][y + dy[i]] + Cnt[x][y]) % Mod;
            }
}

void Solve()
{
    int i, j, sol = 0;

    for(i = 1; i <= n ; ++i)
        for(j = 1; j <= n ; ++j)
        {
            if( Cnt[i][j] == -1 )
                Check(i, j);
        }

    for(i = 1; i <= n ; ++i)
        for(j = 1; j <= n ; ++j)
            if( A[i][j] == nr[m] )
                sol = (sol + Cnt[i][j]) % Mod;

    printf("%d", sol);
}

int main()
{
    Read();
    Solve();
    return 0;
}
