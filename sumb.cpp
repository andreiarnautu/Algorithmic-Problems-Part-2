#include <cstdio>
#include <cstring>
#define Dim 230
using namespace std;
FILE *fin = freopen("sumb.in","r",stdin);
FILE *fout = freopen("sumb.out","w",stdout);
int A[Dim], B[Dim], C[Dim], Sum[Dim] , Min = 0;

void Read()
{
    char s[Dim];
    gets(s);
    A[0] = strlen(s);
    for(int i = 1 ; i <= A[0] ; ++i )
    {
        A[i] = s[A[0] - i] - 48;;
        if( A[i] + 1 > Min )
            Min = A[i] + 1;
    }

    gets(s);
    B[0] = strlen(s);
    for(int i = 1 ; i <= B[0] ; ++i )
    {
        B[i] = s[B[0] - i] - 48;
        if( B[i] + 1 > Min )
            Min = B[i] + 1;
    }
    gets(s);
    C[0] = strlen(s);
    for(int i = 1 ; i <= C[0] ; ++i )
    {
        C[i] = s[C[0] - i] - 48;
        if( C[i] + 1 > Min )
            Min = C[i] + 1;
    }
}

int Base(int x)
{
    int i, t = 0;
    for( i = 0 ; i <= 210 ; ++i )
        Sum[i] = 0;
    for( i = 1 ; i <= A[0] || i <= B[0] || t ; t /= x , ++i )
        Sum[i] = ( t += A[i] + B[i] ) % x;
    Sum[0] = i - 1;
    for(int i = 0 ; i <= Sum[0] ; ++i )
        if( Sum[i] != C[i] )
            return 0;
    return 1;
}

int main()
{
    int Sol = 0;
    Read();
    if( Min == 1 )
    {
        printf("2");
        return 0;
    }
   // printf("%d", Min);
    for(int i = Min ; i <= 100 ; ++i )
        if( Base(i) )
        {
            Sol = i;
            break;
        }
    printf("%d", Sol);
    return 0;
}
