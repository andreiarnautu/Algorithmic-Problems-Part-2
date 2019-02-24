#include <cstdio>
using namespace std;
FILE *fin=freopen("predecesor.in","r",stdin);
FILE *fout=freopen("predecesor.out","w",stdout);
int N, V[500002];
void Read()
{
    scanf("%d",&N);
    for(int i=1; i <= N ; ++i)
        scanf("%d",&V[i]);
}
void Solve()
{
    int Nr = 1;
    for(int i=1; i < N ; ++i)
        if( V[i] >= V[i+1] )
            ++Nr;
    printf("%d",Nr);
}
int main()
{
    Read();
    Solve();
    return 0;
}
