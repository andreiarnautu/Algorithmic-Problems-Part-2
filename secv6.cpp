#include <cstdio>
#include <stack>
#define MaxN 16000013
using namespace std;

FILE *fin=freopen("secv6.in","r",stdin);
FILE *fout=freopen("secv6.out","w",stdout);

stack <int> St;
int n, m = 8192;
int aux[8200], V[MaxN];


void Read()
{
    int i;
    scanf("%d", &n);
    if(n < m)
        m = n;
    for(i = 0; i < m ; ++i)
        scanf("%d", &aux[i]);

    for(i = 0; i < n ; ++i)
        V[i] = i + (aux[i % 8192] ^ aux[i / 8192]);
}

void Solve()
{
    int i;
    long long int cnt = 0;

    for(i = 0; i < n ; ++i)
    {
        while( !St.empty() && V[St.top()] < V[i] )
        {
            ++cnt;
            St.pop();
        }

        if( !St.empty() )
        {
            ++cnt;
            if( V[St.top()] == V[i] )
                St.pop();
        }
        St.push(i);
    }

    printf("%lld", cnt);

}

int main()
{
    Read();
    Solve();
    return 0;
}
