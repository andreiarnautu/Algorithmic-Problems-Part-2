#include <cstdio>
using namespace std;
FILE *fin=freopen("subsets.in","r",stdin);
FILE *fout=freopen("subsets.out","w",stdout);
int N, V[100001];


int main()
{
    scanf("%d", &N);
    V[0] = 1;
    V[1] = 1;
    int t, j, x, y;
    x = (N - 1) / 25;
    y = (N - 1) % 25;
    for(int i = 1 ; i <= x ; ++i )
    {
        t = 0;
        for( j = 1 ; j <= V[0] || t ; t /= 10, ++j )
            V[j] = ( t += 1ll * V[j] * 33554432 ) % 10;
        V[0] = j - 1;
    }
    for(int i = 1 ; i <= y ; ++i )
    {
        t = 0;
        for( j = 1 ; j <= V[0] || t ; t /= 10 , ++j )
            V[j] = ( t += V[j] * 2 ) % 10;
        V[0] = j - 1;
    }
    t = 0;
    for( j = 1 ; j <= V[0] || t ; t /= 10, ++j )
        V[j] = ( t += V[j] * N ) % 10;
    V[0] = j - 1;
  //  printf("%d ",N);
    for(int i = V[0] ; i > 0 ; --i )
        printf("%d", V[i]);
    return 0;
}
