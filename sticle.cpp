#include <cstdio>

using namespace std;

FILE *fin=freopen("sticle.in","r",stdin);
FILE *fout=freopen("sticle.out","w",stdout);


int main()
{
    int k, n, cnt, nr;
    scanf("%d", &n);

    for(int i = 1 ; i <= n ; ++i )
    {
        scanf("%d", &k);
        if( k == 1 )
        {
            printf("0\n");
            continue;
        }

        cnt = 0;
        nr = 1;
        while( k > nr )
        {
            ++cnt;
            nr <<= 1;
        }

        printf("%d\n", cnt);
    }

    return 0;
}
