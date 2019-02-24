#include <cstdio>
#include <algorithm>

using namespace std;

FILE *fin=freopen("suma2.in","r",stdin);
FILE *fout=freopen("suma2.out","w",stdout);
int n, smax, a, b, c, x;


int main()
{
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++i )
    {
        scanf("%d", &x);
        c = max( b, a + x );
        a = b;
        b = c;
    }
    printf("%d", c);
    return 0;
}
