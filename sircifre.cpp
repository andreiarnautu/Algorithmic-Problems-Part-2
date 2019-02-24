#include <cstdio>
#include <cmath>
using namespace std;
FILE *fin=freopen("sircifre.in","r",stdin);
FILE *fout=freopen("sircifre.out","w",stdout);
int N, V[501], F[11];
void Read()
{
    scanf("%d",&N);
    for(int i=1; i<=N; ++i)
    {
        scanf("%d",&V[i]);
        F[V[i]]+=1;
    }
}
void Solve()
{
    bool ok=1;
    int i;
    while(ok)
    {
        ok=0;
        for(i=1; i<N ; ++i)
            if( abs(V[i]-V[i+1])==1 )
            {
                ok=1;
                F[V[i]]-=1;
                F[V[i+1]]-=1;
                break;
            }
        if(ok)
        {
            for(int j=i; j<N-1 ; ++j)
                V[j]=V[j+2];
            N-=2;
        }
    }
  //  for(int i=1; i<=N ; ++i)
  //      ++F[V[i]];
    ok=0;
    for(int i=0; i<10 ; ++i)
        if(F[i])
        {
            ok=1;
            printf("%d %d\n",i,F[i]);
        }
    if(!ok)
        printf("-1");
}
int main()
{
    Read();
    Solve();
    return 0;
}
