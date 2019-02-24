#include <cstdio>
#include <algorithm>
#define MaxN 1003

using namespace std;

FILE *fin=freopen("sort.in","r",stdin);
FILE *fout=freopen("sort.out","w",stdout);

int N, V[MaxN], n1, n2, n3, a, b, cnt;
int A[4][4];

int main()
{
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%d", &V[i]);
        if( V[i] == 1 )
            ++n1;
        else if( V[i] == 2 )
            ++n2;
        else
            ++n3;
    }
    if( n2 )
        a = n1 + 1;
    if( n3 )
        b = n1 + n2 + 1;

    for(int i = 1 ; i <= N ; ++i )
    {
        if( V[i] == 1 )
        {
            if( a <= i && i < b )
                ++A[1][2];
            else if( i >= b )
                ++A[1][3];
        }

        else if( V[i] == 2 )
        {
            if( i < a )
                ++A[2][1];
            else if( i >= b )
                ++A[2][3];
        }

        else
        {
            if( i < a )
                ++A[3][1];
            else if( i < b )
                ++A[3][2];
        }
    }

    cnt += min( A[1][3] , A[3][1] );
    cnt += min( A[1][2] , A[2][1] );
    cnt += min( A[2][3] , A[3][2] );
    cnt += 2 * ( max( A[1][2] , A[2][1] ) - min( A[1][2] , A[2][1] ) );

    printf("%d", cnt);
    return 0;

}
