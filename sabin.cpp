/**
  *  Worg
  */
#include <cstdio>
#include <cstring>

#define sigma 26
#define DIM 30300

using namespace std;
FILE *fin=freopen("sabin.in","r",stdin);
FILE *fout=freopen("sabin.out","w",stdout);

struct trie {
                int cnt;
                trie *fiu[sigma];

                trie()
                {
                    cnt = 0;
                    memset(fiu, 0, sizeof(fiu));
                }
            };

trie *T = new trie;
char S[20][33], R[600], sir[DIM][33];

int N, K, M, P, Q, X, nr, ord;
int v[20];

int val(char c)
{
    return c - 'a';
}

void ins(trie *nod , char *s)
{
    ++nod -> cnt;
    if( !*s )
    {
        return;
    }

    int nr = val(*s);

    if( !nod -> fiu[ nr ] )
        nod -> fiu[ nr ] = new trie;

    ins(nod -> fiu[ nr ], s + 1);
}

void Set()
{
    int i, j, l, pos;
    scanf("%d %d %d %d %d ", &N, &K, &M, &P, &Q);

    for(i = 1; i <= N; ++i)
    {
        for(j = 1; j <= K; ++j)
            scanf("%s", S[j]);

        pos = -1;
        for(j = 0; j < P; ++j)
            for(l = 1; l <= K; ++l)
                R[ ++pos ] = S[ l ][ j ];
        ins(T, R);
    }
    for(i = 1; i <= M; ++i)
        scanf("%s", sir[i]);

}

char GiveChar()
{
    if(nr == K)
        nr = 1, ++ord;
    else
        ++nr;
    return sir[ v[nr] ][ord];

}

int prefix(trie *nod, int rest)
{
    char c = GiveChar();
    int nr = val(c);

    if( !rest  )
        return nod -> cnt;

    if( !nod -> fiu[ nr ] )
        return 0;

    return prefix(nod -> fiu[ nr ], rest - 1);
}

void Query()
{
    int i;
    scanf("%d", &X);
    for(i = 1; i <= K; ++i)
        scanf("%d", &v[i]);

    int q1, q2;

    nr = 0, ord = 0;
    q1 = prefix(T, X * K);

    nr = 0, ord = 0;
    q2 = prefix(T, (X + 1) * K);

    printf("%d\n", q1 - q2);
}

int main()
{
    Set();
    for(int i = 1; i <= Q; ++i)
        Query();
    return 0;
}
