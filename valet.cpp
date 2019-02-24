#include <cstdio>
#include <queue>
using namespace std;
FILE *fin=freopen("valet.in","r",stdin);
FILE *fout=freopen("valet.out","w",stdout);

const int dx[] = {-1, 1, 0, 0};
const int dy[] = { 0, 0,-1, 1};

struct coord{int x1, y1, x2, y2;};
queue <coord> Q;
int n, m, a1, b1, a2, b2;
int F[7000000];
int A[60][60];
char s[60];

void Read()
{
    scanf("%d %d ", &n, &m);

    for(int i = 1; i <= n; ++i)
    {
        scanf("%s ", s);
        for(int j = 0; j < m ; ++j)
        {
            if( s[j] == '#' )
                A[i][j + 1] = -1;
            else if( s[j] == '.' )
                a1 = i, b1 = j + 1;
            else if( s[j] == 'X' )
                a2 = i, b2 = j + 1;
        }
    }
}

inline int config(int q1, int q2, int q3, int q4)
{
    return q1 + q2 * 51 + q3 * 51 * 51 + q4 * 51 * 51 * 51;
}

void Solve()
{
    coord aux, aux2;
    int val, X1, Y1, X2, Y2;

    aux.x1 = a1, aux.y1 = b1, aux.x2 = a2, aux.y2 = b2;
    F[config(aux.x1, aux.y1, aux.x2, aux.y2)] = 1;

    Q.push(aux);

    while( !Q.empty() )
    {
        aux = Q.front(); Q.pop();
        val = F[config(aux.x1, aux.y1, aux.x2, aux.y2)];
        if( aux.x2 == 1 && aux.y2 == 1 )
        {
            printf("%d", val - 1);
            return;
        }

        for(int i = 0; i < 4; ++i)
        {
            X1 = aux.x1 + dx[i];
            Y1 = aux.y1 + dy[i];
            if( X1 > 0 && Y1 > 0 && X1 <= n && Y1 <= m && A[X1][Y1] != -1 )
            {
                if( X1 == aux.x2 && Y1 == aux.y2 )
                    X2 = aux.x1, Y2 = aux.y1;
                else
                    X2 = aux.x2, Y2 = aux.y2;

                if( !F[config(X1, Y1, X2, Y2)] )
                {
                    aux2.x1 = X1, aux2.x2 = X2, aux2.y1 = Y1, aux2.y2 = Y2;
                    Q.push(aux2);
                    F[config(X1, Y1, X2, Y2)] = 1 + val;
                }
            }

        }

    }

    printf("imposibil");
}


int main()
{
    Read();
    Solve();
    return 0;
}
