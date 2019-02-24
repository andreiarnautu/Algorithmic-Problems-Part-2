// How about a coding trick?
#include <cstdio>
#define DIM 260
using namespace std;
FILE *fin=freopen("rf.in","r",stdin);
FILE *fout=freopen("rf.out","w",stdout);

int A[DIM][DIM], cnt[DIM][DIM];
int n;

void Set()
{
    int i, j;
    for(i = 1; i <= n; ++i)
        for(j = 1; j <= n; ++j)
            if( i != j )
                cnt[i][j] = cnt[j][i] = 1;
}

inline int MAX(int a, int b)
{
    return ((a > b) ? a : b);
}

int main()
{
    int i, j, l;
    scanf("%d", &n);
    for(i = 1; i <= n; ++i)
        for(j = 1; j <= n; ++j)
            scanf("%d", &A[i][j]);
    Set();
    for(l = 1; l <= n; ++l)
        for(i = 1; i <= n; ++i)
            for(j = 1; j <= i; ++j)
                if( i != j && i != l && j != l )
                {
                    if( A[i][j] > A[i][l] + A[l][j] )
                    {
                        A[i][j] = A[j][i] = A[i][l] + A[l][j];
                        cnt[i][j] = cnt[j][i] = cnt[i][l] + cnt[l][j];
                    }
                    else if( A[i][j] == A[i][l] + A[l][j] )
                    {
                        cnt[i][j] = MAX( cnt[i][j] , cnt[i][l] + cnt[l][j] );
                        cnt[j][i] = cnt[i][j];
                    }
                }

    for(i = 1; i <= n; ++i)
    {
        for(j = 1; j <= n; ++j)
            printf("%d ", A[i][j]);
        printf("\n");
    }
    for(i = 1; i <= n; ++i)
    {
        for(j = 1; j <= n; ++j)
            printf("%d ", cnt[i][j]);
        printf("\n");
    }
    return 0;
}
