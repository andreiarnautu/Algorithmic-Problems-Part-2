#include <cstdio>
using namespace std;
FILE *fin=freopen("suma1.in","r",stdin);
FILE *fout=freopen("suma1.out","w",stdout);
int N,V[20001],S[20001];
void Read()
{
    scanf("%d",&N);
    for(int i=1; i<=N ; ++i)
        scanf("%d",&V[i]);
}
void Solve()
{
    long sum;
    S[N]=2;
    sum=V[N];
    for(int i=N-1; i>0 ; --i)
    {
        if(sum <= V[i])
        {
            for(int j=i+1; j<=N ; ++j)
            {
                if(S[j]==1)
                    S[j]=2;
                else
                    S[j]=1;
            }
            sum=sum*(-1)+V[i];
            S[i]=2;
        }
        else
        {
            S[i]=1;
            sum-=V[i];
        }
    }
    for(int i=1; i<=N ; ++i)
        printf("%d ",S[i]);
}
int main()
{
    Read();
    Solve();
    return 0;
}
