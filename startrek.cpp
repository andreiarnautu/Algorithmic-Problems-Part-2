#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("startrek.in");
ofstream out("startrek.out");
long long t,n,i,v[4000],x,p,ok=1,poz;
int main()
{
    in>>n>>t;
    for(i=0;i<n;i++)
        in>>v[i];
    for(i=0;i<n;i++)
    {
        in>>x;
        v[i]/=x;
    }
    sort(v,v+n);
    while(ok)
    {
        ok=0;
        ++p;
        v[0]=-1;
        for(i=0;i<n;i++)
        {
            v[i]-=t;
           // out<<v[i]<<" ";
            if(v[i]>=0 && v[i-1]<0)
            {
                poz=i;
                ok=1;
            }
        }
       // out<<endl;
        for(i=0;i<n-poz;i++)
            v[i]=v[i+poz];
        n-=poz;
        //sort(v,v+n);
    }
    out<<p;
    return 0;
}
