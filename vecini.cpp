#include <cstdio>
#define Dim 1003
using namespace std;
FILE *fin=freopen("vecini.in","r",stdin);
FILE *fout=freopen("vecini.out","w",stdout);
int N, V1[Dim], V2[Dim], V3[Dim];
int Aux1[Dim], Aux2[Dim], Aux3[Dim];

int main()
{
    int j , t;
    scanf("%d", &N);
    V1[0] = V2[0] = V3[0] = V1[1] = V2[1] = V3[1] = 1;
    for(int i = 1 ; i < N ; ++i )
    {
        t = 0;
        for( j = 1 ; j <= V1[0] || j <= V2[0] || t ; ++j , t /= 10 )
            Aux1[j] = ( t += V1[j] + V2[j] ) % 10;
        Aux1[0] = j - 1;
        t = 0;
        for( j = 1 ; j <= V1[0] || j <= V2[0] || j <= V3[0] || t ; t /= 10 , ++j )
            Aux2[j] = ( t += V1[j] + V2[j] + V3[j] ) % 10;
        Aux2[0] = j - 1;
        t = 0;
        for( j = 1 ; j <= V2[0] || j <= V3[0] || t ; t /= 10 , ++j )
            Aux3[j] = ( t += V2[j] + V3[j] ) % 10;
        Aux3[0] = j - 1;
        for( j = 0 ; j <= Aux1[0] ; ++j )
            V1[j] = Aux1[j];
        for( j = 0 ; j <= Aux2[0] ; ++j )
            V2[j] = Aux2[j];
        for( j = 0 ; j <= Aux3[0] ; ++j )
            V3[j] = Aux3[j];
    }

    t = 0;
    for( j = 1 ; j <= V1[0] || j <= V2[0] || j <= V3[0] || t ; t /= 10 , ++j )
        V1[j] = ( t += V1[j] + V2[j] + V3[j] ) % 10;
    V1[0] = j - 1;
    for( j = V1[0] ; j > 0 ; --j )
        printf("%d", V1[j]);
    return 0;
}
