/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <cstring>

#define DIM 101
#define sigma 26
#define buffDIM 305

using namespace std;
FILE *fin=freopen("sub.in","r",stdin);
FILE *fout=freopen("sub.out","w",stdout);

struct trie {
                trie *fiu[sigma];
                int a, b;

                trie()
                {
                    memset(fiu, 0, sizeof(fiu));
                    a = b = 0;
                }
            };

trie *T = new trie;
char S[buffDIM];
queue < trie* > Q;
int na;

int val(char c)
{
    return c - 'a';
}

void ins(trie *nod, char *s, int grup, int nr)
{
    if( grup == 1 )
    {
        if( nod -> a == nr - 1 )
            ++nod -> a;
        else if( nod -> a < nr - 1 )
            return;
    }
    else
        nod -> b = 1;


    if( *s == '\n' )
        return;

    int next = val( *s );

    if( !nod -> fiu[ next ] )
    {
        if( grup == 2 )
            return;
        nod -> fiu[ next ] = new trie;
    }
    ins(nod -> fiu[ next ], s + 1, grup, nr);
}

void BFS()
{
    Q.push( T );
    trie *nod;

    int i, ans = 0;

    while( !Q.empty() )
    {
        nod = Q.front(); Q.pop();
        if( nod -> b == 0 && nod -> a == na )
            ++ans;

        for(i = 0; i < sigma - 1; ++i)
            if( nod -> fiu[i] && nod -> a == na )
                Q.push( nod -> fiu[i] );
    }
    printf("%d", ans);
}

int main()
{
    int i, nb, j, lg;
    scanf("%d ", &na);
    for(i = 1; i <= na; ++i)
    {
        fgets(S, buffDIM, stdin);
        lg = strlen(S);
        for(j = 0; j <= lg - 2; ++j)
            ins(T, S + j, 1, i);
    }

    scanf("%d ", &nb);
    for(i = 1; i <= nb; ++i)
    {
        fgets(S, buffDIM, stdin);
        lg = strlen(S);
        for(j = 0; j <= lg - 2; ++j)
            ins(T, S + j, 2, i);
    }

    BFS();

    return 0;
}
