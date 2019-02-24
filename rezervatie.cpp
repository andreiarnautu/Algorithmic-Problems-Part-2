#include <cstdio>
#include <cstring>
using namespace std;
FILE *fin=freopen("rezervatie.in","r",stdin);
FILE *fout=freopen("rezervatie.out","w",stdout);
short a[400][400],l,c;
int n,x,y,v[1001],k=0;
char s[10001];
int verifica()
{
    int nr=0,i;
    for(i=x;i>=0;--i)
        if(a[i][y])
            ++nr;
    if(nr%2==0)
        return 0;
    nr=0;
    for(i=x;i<=2*(l-1)+2;++i)
        if(a[i][y])
            ++nr;
    if(nr%2==0)
        return 0;
    nr=0;
    for(i=y;i>=0;--i)
        if(a[x][i])
            ++nr;
    if(nr%2==0)
        return 0;
    nr=0;
    for(i=y;i<=2*(c-1)+2;++i)
        if(a[x][i])
            ++nr;
    if(nr%2==0)
        return 0;
    return 1;
}
int main()
{
    int j,i;
    scanf("%d%d",&l,&c);
    getchar();
    gets(s);
    if(s[0]=='S')
    {
        x=1;
        a[x][y]=1;
    }
    else
    {
        y=1;
        a[x][y]=1;
    }
    for(i=1;i<strlen(s);i++)
    {
        if(s[i]=='S')
        {
            if(s[i-1]=='S' || s[i-1]=='N')
                x+=2;
            if(s[i-1]=='E')
            {
                ++x;
                ++y;
            }
            if(s[i-1]=='V')
            {
                ++x;
                --y;
            }
        }
        if(s[i]=='N')
        {
            if(s[i-1]=='N' || s[i-1]=='S')
                x-=2;
            if(s[i-1]=='E')
            {
                --x;
                ++y;
            }
            if(s[i-1]=='V')
            {
                --x;
                --y;
            }
        }
        if(s[i]=='E')
        {
            if(s[i-1]=='E' || s[i-1]=='V')
                y+=2;
            if(s[i-1]=='S')
            {
                ++x;
                ++y;
            }
            if(s[i-1]=='N')
            {
                --x;
                ++y;
            }
        }
        if(s[i]=='V')
        {
            if(s[i-1]=='E' || s[i-1]=='V')
                y-=2;
            if(s[i-1]=='S')
            {
                ++x;
                --y;
            }
            if(s[i-1]=='N')
            {
                --x;
                --y;
            }
        }
        a[x][y]=1;
    }
 /*   for(i=0;i<=2*l+1;++i)
    {
        for(j=0;j<=2*c+1;++j)
            printf("%d ",a[i][j]);
        printf("\n");
    }*/
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d%d",&x,&y);
        x=2*(x-1)+1;
        y=2*(y-1)+1;
        if(verifica())
            v[k++]=i;
    }
    printf("%d\n",k);
    for(i=0;i<k-1;i++)
        printf("%d ",v[i]);
    printf("%d",v[k-1]);
    return 0;
}
