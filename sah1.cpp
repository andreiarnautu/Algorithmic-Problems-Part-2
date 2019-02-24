#include <cstdio>
#include <algorithm>
#define Dim 101
using namespace std;
FILE *fin = freopen("sah1.in","r",stdin);
FILE *fout = freopen("sah1.out","w",stdout);

int N, P, A[Dim][Dim], Max, Sol, Lin[4 * Dim], Col[4 * Dim];

void Color(int x, int y)
{
    int i, j, k;
    A[x][y] = - 1;
    k = min(x, y);
    for(int i = 1 ; i < k ; ++i )
        if( A[x - i][y - i] != -1 )
        {
            if( ++A[x - i][y - i] > Max )
                    Max = A[x - i][y - i];
        }
        else
            break;

    for(int i = 1 ; i < x ; ++i )
        if( A[x - i][y] != -1 )
        {
            if( ++A[x - i][y] > Max )
                Max = A[x - i][y];
        }
        else
            break;

    k = min( x, N + 1 - y);
    for(int i = 1 ; i < k ; i++ )
        if( A[x - i][y + i] != -1 )
        {
            if( ++A[x - i][y + i] > Max )
                Max = A[x - i][y + i];
        }
        else
            break;

    k = min( N + 1 - x , N + 1 - y);
    for(int i = 1 ; i < k ; ++i )
        if( A[x + i][y + i] != -1 )
        {
            if( ++A[x + i][y + i] > Max )
                Max = A[x + i][y + i];
        }
        else
            break;

    for(int i = 1 ; i < N - x + 1 ; ++i )
        if( A[x + i][y] != -1 )
        {
            if( ++A[x + i][y] > Max )
                Max = A[x + i][y];
        }
        else
            break;

    k = min ( N - x + 1 , y );
    for(int i = 1 ; i < k ; ++i )
        if( A[x + i][y - i] != -1 )
        {
            if( ++A[x + i][y - i] > Max )
                Max = A[x + i][y - i];
        }
        else
            break;

    for(int i = 1 ; i < y ; ++i )
        if( A[x][y - i] != -1 )
        {
            if( ++A[x][y - i] > Max )
                Max = A[x + i][y - i];
        }
        else
            break;
    for(int i = 1 ; i + y <= N ; ++i )
        if( A[x][y + i] != -1 )
        {
            if( ++A[x][y + i] > Max )
                Max = A[x][y + i];
        }
        else
            break;
}

void Read()
{
    int x, y;
    scanf("%d%d", &N, &P);
    for(int i = 1 ; i <= P ; ++i )
    {
        scanf("%d%d", &Lin[i], &Col[i]);
        A[Lin[i]][Col[i]] = -1;
    }
    for(int i = 1 ; i <= P ; ++i )
        Color(Lin[i], Col[i]);
  /*  for(int i = 1 ; i <= N ; ++i )
    {
        for(int j = 1 ; j <= N ; ++j )
            printf("%d ",A[i][j]);
        printf("\n");
    }*/
}

void Solve()
{
    int pos, q, poz, ok;
    for(int i = 1 ; i <= N ; ++i )
        for(int j = 1 ; j <= N ; ++j )
            if( Max == A[i][j] )
            {
                pos = 0;
                poz = 0;
                ok = 0;
              //  printf("%d %d\n",i , j);
                for( q = 1 ; q < i && q <j ; ++q )
                {
                    if( A[i - q][j - q] == -1 )
                    {
                        ok = 1;
                        break;
                    }
                    else
                        ++poz;
                }
                if( ok )
                    pos += poz;
                ok = 0;
                poz = 0;
                for( q = 1 ; q < i ; ++q )
                {
                    if( A[i - q][j] == -1 )
                    {
                        ok = 1;
                        break;
                    }
                    else
                        ++poz;
                }
                if( ok )
                    pos += poz;
                ok = 0;
                poz = 0;
                for( q = 1 ; q < i && q + j <= N ; ++q )
                {
                    if( A[i - q][j + q] == -1 )
                    {
                        ok = 1;
                        break;
                    }
                    else
                        ++poz;
                }
                if( ok )
                    pos += poz;
                ok = 0;
                poz = 0;
                for( q = 1 ; q + j <= N ; ++q )
                {
                    if( A[i][j + q] == -1 )
                    {
                        ok = 1;
                        break;
                    }
                    else
                        ++poz;
                }
                if( ok )
                    pos += poz;
                ok = 0;
                poz = 0;
                for( q = 1 ; q + i <= N && q + j <= N ; ++q )
                {
                    if( A[i + q][j + q] == -1 )
                    {
                        ok = 1;
                        break;
                    }
                    else
                        ++poz;
                }
                if( ok )
                    pos += poz;
                ok = 0;
                poz = 0;
                for( q = 1 ; q + i <= N ; ++q )
                {
                    if( A[q + i][j] == -1 )
                    {
                        ok = 1 ;
                        break;
                    }
                    else
                        ++poz;
                }
                if( ok )
                    pos += poz;
                ok = 0;
                poz = 0;
                for( q = 1 ; q + i <= N && j - q > 0 ; ++q )
                {
                    if( A[i + q][j - q] == -1 )
                    {
                        ok = 1;
                        break;
                    }
                    else
                        ++poz;
                }
                if( ok )
                    pos += poz;
                ok = 0;
                poz = 0;
                for( q = 1 ; j - q > 0 ; ++q )
                {
                    if( A[i][j - q] == -1 )
                    {
                        ok = 1;
                        break;
                    }
                    else
                        ++poz;
                }
                if( ok )
                    pos += poz;
                ok = 0;
                poz = 0;
                Sol += N * N - pos - P - 1;
            }
    printf("%d",Sol);
}

int main()
{
    Read();
    Solve();
    return 0;
}
