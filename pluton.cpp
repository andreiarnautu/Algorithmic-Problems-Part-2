#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;
ifstream in("pluton.in");
ofstream out("pluton.out");
int n,f[4001];
long long v[4001],p[4001],nrp=0,s[4001];
/*int compara(long long x, long long y)
{
    int v1[10],v2[10],i;
    for(i=0;i<10;i++)
    {
        v1[i]=0;
        v2[i]=0;
    }
    while(x)
    {
        ++v1[x%10];
        x=x/10;
    }
    while(y)
    {
        ++v2[y%10];
        y/=10;
    }
    for(i=0;i<=9;i++)
    {
        //out<<v1[i]<<v2[i]<<" ";
        if(v1[i]!=v2[i])
            return 0;
    }
    return 1;
}*/
int putere(int z)
{
    long long y=1;
    while(z)
    {
        --z;
        y=y*10;
    }
    return y;
}
int id(long long x)
{
    long long y=0;
    while(x)
    {
        y=y+putere(x%10);
        x/=10;
    }
    return y;
}

void repartizare()
{
    int k,i,maxim=0,j;
    for(i=1;i<=n;i++)
    {
        if(p[i]==0)
            ++nrp;
        else
            continue;
        k=1;
        p[i]=nrp;
        for(j=i+1;j<=n;j++)
            if(s[i]==s[j])
            {
                p[j]=nrp;
                ++k;
            }
        f[nrp]=k;
    }
    out<<nrp<<'\n';
    for(i=1;i<=nrp;i++)
        if(f[i]>maxim)
            maxim=f[i];
    out<<maxim<<'\n';
    k=0;
    for(i=1;i<=nrp;i++)
        if(maxim==f[i])
        {
            j=i;
            ++k;
        }
    out<<k<<'\n';
    for(i=1;i<=n;i++)
        if(p[i]==j)
            out<<v[i]<<" ";
}
int main()
{
    int i,j;
    in>>n;
    for(i=1;i<=n;i++)
    {
        in>>v[i];
        s[i]=id(v[i]);
        //out<<s[i]<<" ";
    }
   // out<<s[4]<<endl;
    repartizare();
    return 0;
}
