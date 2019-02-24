#include <cstdio>
#define Dim 5013
using namespace std;
FILE *fin=freopen("ratb.in","r",stdin);
FILE *fout=freopen("ratb.out","w",stdout);

int V[Dim], Sum[Dim], N, K, x, Secv[Dim], Best[Dim], Pos1, Pos2, Max = -5555555, I;

int main()
{
    scanf("%d%d", &N, &K);
    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%d", &x);
        V[i] = x;
        Sum[i] = Sum[i - 1] + x;
    }
    for(int i = K ; i <= N ; ++i )
        Secv[i] = Sum[i] - Sum[i - K];
    Best[K - 1] = Sum[K - 1];
    for(int i = K ; i <= N ; ++i )
    {
        if( Best[i - 1] + V[i] > Secv[i] )
            Best[i] = Best[i - 1] + V[i];
        else
        {
            Best[i] = Secv[i];
            I = i - K + 1;
        }
        if( Best[i] > Max )
        {
            Max = Best[i];
            Pos1 = I;
            Pos2 = i;
        }
    }
    printf("%d\n", Max);
    printf("%d %d\n", Pos1 , Pos2);
    return 0;
}
