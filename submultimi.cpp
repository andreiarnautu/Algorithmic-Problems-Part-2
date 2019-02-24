#include <cstdio>
using namespace std;
FILE *fin=freopen("submultimi.in","r",stdin);
FILE *fout=freopen("submultimi.out","w",stdout);

int n;
int val[20];

void Set()
{
    scanf("%d", &n);
    for(int i = 1, p = 1; i <= n; ++i, p <<= 1)
        val[i] = p;
}

void Write(int nr)
{
    int i;
    for(i = 1; i <= n; ++i)
        if( nr & val[i] )
            printf("%d ", i);
    printf("\n");
}

int main()
{
    Set();
    int i, nr = 1 << n;
    for(i = 1; i < nr; ++i)
        Write(i);
    return 0;
}
