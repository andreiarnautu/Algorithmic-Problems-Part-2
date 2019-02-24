/**
  *  Worg
  */
#include <cstdio>
#include <cstring>
#include <algorithm>

#define DIM 1000100
#define INF 2000000000

using namespace std;

FILE *fin=freopen("rps.in","r",stdin);
FILE *fout=freopen("rps.out","w",stdout);

struct trie {
                int best, cnt, next;
                trie *fiu[3];

                trie()
                {
                    best = -INF;
                    memset(fiu, 0, sizeof(fiu));
                    cnt = next = 0;
                }
            };

trie *T = new trie;

char S[DIM];
int N, K, W, D, it;

int val(char c)
{
    if(c > 'P')
        return c - 'P' - 1;
    return 0;
}


int win[] = {1, 2, 0};
char character[] = {'P', 'R', 'S'};

void ins(trie *nod, char *s, int puse)              //insert a string in the trie
{
    ++nod -> cnt;

    if( puse == K )                                 //if it is a node on the last level
    {
        nod -> best = D * nod -> cnt;
        return;
    }

    int nr = val(*s), curent;

    if( !nod -> fiu[nr] )
        nod -> fiu[nr] = new trie;

    ins(nod -> fiu[nr], s + 1, puse + 1);           //else, insert the next character in the trie

    nod -> best = -INF;
    for(int i = 0; i < 3; ++i)                      // update the best option to choose from this node to one of the 3
                                                    // son nodes
    {
        curent = 0;
        if( nod -> fiu[i] )
            curent = nod -> fiu[i] -> best;
        if( nod -> fiu[win[i]] )
            curent += W * nod -> fiu[win[i]] -> cnt ;  // every value can beat another value ( P > R , R > S, S > P )

        if( curent > nod -> best )
        {
            nod -> best = curent;
            nod -> next = i;
        }
    }

}

void query(trie *nod, int puse)
{
    if( puse == K )
        return;

    if( nod -> fiu[nod -> next] )                   // if there is a son node for the best option
    {
        printf("%c", character[nod -> next]);
        query( nod -> fiu[nod -> next], puse + 1);
    }
    else                                            // else, fill the remaining space with "P" characters
    {
        printf("%c", character[nod -> next]);
        for(int i = puse + 1; i < K; ++i)
            printf("P");
    }
}

int main()
{
    int i;
    scanf("%d %d %d %d ", &N, &K, &W, &D);

    for(i = 1; i <= N; ++i)
    {
        gets(S);
        ins(T, S, 0);
        query(T, 0);
        printf("\n");
    }
}
