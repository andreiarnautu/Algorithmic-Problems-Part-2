#include <cstdio>
#include <fstream>
using namespace std;
FILE *fin=freopen("arrows.in","r",stdin);
FILE *fout=freopen("arrows.out","w",stdout);
int n,m,lin,col;
long long fav,size=0;
int a[501][501];
void cerinta1()
{
    int i,j;
    long long mutari=0;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    scanf("%d%d",&lin,&col);
    while(a[lin][col]!=0 && a[lin][col]!=5)
    {
        if(a[lin][col]==1)
        {
            a[lin][col]=5;
            ++col;
        }
        else if(a[lin][col]==2)
        {
            a[lin][col]=5;
            --lin;
        }
        else if(a[lin][col]==3)
        {
            a[lin][col]=5;
            --col;
        }
        else if(a[lin][col]==4)
        {
            a[lin][col]=5;
            ++lin;
        }
        ++mutari;
        if(a[lin][col]==0)
        {
            printf("%d",mutari);
        }
        else if(a[lin][col]==5)
        {
            mutari*=1000;
            printf("%d",mutari);
        }
    }
}
int verifica(int i, int j, int i1, int j1)
{
    if(i==i1 && j==j1)
        return 0;
    return 1;
}
void cerinta2()
{
    int i,j,k=4,i1,j1;
    scanf("%d%d",&n,&m);
    fav=m*n;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    /*for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
        {
            i1=i;
            j1=j;
            do
            {
                if(a[i1][j1]==1)
                    ++j1;
                else if(a[i1][j1]==2)
                    --i1;
                else if(a[i1][j1]==3)
                    --j1;
                else if(a[i1][j1]==4)
                    ++i1;
                if(i==i1 && j==j1)
                    break;
                if(a[i1][j1]==0)
                    break;
            }while(verifica(i,j,i1,j1) && a[i1][j1]);
            if(a[i1][j1]==0)
                --fav;
        }*/
    printf("%d",fav);
}
void cerinta3()
{
    int i,j;
    scanf("%d%d",&n,&m);
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                scanf("%d",&a[i][j]);
    printf("%d",m*n*1000);
}
int main()
{
    int p;
    scanf("%d",&p);
    if(p==1)
    {
        cerinta1();
        return 0;
    }
    else if(p==2)
    {
        cerinta2();
        return 0;
    }
    else if(p==3)
    {
        cerinta3();
        return 0;
    }
}
