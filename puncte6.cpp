#include <fstream>
using namespace std;
ifstream in("puncte6.in");
ofstream out("puncte6.out");
long long n;
int x[250001],y[250001],poz[250000];
long long f1[1001],f2[1001],maxim;
void cerinta1()
{
    bool ok;
    long long i,j;
    for(i=1;i<=n;i++)
    {
        ++f2[y[i]];
        ++f1[x[i]];
        if(f2[y[i]]>maxim)
            maxim=f2[y[i]];
        if(f1[x[i]]>maxim)
            maxim=f1[x[i]];
    }
    out<<maxim<<'\n';
}
void cerinta2()
{
    long long n1=0,n2=0,n3=0,n4=0,n0=0,k=0,i;
    for(i=1;i<=n;i++)
    {
        if(x[i]+y[i]==0 || x[i]==y[i])
        {
            if(x[i]==0 && y[i]==0)
                n0=1;
            else if(x[i]<0 && y[i]>0)
                ++n1;
            else if(x[i]>0 && y[i]>0)
                ++n2;
            else if(x[i]>0 && y[i]<0)
                ++n3;
            else
                ++n4;
        }
    }
   // out<<n0<<n1<<n2<<n3<<n4;
    if(n0)
    {
        if((n1 && n3) || (n1 || n3))
            ++k;
        if((n2 && n4) || (n2 || n4))
            ++k;
    }
    else
    {
        if(n1 && n3)
            ++k;
        if(n2 && n4)
            ++k;
    }
    k+=n1*n2+n1*n4+n2*n3+n3*n4;
    out<<k<<'\n';
}
void cerinta3()
{
    bool ok;
    long long i,j,p=1,op=0,nr=0;
    do
    {
        ok=0;
        for(i=1;i<n;i++)
            for(j=i+1;j<=n;j++)
                if(x[i]>x[j] || (x[i]==x[j] && y[i]))
                {
                    swap(x[i],x[j]);
                    swap(y[i],y[j]);
                }
    }while(ok);
    while(op<n-1)
    {
        ++op;
        poz[p]=1;
        nr=0;
        i=p+1;
        while(nr<3)
        {
            if(poz[i]!=1)
                ++nr;
            ++i;
            if(i>n)
                i=1;
        }
        p=i-1;
        if(p==0)
            p=n;
      //  out<<p<<endl;
    }
    for(i=1;i<=n;i++)
        if(!poz[i])
            out<<x[i];
}
int main()
{
    long long i;
    in>>n;
    for(i=1;i<=n;i++)
        in>>x[i]>>y[i];
    cerinta1();
    cerinta2();
    cerinta3();
}
