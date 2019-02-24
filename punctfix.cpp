#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin=freopen("punctfix.in","r",stdin);
FILE *fout=freopen("punctfix.out","w",stdout);
int N, K;
long V[10001], F[200001], Min = 1000000001;
void Read()
{
    scanf("%d",&N);
    for(int i=1 ; i<=N; ++i)
    {
        scanf("%d",&V[i]);
        V[i] = i - V[i];
        if( V[i] < Min )
            Min = V[i];
    }
    for(int i=1; i<=N ; ++i)
        ++F[ V[i] - Min ];
}
void Solve()
{
    int i, x;
    scanf("%d",&K);
    for( i = 1 ; i <= K; ++i)
    {
        scanf("%d",&x);
        if( x < Min )
        {
            printf("0\n");
            continue;
        }
        x -= Min;
        printf("%d\n", F[x]);
    }
}
int main()
{
    Read();
    Solve();
    return 0;
}
