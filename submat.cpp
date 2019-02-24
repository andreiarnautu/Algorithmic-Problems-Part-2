#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("submat.in");
ofstream out("submat.out");
int m,n,i,nr,v[1001],j,x;
short ok=0;
long long maxim,nrc;
int main()
{
    in>>n>>m;
    for(i=0;i<n;i++)
    {
        nr=0;
        ok=1;
        for(j=0;j<m;j++)
        {
            in>>x;
            if(x==1 && ok!=0)
                {nr=j;ok=0;}
        }
        if(x!=1)
            nr=m;
       // out<<nr<<" ";
        v[i]=nr;
    }
    sort(v,v+n);
    for(i=n-1;i>=0;i--)
    {
        //out<<v[i]<<'\n';
        nrc=(n-i)*v[i];
        if(nrc>maxim)
            maxim=nrc;
    }
    out<<maxim;
    return 0;
}
