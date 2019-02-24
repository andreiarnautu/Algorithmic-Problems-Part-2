#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin=freopen("vila.in","r",stdin);
FILE *fout=freopen("vila.out","w",stdout);

short n, m, best, cnt, val, X, Y, area;
short A[130][130], Zone[130*130], V[4];


void Read()
{
    char s[130];
    scanf("%d %d ", &m, &n);
    for(int i = 1; i <= m  ; ++i)
    {
        gets(s);
        for(int j = 0; j < n ; ++j)
        {
            if(s[j] == '1')
                A[i][j + 1] = -1;
        }
    }
}

void Fill(int x, int y)
{
    ++Zone[cnt];
    A[x][y] = cnt;

    if( x > 1 && A[x - 1][y] == 0 )
        Fill(x - 1, y);
    if( y > 1 && A[x][y - 1] == 0 )
        Fill(x, y - 1);
    if( x < m && A[x + 1][y] == 0 )
        Fill(x + 1, y);
    if( y < n && A[x][y + 1] == 0 )
        Fill(x, y + 1);
}

void Compute_Area(int x, int y)
{
    int i, j, p = 0;
    area = 1;
    V[0] = V[1] = V[2] = V[3] = 0;

    if( A[x - 1][y] != -1 )
        V[0] = A[x - 1][y];
    if( A[x + 1][y] != -1 )
        V[1] = A[x + 1][y];
    if( A[x][y - 1] != -1 )
        V[2] = A[x][y - 1];
    if( A[x][y + 1] != -1 )
        V[3] = A[x][y + 1];

    sort(V, V + 4);
    area += Zone[V[0]];

    for(i = 1; i < 4 ; ++i)
        if( V[i] != V[i - 1] )
            area += Zone[V[i]];


}

void Solve()
{
    for(int i = 1; i <= m ; ++i)
        for(int j = 1; j <= n ; ++j)
            if( A[i][j] == 0 )
            {
                ++cnt;
                Fill(i, j);
                if( Zone[cnt] > best )
                    best = Zone[cnt];
            }

    printf("%d\n%d\n", cnt, best);

    for(int i = 1; i <= m ; ++i)
        for(int j = 1; j <= n ; ++j)
            if( A[i][j] == -1 )
            {
                Compute_Area(i, j);
                if( area > val )
                {
                    val = area;
                    X = i;
                    Y = j;
                }
            }
    printf("%d %d %d", X, Y, val);
}

int main()
{
    Read();
    V[0] = 1, V[1] = 3, V[2] = 4, V[3] = 2;
    Solve();
    return 0;
}
