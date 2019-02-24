/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstring>

#define DIM 10100
#define sigma 27

using namespace std;
FILE *fin=freopen("ratina.in","r",stdin);
FILE *fout=freopen("ratina.out","w",stdout);

struct trie {
                trie *fiu[sigma];

                trie()
                {
                    memset(fiu, 0, sizeof(fiu));
                }
            };
trie *T = new trie;
int n, m, x, Q[31];
char S[2020];

vector < trie* > V[DIM];

int val(char c)
{
    return c - 'a';
}

void ins(trie *nod, char *s, int ord)   // when we insert a string in the trie, we want to include in the vector
                                        // the trie nodes for each character of the string
{
    V[ord].push_back( nod );
    if( *s == '\n' )
        return;

    int nr = val(*s);

    if( nod -> fiu[ nr ] == 0 )
    {
        nod -> fiu[ nr ] = new trie;
    }

    ins( nod -> fiu[ nr ], s + 1 , ord );
}

void Query()                                // we binary search the length
                                            // when we check, we have to have on the same position the same node
{
    int i, st = 0, dr = 2020, m, sol = 0;
    bool ok;

    while(st <= dr)
    {
        m = (st + dr) >> 1;
        if( m >= V[ Q[1] ].size() )
        {
            dr = m - 1; continue;
        }

        ok = 1;
        for(i = 2; i <= x; ++i)
            if( m >= V[ Q[i] ].size() || V[ Q[i] ][ m ] != V[ Q[1] ][ m ] )
            {
                ok = 0;
                break;
            }

        if( ok )
            sol = m, st = m + 1;
        else
            dr = m - 1;
    }
    printf("%d\n", sol);
}

int main()
{
    scanf("%d %d ", &n, &m);
    for(int i = 1; i <= n; ++i)
    {
        fgets(S, 2002, stdin);          // introduce a string in the trie
        ins(T, S, i);
    }
    for(int i = 1; i <= m; ++i)
    {
        scanf("%d", &x);                // query
        for(int j = 1; j <= x; ++j)
            scanf("%d", &Q[j]);
        Query();
    }
    return 0;
}
