/**
  *  Worg
  */
#include <cstdio>

#define INF         1000000000
#define MAX_N       1 + 100

using namespace std;
FILE *fin=freopen("royfloyd.in","r",stdin);
FILE *fout=freopen("royfloyd.out","w",stdout);

int A[MAX_N][MAX_N];
int n;

int main()
{
    int i, j, k;
    scanf("%d", &n);
    for(i = 1; i <= n; ++i)
        for(j = 1; j <= n; ++j) {

            scanf("%d", &A[i][j]);
            A[i][j] = (A[i][j] != 0 ? A[i][j] : INF);
        }

    for(k = 1; k <= n; ++k)
        for(i = 1; i <= n; ++i)
            for(j = 1; j <= n; ++j)
                if( i != j && A[i][j] > A[i][k] + A[k][j])
                    A[i][j] = A[i][k] + A[k][j];

    for(i = 1; i <= n; ++i)
    {
        for(j = 1; j <= n; ++j)
            printf("%d ", (A[i][j] != INF ? A[i][j] : 0));
        printf("\n");
    }
    return 0;
}
