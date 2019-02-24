#include <cstdio>
#include <stack>
using namespace std;

FILE *fin=freopen("xspe.in","r",stdin);
FILE *fout=freopen("xspe.out","w",stdout);

stack <int> St;
int C[1000003];
int Val[1000003];
int n;

int main()
{
    int i;
    scanf("%d", &n);
    for(i = 1; i <= n ; ++i)
        scanf("%d", &C[i]);

    for(i = n; i > 0; --i)
    {
        while( !St.empty() && C[St.top()] >= C[i] )
            St.pop();
        Val[i] = C[i];
        if( !St.empty() )
            Val[i] += C[St.top()];
        St.push(i);
    }

    for(i = 1; i <= n; ++i)
        printf("%d ", Val[i]);

    return 0;

}
