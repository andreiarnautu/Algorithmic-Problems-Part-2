#include <cstdio>
using namespace std;
FILE *fin=freopen("windows.in","r",stdin);
FILE *fout=freopen("windows.out","w",stdout);
struct coord{int l1,l2,c1,c2;};
coord v[101];
int x=1,n,a[101];
int verifica(int m, int n)
{
    if(v[n].l1<=v[m].l1 && v[n].l2>=v[m].l1 && v[n].c1<=v[m].c2 && v[n].c2>=v[m].c2)
        return 1;
    return 0;
}
void inchide(int k)
{
    for(int i=k+1;i<n;i++)
        if(verifica(k,i) && !a[i])
        {
            a[i]=1;
            ++x;
            inchide(i);
        }
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d%d%d%d",&v[i].l1,&v[i].c1,&v[i].l2,&v[i].c2);
    inchide(0);
    printf("%d",x);
    return 0;
}
