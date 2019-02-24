/**
  *  Worg
  */
#include <cstdio>
#include <cstring>

#define sigma 54
#define DIM (1 << 17) + 10

using namespace std;
FILE *fin=freopen("seti.in","r",stdin);
FILE *fout=freopen("seti.out","w",stdout);

struct trie {
                int cnt;
                trie *fiu[sigma];

                trie()
                {
                    memset(fiu, 0, sizeof(fiu));
                    cnt = 0;
                }
            };

trie *T = new trie;

char S[DIM], aux[70], Cuv[32032][20];
int n, m, len;

int val(char c)
{
    if( c >= 'a')
        return c - 'a' + 26;
    return c - 'A';
}

void Read_Text()
{
    scanf("%d ", &n);
    for(int i = 1; i <= n; ++i)
    {
        gets(aux);
        strcat(S, aux);
    }
    len = n * 64;
}

void ins(trie *nod, char *s)
{
    if( !*s )
        return;

    int nr = val( *s );
    if( !nod -> fiu[ nr ] )
        nod -> fiu[ nr ] = new trie;

    ins(nod -> fiu[ nr ], s + 1);
}

void Set()
{
    int i;
    scanf("%d ", &m);

    for(i = 1; i <= m; ++i)
    {
        gets( Cuv[i] );
        ins(T, Cuv[i]);
    }
}

void Update(trie *nod, char *s)
{
    ++nod -> cnt;
    if( !*s )
        return;

    int nr = val( *s );
    if( !nod -> fiu[ nr ] )
    {
        return;
    }
    Update(nod -> fiu[ nr ], s + 1);
}

int Find(trie *nod, char *s)
{
    if( !*s )
        return nod -> cnt;
    return Find(nod -> fiu[ val( *s ) ], s + 1);
}

void Solve()
{
    int i;
    for(i = 0; i < len; ++i)
        Update(T, S + i);

    int ans;
    for(i = 1; i <= m; ++i)
    {
        ans = Find(T, Cuv[i]);
        printf("%d\n", ans);
    }
}

int main()
{
    Read_Text();
    Set();
    Solve();
    return 0;
}
