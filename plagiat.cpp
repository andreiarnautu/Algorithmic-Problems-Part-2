#include <cstdio>
#include <algorithm>
#include <cmath>
#define Nmax 403
using namespace std;
FILE *fin=freopen("plagiat.in","r",stdin);
FILE *fout=freopen("plagiat.out","w",stdout);

struct {int x, y;} P[Nmax];
struct line{ double Angle, Length;} S[Nmax * Nmax];
int N, K;

void Read()
{
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
        scanf("%d%d", &P[i].x, &P[i].y);
}

int cmp(line a, line b)
{
    if( a.Angle < b.Angle )
        return 0;
    else if( a.Angle == b.Angle && a.Length < b.Length )
        return 0;
    return 1;
}

void Solve()
{
    K = 0;
    for(int i = 1 ; i < N ; ++i )
        for(int j = i + 1 ; j <= N ; ++j )
        {
            ++K;
            if(P[i].y == P[j].y)
                S[K].Angle = 696969;
            else if(P[i].x == P[j].x)
                S[K].Angle = 69696969;
            else
                S[K].Angle = (P[i].y - P[j].y) / (P[i].x - P[j].x);
            S[K].Length = sqrt( (double) (P[i].y - P[j].y) * (P[i].y - P[j].y) + (P[i].x - P[j].x) * (P[i].x - P[j].x) );
        }
   sort( S + 1 , S + K + 1 , cmp);
   //for(int i = 1 ; i <= K ; ++i )
     //   printf("%.3f %.3f\n", S[i].Angle, S[i].Length);
    for(int i = 1 ; i + 2 <= K ; ++i )
    {
        if( S[i].Angle == S[i + 1].Angle && S[i].Angle == S[i + 2].Angle && S[i].Length == S[i + 1].Length && S[i].Length == S[i + 2].Length)
        {
           // printf("%d ",i);
            printf("DA\n");
            return;
        }
    }
    printf("NU\n");
}

int main()
{
    int T;
    scanf("%d", &T);
    for(int i = 1 ; i <= T ; ++i )
    {
        Read();
        Solve();
    }
}
