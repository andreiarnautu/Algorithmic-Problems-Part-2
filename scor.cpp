#include <cstdio>
#include <cstring>
using namespace std;
FILE *fin = freopen("scor.in" , "r", stdin);
FILE *fout = freopen("scor.out" , "w" , stdout);

void Solve()
{
    char S1[103], S2[103];
    int S[103] = {0}, D[103] = {0}, Aux[105] = {0}, i;

    scanf("%s%s", &S1, &S2);
    S[0] = strlen(S1);
    for( i = 1 ; i <= S[0] ; ++i )
        S[i] = S1[S[0] - i] - 48;
    D[0] = strlen(S2);
    for( i = 1 ; i <= D[0] ; ++i )
        D[i] = S2[D[0] - i] - 48;

    int t = 0;
    if( D[0] > S[0] )
    {
        printf("impossible\n");
        return;
    }
    else if( D[0] == S[0] )
    {
        for( i = D[0] ; i > 0 ; i-- )
        {
            if( D[i] > S[i] )
            {
                printf("impossible\n");
                return;
            }
            else if( S[i] > D[i] )
                break;
        }
    }

    for( i = 1 ; i <= S[0] || t ; ++i , t /= 10 )
        Aux[i] = ( t += S[i] + D[i] ) % 10;
    Aux[0] = i - 1;
   // for( i = Aux[0] ; i > 0 ; --i )
  //      printf("%d",Aux[i]);
    if( Aux[1] % 2 == 1 )
    {
        printf("impossible \n");
        return;
    }

    t = 0;
    for( i = Aux[0] ; i > 0 ; --i , t %= 2 )
        Aux[i] = ( t = t * 10 + Aux[i] ) / 2;
    while( Aux[Aux[0]] == 0 )
        --Aux[0];
    for( i = Aux[0] ; i > 0 ; --i )
        printf("%d", Aux[i]);
    printf(" ");

    t = 0;
    for( i = 1 ; i <= S[0] ; ++i )
    {
        S[i] -= ( ( i <= Aux[0] ) ? Aux[i] : 0 ) + t;
        S[i] += ( t = S[i] < 0 ) * 10;
    }
    for( ; S[0] > 1 && !S[S[0]] ; S[0]-- );
    for( i = S[0] ; i > 0 ; --i )
        printf("%d",S[i]);
    printf("\n");

}

int main()
{
    int T;
    scanf("%d", &T);
    for(int i = 1 ; i <= T ; ++i )
        Solve();
}
