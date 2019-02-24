#include <cstdio>
using namespace std;
FILE *fin=freopen("prieteni3.in","r",stdin);
FILE *fout=freopen("prieteni3.out","w",stdout);
short w[101][101],n,A,k;
short viz[101],C[101];
void Read()
{
    scanf("%d%d%d",&n,&A,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&w[i][0]);
        for(int j=1;j<=w[i][0];j++)
            scanf("%d",&w[i][j]);
    }
}
void BFS(int x)
{
    int p,u;
    viz[x]=1;
    C[0]=x;
    p=u=0;
    while(p<=u)
    {
        x=C[p++];
        for(int i=1;i<=w[x][0];i++)
        {
            if(!viz[w[x][i]])
            {
                viz[w[x][i]]=viz[x]+1;
                C[++u]=w[x][i];
            }
            else if(viz[w[x][i]]>viz[x]+1)
                viz[w[x][i]]=viz[x]+1;
        }
    }
}
void Write()
{
    int nr=0;
    for(int i=1;i<=n;i++)
        if(viz[i]-1==k)
            ++nr;
    printf("%d\n",nr);
    for(int i=1;i<=n;i++)
        if(viz[i]-1==k)
            printf("%d ",i);
}
int main()
{
    Read();
    BFS(A);
    Write();
    return 0;
}
