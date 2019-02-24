#include <cstdio>
using namespace std;
FILE *fin=freopen("reflex.in","r",stdin);
FILE *fout=freopen("reflex.out","w",stdout);
int main()
{
    long long m,n,x,r,y,v,s,h;
    int colt[3]={2,4,3};
    scanf("%lld%lld",&n,&m);
    x=n-1;
    y=m-1;
    while(y)
    {
        r=x%y;
        x=y;
        y=r;
    }
    h=(m-1)/x;
    v=(n-1)/x;
    r=colt[v%2+h%2+h%2-1];
    s=v*(m-1);
    printf("%lld %lld\n%lld %lld",s+1,r,h-1,v-1);
    return 0;
}
