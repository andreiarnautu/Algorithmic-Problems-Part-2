//prof.Pit-Rada Ionel Vasile
#include<fstream>
using namespace std;

int lin[2013], col[2013];
int bis1,bis2,oo,i,n,nrp,nrd,xp,u,v;

void abscisa()
{
    int d,w,i,p,t;
    d=0;
    w=1;
    do
    {
        for (i=0;i<=2000;i++)
            if (col[i]>=w)
            {
                p=(col[i]-w)/3;
                if (w+3*p==col[i])w=3;
                else if (w+3*p==col[i]-1)w=2;
                else w=1;
                col[i]=col[i]-p-1;
                d=d+p+1;
                xp=i;
            }
            else w=w-col[i];
    }
    while (d<n);
}

int main()
{
    ifstream fin("puncte6.in");
    ofstream fout("puncte6.out");
    fin>>n;
    bis1=0;
    bis2=0;
    oo=0;
    for (i=1;i<=n;i++)
    {
        fin>>u>>v;
        col[u+1000]++;
        lin[v+1000]++;
        if (u==v)bis1++;
        if (u==-v)bis2++;
        if (u==0 && v==0) oo++;
    }
    nrp=0;
    for (i=0;i<=2000;i++)
    {
        if (lin[i]>nrp)nrp=lin[i];
        if (col[i]>nrp)nrp=col[i];
    }
    bis1=bis1-oo;
    bis2=bis2-oo;
    nrd=bis1*bis2;
    if (bis1+oo>1)
    {
        nrd++;
    }
    if (bis2+oo>1)
    {
        nrd++;
    }
    fout<<nrp<<"\n";
    fout<<nrd<<"\n";
    abscisa();
    fout<<xp-1000;
    fin.close();
    fout.close();
    return 0;
}

