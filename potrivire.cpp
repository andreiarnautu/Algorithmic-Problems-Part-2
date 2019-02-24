/**
  *  Worg
  */
#include <cstdio>
#include <cstring>

#define DIM 15100

using namespace std;
FILE *fin=freopen("potrivire.in","r",stdin);
FILE *fout=freopen("potrivire.out","w",stdout);

char A[DIM], B[DIM], S[DIM], sep[] = " *", *pointer;
int pi[DIM];
int n, m, lastpos = -1, left;
bool ok = 1;

void Solve()
{
    int d = 0, k = 0, i, len = strlen(pointer), val;
    for(i = 1; i <= len; ++i)
        S[i] = pointer[i - 1];

    for(i = 2; i <= len; ++i)
    {
        while( k && S[i] != S[k + 1] )
            k = pi[k];
        if( S[i] == S[k + 1] )
            ++k;
        pi[i] = k;
    }

    for(i = lastpos + 1; i < n; ++i)
    {
        while( d && A[i] != S[d + 1] )
            d = pi[d];
        if( A[i] == S[d + 1] )
            ++d;
        if( i > lastpos && d == len )
        {
            val = i - len + 1 - lastpos;

            if(val <= 0)
            {
                continue;
            }

            if( lastpos == -1 )
                left = i - len + 1;
            lastpos = i;
            return;
        }
    }
    ok = 0;

}

int main()
{
    scanf("%d %d ", &n, &m);
    scanf("%s", A); scanf("%s", B);

    pointer = strtok(B, sep);

    while( pointer != NULL )
    {
        Solve();
        pointer = strtok(NULL, sep);
    }

    if( !ok )
    {
        printf("-1"); return 0;
    }

    if( B[0] == '*' )
        left = 0;

    if(lastpos < left)
        lastpos = left;

    printf("%d %d", left + 1, lastpos + 1);
    return 0;
}
