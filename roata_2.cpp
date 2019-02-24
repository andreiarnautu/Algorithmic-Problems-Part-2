#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("roata.in");
ofstream out("roata.out");
long long x,p,maxim,pers[361],nrc[361],gasit,t[100001],minim,n;
long long v[361];
unsigned long long int s;
void gaseste()
{
    long long i;
    minim=1000011;
    for(i=1;i<=n;i++)
        if(v[i]<minim)
        {
            minim=v[i];
            gasit=i;
        }
}
void sorteaza(long long q)
{
    bool ok;
    long long aux,i;
    do
    {
        ok=0;
        for(i=1;i<q;i++)
            if(v[i]>v[i+1])
            {
                ok=1;
                aux=v[i];
                v[i]=v[i+1];
                v[i+1]=aux;
                aux=pers[i];
                pers[i]=pers[i+1];
                pers[i+1]=aux;
                aux=nrc[i];
                nrc[i]=nrc[i+1];
                nrc[i+1]=aux;

            }
    }while(ok);
}
int main()
{
    long long i,j,aux;
    in>>n>>p;
    if(n>=p)
    {
        for(i=1;i<=p;i++)
        {
            in>>v[i];
            pers[i]=i;
            s+=v[i];
        }
        sorteaza(p);
        out<<s<<'\n';
        for(i=1;i<=p;i++)
            out<<pers[i]<<" ";
        out<<'\n'<<pers[p];
        return 0;
    }
    for(i=1;i<=p;i++)
    {
        in>>t[i];
        s+=t[i];
    }
    out<<s<<'\n';
    for(i=1;i<=n;i++)
    {
        v[i]=t[i];
        nrc[i]=i;
        pers[i]=i;
    }
    i=n+1;
    while(i<=p)
    {
        gaseste();
        for(j=1;j<=n;j++)
        {
            if(v[j]==minim)
            {
                v[j]+=t[i];
                out<<pers[j]<<" ";
                if(i<=p)
                    pers[j]=i;
                else
                    pers[j]=-1;
                ++i;
            }
        }
        if(minim>1000000)
            for(j=1;j<=n;j++)
                v[j]-=1000000;
    }
    sorteaza(n);
    for(i=1;i<=n;i++)
        if(pers[i]!=-1)
            out<<pers[i]<<" ";
    out<<'\n'<<nrc[n];
    return 0;
}
