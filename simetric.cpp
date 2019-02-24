#include <cstdio>
#include <fstream>
using namespace std;
ifstream in("simetric.in");
ofstream out("simetric.out");
FILE *fin=freopen("simetric.in","r",stdin);
FILE *fout=freopen("simetric.out","w",stdout);
int N, V[101];
void Read()
{
   // in>>N;
 //   for(int i=1; i<=N ; ++i)
   //     in>>V[i];
    scanf("%d",&N);
    for(int i=1; i<=N ; ++i)
        scanf("%d",&V[i]);
}
void Solve()
{
    int x,ok;
    x=N/2+1;
    while(x<=N)
    {
        ok=0;
        if(N-x+1<=x-1)
        {
            ok=1;
            for(int i=x; i<=N ; ++i)
                if(V[i] != V[x-(i-x+1)])
                {
                    ok=0;
                  //  printf("%d ",x);
                    break;
                }
        }
        if(ok)
        {
         //   printf("%d ",x);
            printf("%d\n",2*x-N-2);
            if(2*x-N-2==0)
                printf("\n");
            for(int i=2*x-N-2; i>0 ; i--)
                printf("%d ",V[i]);
            return;
        }
        ok=1;
        for(int i=x+1; i<=N ;++i)
            if(V[i] != V[x-(i-x)])
            {
                ok=0;
                break;
            }
        if(ok)
        {
            printf("%d\n",2*x-N-1);
            if(2*x-N-1==0)
                printf("\n");
            for(int i=2*x-N-1; i>0 ; i--)
                printf("%d ",V[i]);
            return;
        }
        ++x;
    }
}
int main()
{
    Read();
    Solve();
    return 0;
}
