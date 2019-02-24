/*
    How about a coding trick?
*/
#include <cstdio>
#include <vector>
#define DIM 50050
using namespace std;
FILE *fin=freopen("sortaret.in","r",stdin);
FILE *fout=freopen("sortaret.out","w",stdout);

vector < int > v[DIM];
int cnt[DIM], rez[DIM], nr;
int n, m;

void Read()
{
    int x, y;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i)
    {
        scanf("%d %d", &x, &y);
        v[ x ].push_back( y );
        ++cnt[y];
    }
    for(int i = 1; i <= n; ++i)
        if( !cnt[i] )
            rez[ ++nr ] = i;
}

void Sort_T()
{
    int i, j;
    for(i = 1; i <= n; ++i)
    {
        int nod = rez[ i ];

        for(j = 0; j < v[ nod ].size(); ++j)
        {
            --cnt[ v[nod][j] ];
            if( !cnt[ v[nod][j] ] )
                rez[ ++nr ] = v[nod][j];
        }
    }
    for(i = 1; i <= n; ++i)
        printf("%d ", rez[i]);
}

int main()
{
    Read();
    Sort_T();
    return 0;
}
