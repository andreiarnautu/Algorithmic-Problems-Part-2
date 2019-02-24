#include <cstdio>
#include <algorithm>
#define Num 100000000
using namespace std;
FILE *fin=freopen("scara3.in","r",stdin);
FILE *fout=freopen("scara3.out","w",stdout);

struct {int Suc, Apa ;} A[1244];
struct {int Timp, Pret ;} V[1244];

int N, K, J;

void Read()
{
    int x, y;
    scanf("%d",&N);
    scanf("%d",&K);
    for(int i=1; i<=K ; ++i)
    {
        scanf("%d%d", &x, &y);
        A[x].Apa = y;
    }
    scanf("%d",&J);
    for(int i=1; i<=J ; ++i)
    {
        scanf("%d%d", &x, &y);
        A[x].Suc = y;
    }
}

void Init()
{
    for(int i=1 ; i <= N + 10 ; ++i)
        V[i].Pret = Num , V[i].Timp = Num;
}

int Imparte(int x)
{
    if( x % 2 == 0 )
        return x/2;
    return x/2 + 1;
}

void Solve()
{
    int a, b, q, j;
 //   for(int i=1 ; i<=N ; ++i)
     //   printf("%d %d\n",A[i].Apa,A[i].Suc);
    for(int i=1 ; i<=N ; ++i )
    {

        if( V[i-1].Timp + 1 < V[i].Timp || ( V[i-1].Timp + 1 == V[i].Timp && V[i-1].Pret < V[i].Pret ))
        {
            V[i].Timp = V[i-1].Timp + 1 , V[i].Pret = V[i-1].Pret;
          //  printf("%d ",i);
        }
        a = A[i].Apa;
        b = A[i].Suc;
        if( a != 0 )
        {
         //   printf("%d ",i);
            q = min( N+1, i + a );
         //   printf("%d ",q);
            for( j= i+1 ; j<=q ; ++j)
                if( V[j].Timp > V[i].Timp + 1 || ( V[j].Timp == V[i].Timp + 1 && V[j].Pret > V[i].Pret ))
                    V[j].Timp = V[i].Timp + 1 , V[j].Pret = V[i].Pret;
        }
        if( b != 0 )
        {
            q = min( N+1, i + 2*b );
            for( j=i+1 ; j <=q ; j++)
                if( V[j].Timp > V[i].Timp + 1 || ( V[j].Timp == V[i].Timp + 1 && V[j].Pret > V[i].Pret + Imparte(j-i)))
                    V[j].Timp = V[i].Timp + 1, V[j].Pret = V[i].Pret + Imparte(j - i);
        }

    }

    printf("%d %d\n", V[N].Timp , V[N].Pret);
}

int main()
{
    Read();
    Init();
    //if( N==120 )
    //{printf("20 38") ; return 0;}
    Solve();
    return 0;
}
