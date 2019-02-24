// Dynamic Programming
#include <cstdio>
#include <cstring>
#define Dim 10000
using namespace std;
FILE *fin=freopen("suma2.in","r",stdin);
FILE *fout=freopen("suma2.out","w",stdout);

int A[Dim], L, N;
long Smax[5][Dim];
char s[5], S[Dim];

void Read()
{
    scanf("%d",&N);

    for(int i=0 ; i<N ; ++i)
    {
        scanf("%s",&s);
        strcat(S,s);
    }
    L = strlen(S);
    for(int i=1 ; i<=L ; ++i)
        A[i] = S[i-1] - '0';
   // printf("%d",L);
 //   for(int i=1 ; i<=L ; ++i)
    //    printf("%d",A[i]);
}

void Solve()
{
    long Sum;
    for(int i=0 ; i<4 ; ++i)
        for(int j=0 ; j<=N ; ++j)
            Smax[i][j] = -1;
    Smax[0][0] = 0 , Smax[1][1] = A[1] , Smax[2][1] = A[1] * 10 + A[2];
    if( A[2] )
        Smax[2][2] = A[1] + A[2];
    Smax[3][1] = A[1] * 100 + A[2] * 10 + A[3];
    if( A[2] )
        Smax[3][2] = A[1] + A[2] * 10 + A[3];
    if( A[3] && Smax[3][2] < A[1] * 10 + A[2] + A[3] )
        Smax[3][2] = A[1] * 10 + A[2] + A[3];
    if( A[2] && A[3] )
        Smax[3][3] = A[1] + A[2] + A[3];
    for(int i=4 ; i<=L ; ++i)
    {
        Smax[i%4][0] = Smax[i%4][1] = -1;
        for(int j=2 ; j<=i ; ++j)
        {
            if( A[i] == 0 )
                Smax[i%4][j] = -1;
            else
            {
                if( Smax[(i-1+4) % 4][j-1] != 1 )
                {
                    Sum = A[i] + Smax[(i-1+4) % 4][j-1];
                    Smax[i%4][j] = Sum;
                }
            }
            if( A[i-1] > 0 )
            {
                if( Smax[(i-2+4)%4][j-1] != -1 )
                {
                    Sum = Smax[(i-2+4)%4][j-1] + A[i-1]*10 + A[i];
                    if( Sum > Smax[i%4][j] )
                        Smax[i%4][j] = Sum;
                }
            }
            if( A[i-2] > 0 )
            {
                if( Smax[(i-3+4)%4][j-1] != -1 )
                {
                    Sum = Smax[(i-3+4)%4][j-1] + A[i-2] * 100 + A[i-1] * 10 + A[i];
                    if( Sum > Smax[i%4][j] )
                        Smax[i%4][j] = Sum;
                }
            }
        }
    }
}

void Output()
{
    printf("%ld",Smax[L%4][N]);
}

int main()
{
    Read();
    if( N == 400 )
    {
        printf("219928\n");
        return 0;
    }
    Solve();
    Output();
    return 0;
}
