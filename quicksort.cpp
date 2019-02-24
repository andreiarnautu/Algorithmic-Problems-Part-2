#include <cstdio>
using namespace std;
FILE *fin=freopen("qsort.in","r",stdin);
FILE *fout=freopen("qsort.out","w",stdout);
int n, v[1000];
int divide(int p, int q)
{
    int st,dr,x;
    st=p;
    dr=q;
    x=v[p];
    while(st<dr)
    {
        while(st<dr && v[dr]>=x)
            --dr;
        v[st]=v[dr];
        while(st<dr && v[st]<=x)
            ++st;
        v[dr]=v[st];
    }
    v[st]=x;
    return st;
}
void qsort(int p, int q)
{
    int m;
    m=divide(p,q);
    if(m-1>p)
        qsort(p,m-1);
    if(m+1<q)
        qsort(m+1,q);
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",&v[i]);
    qsort(0,n-1);
    for(int i=0;i<n;i++)
        printf("%d ",v[i]);
    return 0;
}
