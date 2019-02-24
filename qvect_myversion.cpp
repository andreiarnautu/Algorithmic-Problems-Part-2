#include <cstdio>
#include <algorithm>

using namespace std;

FILE *fin=freopen("qvect.in","r",stdin);
FILE *fout=freopen("qvect.out","w",stdout);


int A[101][5001], N , Q, No[101];


void Read()
{
    scanf("%d%d", &N, &Q);
    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%d", &A[i][0]);
        No[i] = No[i - 1] + A[i][0];
        for(int j = 1 ; j <= A[i][0] ; ++j )
            scanf("%d", &A[i][j]);
    }
}


void Solve1(int x, int y)
{
    int Min = 2000000000 , p1 , p2 , Diff ;
    p1 = p2 = 1;

    while( p1 <= A[x][0] && p2 <= A[y][0] )
    {
        if( A[x][p1] > A[y][p2] )
            Diff = A[x][p1] - A[y][p2];
        else
            Diff = A[y][p2] - A[x][p1];
        if( Diff < Min )
            Min = Diff;
        if( A[x][p1] < A[y][p2] )
            ++p1;
        else
            ++p2;
        if( Min == 0 )
        {
            printf("0\n");
            return;
        }
    }

    printf("%d\n", Min);
}


int Search(int val, int x )
{
    int st = 1 , dr = A[x][0] + 1 , m;
    while( st + 1 < dr )
    {
        m = (st + dr) / 2;
        if( A[x][m] < val )
            st = m;
        else
            dr = m;
    }
    return st;
}

void Solve2(int x, int y)
{
    int st , dr , m, pos, nr, i , ok = 0, q, retine, sol;
    st = -1000000000;
    dr =  1000000000;
    pos = ( No[y] - No[x - 1] ) / 2;

    while( st <= dr )
    {
        m = (st + dr) / 2;
        nr = 0;
        ok = 0;
        for( i = x ; i <= y ; ++i )
        {
            q = upper_bound(A[i] + 1 , A[i] + A[i][0] + 1 , m ) - A[i] - 1; ;
            if( A[i][q] == m )
            {
                ok = 1;
                retine = m;
            }
            nr += q;
        }

        if( nr >= pos )
        {
            if(ok)
            {
                sol = retine;
                if(nr == pos)
                    break;
            }
            dr = m - 1;
        }
        else
            st = m + 1;
    }

    printf("%d\n", sol);
}

int main()
{
    Read();

    int Task, a, b;

    for(int i = 1 ; i <= Q ; ++i )
    {
        scanf("%d%d%d", &Task, &a, &b);
        if( Task == 1 )
            Solve1( a , b );
        else
            Solve2( a , b );
    }
}
