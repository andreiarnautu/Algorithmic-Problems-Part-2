#include <fstream>
using namespace std;
ifstream in("subsecvmax.in");
ofstream out("subsecvmax.out");

long n,v[100000];


int main()
{
    long k=1,lmax=0,poz,nrc,pozc,ok;
    in>>n;
    for(long i=1;i<n+1;i++)
        in>>v[i];
    while(k<n)
    {
        pozc=k;
        ok=1;
        nrc=1;
        while(v[k]<=v[k+1] && k<n)
        {
           // out<<k<<endl;
            ++nrc;
            ++k;
            ok=0;
        }
        if(nrc>lmax)
        {
            lmax=nrc;
            poz=pozc;
        }
        if(ok==1)
            ++k;
    }
    if(n==1)
        out<<"1 1";
    else
    {
        out<<poz<<" ";
        out<<lmax;
    }
    return 0;
}
