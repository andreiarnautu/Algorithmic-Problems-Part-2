#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("sir4.in");
ofstream out("sir4.out");
long ok[100],v[100];
int compar(long a,long b)
{
    long ua=0,ub=0;
    while(a)
    {
        ua=a%10;
        a=a/10;
    }
    while(b)
    {
        ub=b%10;
        b=b/10;
    }
    if(ua>=ub)
        return 0;
    return 1;
}
void generare()
{
    int k=1,bine=0,n;
    while(bine==0)
    {
        n=v[k-1]*v[k-1];
        v[k]=(n/10)%100;
        ++ok[v[k]];
        if(ok[v[k]]>1)
            {bine=1;--k;break;}
        if(bine==0)
        {
            ++k;
        }
    }
    for(int i=0;i<=k;i++)
        out<<v[i]<<" ";
    out<<endl;
    sort(v,v+k+1,compar);
    for(int i=0;i<=k;i++)
        out<<v[i]<<" ";
}

int main()
{
    long k,nr=0;
    in>>k;
    k=k*k;
    nr+=(k/10)%100;
    v[0]=nr;
    ++ok[v[0]];
    generare();
    return 0;
}
