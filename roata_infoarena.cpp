#include <cstdio>
#include <algorithm>
#define MaxP 100013
#define MaxN 363

using namespace std;

FILE *fin=freopen("roata.in","r",stdin);
FILE *fout=freopen("roata.out","w",stdout);

int n, p, vmin, pos;
long long int money;
int V[MaxP];
struct noname{int R, No, Position, Cabina;} A[MaxN], B[MaxN];



void Read_and_First()
{
    scanf("%d%d", &n, &p);
    for(int i = 1 ; i <= p ; ++i )
    {
        scanf("%d", &V[i]);
        money = 1ll * (money + V[i]);
    }

    printf("%lld\n", money);
}

void Find_minimum()
{
    vmin = MaxP;

    for(int i = 1 ; i <= n ; ++i )
    {
        if( A[i].R < vmin )
        {
            vmin = A[i].R;
            pos = i;
        }
        else if( vmin == A[i].R && (n + 1 - i) % n < (n + 1 - pos) % n )
            pos = i;
    }

}

void Lower_Values()
{
    for(int i = 1 ; i <= n ; ++i )
        A[i].R -= vmin;
}

void Shift_Right()
{
    int number, aux;
    number = (n + 1 - pos) % n;

    for(int i = 1 ; i <= n ; ++i )
    {
        aux = i - number;
        if( aux < 1 )
            aux += n;
        B[i].R = A[aux].R , B[i].No = A[aux].No, B[i].Cabina = A[aux].Cabina;
    }

    for(int i = 1 ; i <= n ; ++i )
        A[i].R = B[i].R , A[i].No = B[i].No, A[i].Cabina = B[i].Cabina;

}

inline int cmp(noname q1, noname q2)
{
    if( (q1.R > q2.R ) || (q1.R == q2.R && (n + 1 - q1.Position) % n > (n + 1 - q2.Position) % n ) )
        return 0;
    return 1;
}

void Second_and_Third()
{

    for(int i = 1 ; i <= min(n, p) ; ++i )
        A[i].No = i , A[i].R = V[i], A[i].Cabina = i;


    for(int i = min(n, p) ; i > 0 ; --i )
        A[i].Cabina =  i , A[i].No = min(n, p) - i + 1, A[i].R = V[A[i].No];

    if( n <= p )
    for(int i = min(n, p) ; i <= p ; ++i )
    {
        Find_minimum();
        Lower_Values();
        Shift_Right();
        if( i < p )
        {
            printf("%d ", A[1].No);
            //printf("\n");
            A[1].No = i + 1 , A[1].R = V[i + 1];
           // for(int j = 1 ; j <= n ; ++j )
              //  printf("%d %d\n", A[j].R, A[j].No);
        }
        //printf("%d\n", vmin);
    }

    for(int i = 1 ; i <= min(n, p) ; ++i )
        A[i].Position = i;

    sort( A + 1, A + min(p, n) + 1, cmp);

    for(int i = 1 ; i <= min(n, p) ; ++i )
        printf("%d ", A[i].No);

    printf("\n%d",A[min(n, p)].Cabina);
}

int main()
{
    Read_and_First();
    Second_and_Third();
    return 0;
}
