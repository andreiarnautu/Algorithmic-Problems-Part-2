/**
  *  Worg
  */
#include <cstdio>
#include <cstring>

#define sigma 2
#define DIM 100100

using namespace std;
FILE *fin=freopen("xormax.in","r",stdin);
FILE *fout=freopen("xormax.out","w",stdout);

struct trie {
                int indice;
                trie* fiu[sigma];

                trie()
                {
                    memset(fiu, 0, sizeof(fiu));
                }
            };

trie *T = new trie;
int sum[DIM];
int n;

void Read()
{
    int i, x;
    scanf("%d", &n);
    for(i = 1; i <= n; ++i)
    {
        scanf("%d", &x);
        sum[i] = sum[i - 1] ^ x;        // partial XOR sums
    }
}

void Update(int x, int ind)             // update the trie with the current XOR sum
{
    trie *nod = T;
    int bit;

    for(int i = (1 << 21); i; i >>= 1)
    {
        bit = ( (i & x) > 0 );

        if( !nod -> fiu[ bit ] )
            nod -> fiu[ bit ] = new trie;
        nod = nod -> fiu[ bit ];
    }
    nod -> indice = ind;
}

int Query(int x)                        // find the suitable element to maximize the XOR sum with the current element
{
    trie *nod = T;

    int bit;
    for(int i = (1 << 21); i; i >>= 1)
    {
        bit = ( (i & x) > 0 );

        if( nod -> fiu[ !bit ] )
            nod = nod -> fiu[ !bit ];
        else
            nod = nod -> fiu[ bit ];
    }
    return nod -> indice;
}

int main()
{
    Read();
    Update(sum[1], 1);

    int ind, ans = sum[1], i, st = 1, dr = 1;
    for(i = 2; i <= n; ++i)
    {
        ind = Query( sum[i] );
        if( ( sum[ i ] ^ sum[ ind ] ) > ans )               // if we found a XOR sum bigger than the one before
        {
            ans = sum[ i ] ^ sum[ ind ], st = ind + 1, dr = i;
        }
        Update(sum[i], i);
    }
    printf("%d %d %d", ans, st, dr);
    return 0;
}
