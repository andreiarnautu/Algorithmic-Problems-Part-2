// How about a coding trick?
#include <cstdio>
#include <vector>
#include <bitset>
#define DIM 1010
using namespace std;
FILE *fin=freopen("rox.in","r",stdin);
FILE *fout=freopen("rox.out","w",stdout);
//FILE *fout = freopen("rox.in","w",stdout);
char Sol[DIM][DIM];
int m, n, u;

bitset <DIM> sum[DIM];
bitset <DIM> pos[DIM];

struct coord{
                int i1, j1, i2, j2;
            };

vector < coord > V[30];

void Read()
{
    int i, x1, y1, x2, y2, numeric;
    coord aux;
    char c;
    scanf("%d%d%d", &n, &m, &u);
    //printf("%.3f\n", (float)(sizeof(sum) + sizeof(pos) + sizeof(Sol) + sizeof(W)) / 1024);
    for(i = 1; i <= u; ++i)
    {
        scanf("%d %d %d %d %c", &x1, &y1, &x2, &y2, &c);
        aux.i1 = x1, aux.j1 = y1, aux.i2 = x2, aux.j2 = y2, numeric = c - 'A' + 1;
        V[numeric].push_back(aux);
    }
}

void Gen(int lit)
{
    if( V[lit].size() == 0 )
        return;
    int i, j = V[lit].size(), x1, y1, x2, y2;
    int ok;

    for(i = 0; i < j; ++i)
    {
        x1 = V[lit][i].i1, y1 = V[lit][i].j1, x2 = V[lit][i].i2, y2 = V[lit][i].j2;

        pos[x1][y1] = 1 - pos[x1][y1];
        pos[x1][y2 + 1] = 1 - pos[x1][y2 + 1];
        pos[x2 + 1][y1] = 1 - pos[x2 + 1][y1];
        pos[x2 + 1][y2 + 1] = 1 - pos[x2 + 1][y2 + 1];
    }

    ok = 0;
    for(i = 1; i <= n; ++i)
    {
        ok = 0;
        for(j = 1; j <= m; ++j)
        {
            ok = ( sum[i - 1][j - 1] + sum[i - 1][j] + pos[i][j] + ok ) % 2;
            if( ok )
                ++Sol[i][j];
            sum[i][j] = ok;
        }
    }
    j = V[lit].size();
    for(i = 0; i < j; ++i)
    {
        x1 = V[lit][i].i1, y1 = V[lit][i].j1, x2 = V[lit][i].i2, y2 = V[lit][i].j2;
        pos[x1][y1] = 1 - pos[x1][y1];
        pos[x1][y2 + 1] = 1 - pos[x1][y2 + 1];
        pos[x2 + 1][y1] = 1 - pos[x2 + 1][y1];
        pos[x2 + 1][y2 + 1] = 1 - pos[x2 + 1][y2 + 1];
    }

}

inline void Query()
{
    int x, y;
    scanf("%d%d", &x, &y);
    printf("%d\n", Sol[x][y]);
}

int main()
{
    Read();
    for(int i = 1; i <= 26; ++i)
        Gen(i);
    int q; scanf("%d", &q);
    for(; q; --q)
        Query();
    return 0;
}
