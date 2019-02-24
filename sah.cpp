/*
    Worg
*/
#include <cstdio>
using namespace std;
FILE *fin=freopen("sah.in","r",stdin);
FILE *fout=freopen("sah.out","w",stdout);

int main()
{
    int n, i, j, zones = 0;
    scanf("%d", &n);
    for(i = 1; i <= n; ++i)
    {
        for(j = 1; j <= n; ++j)
            printf("%d ", zones + (i + 1) / 2 + ( j > (n - (i - 1) / 2) ) );
        printf("\n");
        zones += (i % 2 == 0 && i > 2);
    }
    return 0;
}
