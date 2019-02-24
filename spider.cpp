#include <cstdio>
#define Dim 1003
#define Inf 1000000000

using namespace std;

FILE *fin=freopen("spider.in","r",stdin);
FILE *fout=freopen("spider.out","w",stdout);

int M, N, A[Dim][Dim], Best[Dim][Dim][5], MaxJumps, X, Y , last, cnt;
short Direction[Dim][Dim][5];


void Read()
{
    scanf("%d%d", &M, &N);
    for(int i = 1 ; i <= M ; ++i )
        for(int j = 1; j <= N ; ++j )
            scanf("%d", &A[i][j] );
}

void Check(int x , int y, int dir )
{
    int nx, ny, nd, Min = Inf;

    if( A[x - 1][y] <= A[x][y] && A[x][y] - A[x - 1][y] < Min && dir != 1 )
    {
        Min = A[x][y] - A[x - 1][y];
        nx = x - 1;
        ny = y;
        nd = 3;
    }

    if( A[x][y + 1] <= A[x][y] && A[x][y] - A[x][y + 1] < Min && dir != 2 )
    {
        Min = A[x][y] - A[x][y + 1];
        nx = x;
        ny = y + 1;
        nd = 4;
    }

    if( A[x + 1][y] <= A[x][y] && A[x][y] - A[x + 1][y] < Min && dir != 3 )
    {
        Min = A[x][y] - A[x + 1][y];
        nx = x + 1;
        ny = y;
        nd = 1;
    }

    if( A[x][y - 1] <= A[x][y] && A[x][y] - A[x][y - 1] < Min && dir != 4 )
    {
        Min = A[x][y] - A[x][y - 1];
        nx = x;
        ny = y - 1;
        nd = 2;
    }

    if( Min == Inf )
        Best[x][y][dir] = 1;

    else
    {
        if( !Best[nx][ny][nd] )
            Check(nx , ny , nd );
        Best[x][y][dir] = Best[nx][ny][nd] + 1;

        if( nd == 1 )
            Direction[x][y][dir] = 3;
        else if( nd == 2 )
            Direction[x][y][dir] = 4;
        else if( nd == 3 )
            Direction[x][y][dir] = 1;
        else if( nd == 4 )
            Direction[x][y][dir] = 2;

    }

    ++cnt;

}

void Solve_it()
{
    for(int i = 1 ; i <= N ; ++i )
        A[0][i] = A[M + 1][i] = Inf;

    for(int i = 1 ; i <= M ; ++i )
        A[i][0] = A[i][N + 1] = Inf;

    for(int i = 1 ; i <= M ; ++i )
        for(int j = 1 ; j <= N ; ++j )
        {
            Check( i , j, 0 );
            //--Best[i][j][0];
            if( MaxJumps < Best[i][j][0] )
            {
                MaxJumps = Best[i][j][0] ;
                X = i;
                Y = j;
            }
        }

    //printf("%d ", Best[5][4][0]);

    printf("%d\n", MaxJumps - 1);

    for(int i = MaxJumps ; i > 0 ;  --i )
    {
        printf("%d %d\n", X , Y);
        if( Direction[X][Y][last] == 1 )
        {
            --X;
            last = 3;
        }
        else if( Direction[X][Y][last] == 2 )
        {
            ++Y;
            last = 4;
        }
        else if( Direction[X][Y][last] == 3 )
        {
            ++X;
            last = 1;
        }
        else if( Direction[X][Y][last] == 4 )
        {
            --Y;
            last = 2;
        }
    }

}

int main()
{
    Read();
    Solve_it();
}
