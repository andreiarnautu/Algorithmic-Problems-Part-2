#include <fstream>
using namespace std;
ifstream in("prieteni.in");
ofstream out("prieteni.out");
short n,f[65535];
long long i,j,x,s,xx,v[100],af[70000],k=0;
void ciur()
{
    for(i=4;i<=65535;i+=2)
        f[i]=1;
    for(i=3;i<=65535;i+=2)
        if(f[i]==0)
            for(j=i*3;j<=65535;j+=2*i)
                f[j]=1;
}
int cmmdc(long long a,long long b)
{
    long long r;
    r=a%b;
    while(r!=0)
    {
        a=b;
        b=r;
        r=a%b;
    }
    return b;
}
int main()
{
    in>>n;
    ciur();
    for(i=0;i<n;i++)
    {
        in>>v[i];
        f[v[i]]=2;
    }
    for(i=0;i<n;i++)
    {
        x=v[i];
        xx=x;
        s=0;
        while(xx)
        {
            s+=xx%10;
            xx/=10;
        }
       // out<<s<<endl;
        if(cmmdc(x,s)==1)
            for(j=s;j<=x;j++)
                if(f[j]==0)
                {
                    af[k]=j;
                   // out<<k<<" "<<af[k]<<endl;
                    ++k;
                    f[j]=2;
                }
        af[k]=x;
      //  out<<af[k]<<endl;
        ++k;
    }
    out<<k<<'\n';
    for(i=0;i<k;i++)
        out<<af[i]<<" ";
    return 0;
}
