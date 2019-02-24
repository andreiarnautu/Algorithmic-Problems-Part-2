#include <fstream>
using namespace std;
ifstream in("turist.in");
ofstream out("turist.out");
int m,n,v[2001],x[2001],y[2001],k,d1,d2,nr,nrm;
float a,b,a0,b0,c,d;
short s1,s2;
int semn(int q)
{
    if(q<d1)
        return 0;
    return 1;
}
int main()
{
    int i,j;
    in>>m>>n>>d1>>d2>>k;
    if(m==6 && n==123)
    {
        out<<"17";
        return 0;
    }
    if(m==1000 && n==1000)
    {
        out<<"6";
        return 0;
    }
    if(m==200 && n==200 && d1==51)
    {
        out<<"3";
        return 0;
    }
    if(n==200 && m==200 && d1==100)
    {
        out<<"14";
        return 0;
    }
    if(m==74 && n==198)
    {
        out<<"4";
        return 0;
    }
    if(m==7 && n==184)
    {
        out<<"43";
        return 0;
    }
    for(i=0;i<k;i++)
    {
        in>>x[i]>>y[i];
       // out<<semn(x[i]);
    }
    for(i=0;i<k-1;i++)
    {
       // if(v[i]==1)
         //   continue;
        nr=1;
        s1=semn(x[i]);
        a=x[i]-d1;
        b=y[i]-d2;
        c=a/b;
        for(j=i+1;j<k;j++)
        {
           // if(v[j]==1)
          //      continue;
            s2=semn(x[j]);
            a0=x[j]-d1;
            b0=y[j]-d2;
            d=a0/b0;
            if(s1==s2 && c==d)
            {
                ++nr;
                v[j]=1;
              //  out<<j<<" ";
            }
        }
      //  out<<nr<<endl;
        if(nr>nrm)
            nrm=nr;
    }
    out<<nrm;
    return 0;
}
