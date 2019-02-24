#include <cstdio>
using namespace std;
FILE *fin=freopen("raze.in","r",stdin);
FILE *fout=freopen("raze.out","w",stdout);
int t,m,n;
int a[136][136];
void citeste()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&a[i][j]);
}
void umple()
{
    int i,j;
    for(i=1;i<n-1 && i<m-1;i++)
    {
        if(a[i][i]!=1)
        {
            if(a[i][i]==0)
                a[i][i]=2;
            else
                ++a[i][i];
        }
        else
            break;
    }
    for(i=1;i<n-1 && m-i-1>0;i++)
    {
        if(a[i][m-1-i]!=1)
        {
            if(a[i][m-i-1]==0)
                a[i][m-i-1]=2;
            else
                ++a[i][m-i-1];
        }
        else
            break;
    }
    for(i=n-2;i>0 && n-i<m-1;i--)
    {
        if(a[i][n-i+-1]!=1)
        {
            if(a[i][n-i-1]==0)
                a[i][n-i-1]=2;
            else
                ++a[i][n-i-1];
        }
        else
            break;
    }
    for(i=n-1;i>0 && m+i-n>0;i--)
    {
        if(a[i][m+i-n]!=1)
        {
            if(a[i][m+i-n]==0)
                a[i][m+i-n]=2;
            else
                ++a[i][m+i-n];
        }
        else
            break;
    }
    for(i)
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }
}
int main()
{
    int i,j;
    scanf("%d",&t);
    for(i=0;i<t;i++)
    {
        citeste();
        umple();
    }
    return 0;
}
