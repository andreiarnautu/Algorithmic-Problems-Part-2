#include <cstdio>
using namespace std;
FILE *fin=freopen("sir2.in","r",stdin);
FILE *fout=freopen("sir2.out","w",stdout);
int N;


int main()
{
    scanf("%d", &N);
    int S1[1001], S2[1001], S0[1001], Aux1[1001], Aux2[1001], Aux0[1001], t;

    S0[0] = S1[0] = S2[0] = S1[1] = S2[1] = S0[1] = 1;

    for(int i = 2 ; i <= N ; ++i )
    {
        t = 0;
        int j;
        for( j = 1 ; j <= S1[0] || j <= S2[0] || t ; ++j , t /= 10 )
            Aux0[j] = ( t += S1[j] + S2[j] ) % 10;
        Aux0[0] = j - 1;
        t = 0;
        for( j = 1 ; j <= S1[0] || j <= S2[0] || j <= S0[0] || t ; ++j , t /= 10 )
            Aux1[j] = ( t += S1[j] + S2[j] + S0[j] ) % 10;
        Aux1[0] = j - 1;
        t = 0;
        for( j = 1 ; j <= S1[0] || j <= S2[0] || j <= S0[0] || t ; ++j , t /= 10 )
            Aux2[j] = ( t += S1[j] + S2[j] + S0[j] ) % 10;
        Aux2[0] = j - 1;
        for( j = 0 ; j <= Aux0[0] ; ++j )
            S0[j] = Aux0[j];
        for( j = 0 ; j <= Aux1[0] ; ++j )
            S1[j] = Aux1[j];
        for( j = 0 ; j <= Aux2[0] ; ++j )
            S2[j] = Aux2[j];
    }

    t = 0;
    int i;
    for( i = 1 ; i <= S0[0] || i <= S1[0] || t ; ++i, t /= 10 )
        S0[i] = ( t += S0[i] + S1[i] ) % 10;
    S0[0] = i - 1;
    for( i = 1 ; i <= S0[0] || i <= S2[0] || t ; ++i, t /= 10 )
        S0[i] = ( t += S0[i] + S2[i] ) % 10;
    t = 0;
    S0[0] = i - 1;
    for(int i = S0[0] ; i > 0 ;--i )
        printf("%d",S0[i]);

    return 0;
}
