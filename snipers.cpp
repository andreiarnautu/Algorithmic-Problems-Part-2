#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
FILE *fin=freopen("snipers.in","r",stdin);
FILE *fout=freopen("snipers.out","w",stdout);
int N;
struct{int x, y;} P1[203], P2[203];
int T[203];

void Read()
{
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%d%d", &P1[i].x, &P1[i].y);
        T[i] = i;
    }
    for(int i = 1 ; i <= N ; ++i )
        scanf("%d%d", &P2[i].x, &P2[i].y);
}

int Intersection(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    double a, b, c, d;
    a = sqrt((double)(x1-x2) * (x1-x2) + (y1-y2) * (y1-y2));
    b = sqrt((double)(x3-x4) * (x3-x4) + (y3-y4) * (y3-y4));
    c = sqrt((double)(x1-x4) * (x1-x4) + (y1-y4) * (y1-y4));
    d = sqrt((double)(x3-x2) * (x3-x2) + (y3-y2) * (y3-y2));
    if( a + b < c + d )
        return 0;
    return 1;
}

void Solve()
{
    int i, j, ok, inter;
    if( N == 1 )
        return;
    do
    {
        ok = 1;
        i = 1;
        do
        {
            j = i;
            do
            {
                ++j;
                inter = Intersection(P1[i].x, P1[i].y, P2[T[i]].x, P2[T[i]].y, P1[j].x, P1[j].y, P2[T[j]].x, P2[T[j]].y );
                if( inter )
                {
                    ok = 0;
                    swap(T[i], T[j]);
                }
            }while( j < N && !inter );
            if(!inter)
                ++i;
        }while(i < N);
    }while(!ok);
    for(int i = 1 ; i <= N ; ++i )
        printf("%d\n",T[i]);
}

int main()
{
    Read();
    Solve();
//    Write();
    return 0;
}
